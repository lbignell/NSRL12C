#include "SensitiveDetector.hh"
#include "G4Step.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4SystemOfUnits.hh"

#include "RunAction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4SteppingManager.hh"
#include <iterator>
#include "G4TrackVector.hh"
#include "G4SDManager.hh"
#include "SDHodo.hh"
#include "PMTwin.hh"


//Called at the beginning of each new session.
SensitiveDetector::SensitiveDetector(G4String name)
  : G4VSensitiveDetector(name){
  //Get name of LV corresponding to this SD.
  LVname = name;
  runnum = 0;
}

SensitiveDetector::~SensitiveDetector(){;}

//Called at the beginning of each event
void SensitiveDetector::Initialize(G4HCofThisEvent* HCE){

  TrackID = 0;
  EdepThisEventUnquenched = 0;

  //Set constants for Stopping Power calculation
  Const = (0.15353745)*((MeV*cm2)/g);
  SpdOfLight = (2.99792458*pow(10.,10.))*(cm/s);
  ElecRestEnergy = 0.511003*MeV;
  DensityEffectCorr = 0.;

  KinEnIn = 0.;
  VertexX = DBL_MAX;
  VertexY = DBL_MAX;

  TotOptPhotons = 0;
  dblvec.clear();
  intvec.clear();
  InitEnVec.clear();
  ParentIDVec.clear();
  ProcVec.clear();

  for(int i = 0; i<3; i++){
    //G4cout << "Initialising vector dimensions" << G4endl;
    InitEnVec.push_back(dblvec);
    ParentIDVec.push_back(intvec);
  }

  HitWindow = false;
  hazPrimary = false;
}

//This method is invoked by G4SteppingManager when a step is composed in the
//G4LogicalVolume which has the pointer to this sensitive detector. The first
//argument of this method is a G4Step  object of the current step.
G4bool SensitiveDetector::ProcessHits(G4Step* theStep, G4TouchableHistory*){

  //A bit of code to check for reflections:
  if((HitWindow)&&(theStep->GetTrack()->GetTrackID()==PhotonID)){
    //G4cout << "Photon reflected from UVT Acrylic, removing hit!" << G4endl;
    if(ProcVec.size()!=0){
      ProcVec.pop_back();
    }
    HitWindow = false;
  } 


  //Check whether the particle is stepping into the volume from outside...
  if((theStep->GetTrack()->GetTrackID()!=TrackID)&&
     (theStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName()!=
      theStep->GetTrack()->GetVolume()->GetLogicalVolume()->GetName())
     ){
    //Set the TrackID to avoid repeatedly counting particles.
    TrackID = theStep->GetTrack()->GetTrackID();
    //There are some issues with the way KinEnIn is tallied (sometimes a
    //particle's kinetic energy is counted twice; leading to incident KE greater
    //than the primary particle's energy.
    //I can avoid many of these events by just avoiding counting the primary
    //particle more than once; as below...
    if(!((theStep->GetTrack()->GetTrackID()==1)&&(hazPrimary))){
      KinEnIn += theStep->GetPreStepPoint()->GetKineticEnergy();
    }
    if(theStep->GetTrack()->GetTrackID()==1){hazPrimary = true;}

    //This only captures the vertex of the first particle entering; which in
    //most cases will be the primary.
    if(VertexX==DBL_MAX){
      //Collect the vertex locations of the entering particle.
      VertexX = theStep->GetTrack()->GetVertexPosition().getX();
      VertexY = theStep->GetTrack()->GetVertexPosition().getY();
    }
  }


  //Need to add in alternate Edep collection, simple Edep per step.
  EdepThisEventUnquenched += theStep->GetTotalEnergyDeposit()*MeV;


  ////////////////////////////////////////////////////////////////////////////  
  //Get optical photons
  if(theStep->GetTrack()->GetParticleDefinition()->GetParticleName()
     =="opticalphoton"){

    ///////First step stuff///////
    //Identify optical photons upon creation within the volume.
    G4int StepNum = theStep->GetTrack()->GetCurrentStepNumber();

    //Increment the tally of the number of optical photons generated.
    if( StepNum == 1 ){      

      //idx[0] = Cerenkov photons,
      //idx[1] = WLS photons,
      //idx[2] = scintillation photons.      
      if(theStep->GetTrack()->GetCreatorProcess()->GetProcessName()
	 =="Cerenkov"){
	//Energy upon production.
	InitEnVec.at(0)
	  .push_back(theStep->GetTrack()->GetVertexKineticEnergy());
	//ParentID
	ParentIDVec.at(0).push_back(theStep->GetTrack()->GetParentID());
      }
      else if(theStep->GetTrack()->GetCreatorProcess()->GetProcessName()
	      =="OpWLS"){
	//First step of a WLS photon.
	InitEnVec.at(1)
	  .push_back(theStep->GetTrack()->GetVertexKineticEnergy());
	//Get the particle ID of the parent.
	ParentIDVec.at(1).push_back(theStep->GetTrack()->GetParentID());
      }
      else if(theStep->GetTrack()->GetCreatorProcess()->GetProcessName()
	      =="Scintillation"){
	//Scintillation photon
	InitEnVec.at(2)
	  .push_back(theStep->GetTrack()->GetVertexKineticEnergy());
	//Get the particle ID of the parent.
	ParentIDVec.at(2).push_back(theStep->GetTrack()->GetParentID());
      }
      else{
	//Some other process for generating optical photons, issue warning.
	G4cout << "WARNING: an optical photon was generated by a process other"
	       << " than 'Cerenkov' or 'OpWLS'. The process was: "
	       << theStep->GetTrack()->GetCreatorProcess()->GetProcessName()
	       << G4endl;
      }

      //Increment number of opt photons.
      TotOptPhotons++;

    }
    
    
    ///////Absorption/process stuff///////
    //What I want from this section is to get an idea of the number of photons
    //absorbed by the water and that escape through the acrylic window.
    //The black teflon reflection can be implemented here.
    
    if( (theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()
	 != "Transportation") ){
      //"Transportation" covers the step being limited by the maximum step size
      //or encountering a boundary.
      
      //Something happened. Log the data.
      ProcVec.push_back(theStep->GetPostStepPoint()->GetProcessDefinedStep()
			->GetProcessName());

    }
    //Also need to cover the case where the post step point lands in the
    //UVT Acrylic
    else if(theStep->GetPostStepPoint()->GetMaterial()->GetName()
	    == "G4_POLYACRYLONITRILE"){

      ProcVec.push_back("UVTwindow");

      //Get track ID. If the very next time this method is called it is still 
      //the same track ID, then the photon was reflected. (this is doubly true
      //as all photons that are incident on the PMT window are killed).
      PhotonID = theStep->GetTrack()->GetTrackID();
      HitWindow = true;
    }
    else if(theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()
	    =="T2_phys"){
      //Implement the reflection probability.
      G4double ReflProb = 0.0;
      if(G4UniformRand()<ReflProb){
	//Allow photon to live (do nothing).
      }
      else{
	//kill the photon.
	theStep->GetTrack()->SetTrackStatus(fStopAndKill);
      }

    }
    else if(theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()
    	    =="T1_phys"){
    //Implement the reflection probability.
      G4double ReflProb = 0.865;//Old value, when white tub was implemented.
      //G4double ReflProb = 0.;
      if(G4UniformRand()<ReflProb){
	//Allow photon to live (do nothing).
      }
      else{
	//kill the photon.
	theStep->GetTrack()->SetTrackStatus(fStopAndKill);
      }

    }

    //    else if(theStep->GetPostStepPoint()->GetMaterial()->GetName()
    //	    !="G4_WATER"){
    //cout << "PV at boundary = "
    //	   << theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()
    //	   << endl;
    //}
  }
  
  return true;  
}


/*This method is invoked at the end of each event. The argument of this method is the same object as the previous method. Hits collections occasionally created in your sensitive detector can be associated to the G4HCofThisEvent object.*/
void SensitiveDetector::EndOfEvent(G4HCofThisEvent*){
  //ensure tree is filled only once per event, only call from T1...
  if(LVname=="T1_log"){
    //get run action pointer
    RunAction* myRunAction = (RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
    
    if(myRunAction){
      //Get the H1/H2/H3 Edep and whether primary was incident.
      G4SDManager* SDman = G4SDManager::GetSDMpointer();
      
      SDHodo* pH1 = (SDHodo*)SDman->FindSensitiveDetector("H1_log");
      G4double EnH1 = pH1->GetEdep();
      G4bool HPH1 = pH1->HadPrimary();
      
      SDHodo* pH2 =(SDHodo*)SDman->FindSensitiveDetector("H2_log");
      G4double EnH2 = pH2->GetEdep();
      G4bool HPH2 = pH2->HadPrimary();
      
      SDHodo* pH3 =(SDHodo*)SDman->FindSensitiveDetector("H3_log");
      G4double EnH3 = pH3->GetEdep();
      G4bool HPH3 = pH3->HadPrimary();

      //Get pointer to T2's SD.
      SensitiveDetector* pT2 =
	(SensitiveDetector*)SDman->FindSensitiveDetector("T2_log");
      
      PMTwin* PMTT1 = (PMTwin*)SDman->FindSensitiveDetector("PMT_T1_log");
      vector< vector< double > > PMTEnT1 = PMTT1->GetEnSpec();
      vector< vector< double > > MeasPMTEnT1 = PMTT1->GetMeasEnSpec();
      unsigned long long int PhotonsT1 = PMTT1->GetTotalPhotons();
      unsigned long long int MeasPhotonsT1 = PMTT1->GetMeasPhotons();
      vector<string> LVatVertexT1 = PMTT1->GetLVatVertex();
      vector<double> TrackLengthT1 = PMTT1->GetTrackLength();
      
      PMTwin* PMTT2 = (PMTwin*)SDman->FindSensitiveDetector("PMT_T2_log");
      vector< vector< double > > PMTEnT2 = PMTT2->GetEnSpec();
      vector< vector< double > > MeasPMTEnT2 = PMTT2->GetMeasEnSpec();
      unsigned long long int PhotonsT2 = PMTT2->GetTotalPhotons();
      unsigned long long int MeasPhotonsT2 = PMTT2->GetMeasPhotons();
      vector<string> LVatVertexT2 = PMTT2->GetLVatVertex();
      vector<double> TrackLengthT2 = PMTT2->GetTrackLength();
      
      //cout << "T1 generated = " << TotOptPhotons << endl
      //   << "T1 at PMTwin = " << PhotonsT1 << endl
      //   << "T1 measured  = " << MeasPhotonsT1 << endl
      //   << "T2 generated = " << pT2->GetNumOP() << endl
      //   << "T2 at PMTwin = " << PhotonsT2 << endl
      //   << "T2 measured  = " << MeasPhotonsT2 << endl
      //   << "###########################" << endl;
      
      //See RunAction.hh for a list of arguments
      myRunAction->
	TallyEvtData(KinEnIn, pT2->GetKE(), EnH1, EnH2, EnH3,
		     EdepThisEventUnquenched, pT2->GetEdep(), VertexX, VertexY,
		     HPH1, HPH2, HPH3, hazPrimary, pT2->HadPrimary(),
		     TotOptPhotons, pT2->GetNumOP(), InitEnVec, pT2->GetOPEn(),
		     ProcVec, pT2->GetOPProc(), PMTEnT1, PMTEnT2,
		     MeasPMTEnT1, MeasPMTEnT2, PhotonsT1, PhotonsT2,
		     MeasPhotonsT1, MeasPhotonsT2, LVatVertexT1, LVatVertexT2,
		     TrackLengthT1, TrackLengthT2);
      
    }
  }
}
  

G4double SensitiveDetector::ApplyBirksQuench(G4double En){
  //method to get the ionisation quench correction.

  //I can get the Mean Ionisation Potential in the following ways:
  //1.If I'm happy with the way G4 calculates this (see web) then I can get it
  //  via theStep()->GetTrack()->GetMaterial()->GetIonisation()
  //  ->GetMeanExcitationEnergy() method.
  //2.Define the Mean Excitation Energy as an entry in the Materials Property
  //  Table which can be accessed via theStep->GetTrack()->GetMaterial()
  //  ->GetMaterialPropertiesTable()->GetConstProperty(ref) method.
  //  This would also be a convenient way of getting kB.
  //3.Calculate it myself here.
  //4.Define it here as a number which will need to be changed depending on the
  //  scintillant used.

  //Going to go with Option 2. on advice from Li.
  //Code is implemented in ProcessHits.

  //Need to evaluate integral by either Simpson's rule or Trapezoidal rule
  //Take approximation over 10000 points.

  if(En!=0){
    G4int numPoints = 1000;
    G4double SumPart = 0;
    for(int i = 1; i<(numPoints); i++){
      SumPart += EvaluateBirks((En*i)/numPoints);
    }

    G4double BraketedBit = (((EvaluateBirks(En)+EvaluateBirks(0.))/2)+SumPart);
    G4double QuenchIntegral = BraketedBit/numPoints;
    G4double QuenchedEnergy = En*QuenchIntegral;

    //Then return the quenched energy.
    return QuenchedEnergy;
  }
  else{return 0;}
}

G4double SensitiveDetector::EvaluateBirks(G4double En){
  if(En!=0){
    G4bool Interp = false;
    G4double EnOrig;
    if(En<0.1*keV){
      EnOrig = En;
      En = 0.1*keV;
      Interp = true;
    }
    
    //Get necessary constants sorted out.
    G4double BetaSquared = 1 - pow((ElecRestEnergy/(ElecRestEnergy+En)),2);
    G4double Tau = (En/ElecRestEnergy);
    G4double Fminus = (1-BetaSquared)*(1+((Tau*Tau)/8)-((2*Tau+1)*log(2)));
    
    //Calculate the stopping power
    G4double dEdX = ScintDensity*Const*(1/BetaSquared)*ZonA*(log(pow((En/MeanExEn),2))+log(1+Tau/2)+Fminus-DensityEffectCorr);
    
    if(Interp==true){
      //Interpolate to zero for < 100eV particles.
      dEdX = dEdX*(EnOrig/(0.1*keV));
    }

    //Apply the basic Birk's formula
    G4double BirksCorr = (1/(1+kB*dEdX));

    return BirksCorr;  
  }
  else{return 0;}
}

vector< vector< double > >& SensitiveDetector::GetOPEn(){return InitEnVec;}

vector< string >& SensitiveDetector::GetOPProc(){return ProcVec;}

double SensitiveDetector::GetKE(){return KinEnIn;}

double SensitiveDetector::GetEdep(){return EdepThisEventUnquenched;}

bool SensitiveDetector::HadPrimary(){return hazPrimary;}

unsigned long long int SensitiveDetector::GetNumOP(){return TotOptPhotons;}
