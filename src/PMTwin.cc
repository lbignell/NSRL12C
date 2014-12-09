#include "PMTwin.hh"
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
#include "G4TrackStatus.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"

PMTwin::PMTwin(G4String name) : G4VSensitiveDetector(name){
  runnum = 0;
  LVname = name;
}

PMTwin::~PMTwin(){;}

void PMTwin::Initialize(G4HCofThisEvent* HCE){

  runnum = 0;
  HazPrimary = false;
  TotPhotons = 0;
  MeasPhotons = 0;
  PCphotons = 0;
  TrackID = 0;
  dblvec.clear();
  PhotEn.clear();
  ParentID.clear();
  PMTFireParentID.clear();
  PMTFirePhotEnIn_nm.clear();

  for(int i = 0; i<3; i++){
    PhotEn.push_back(dblvec);
    ParentID.push_back(dblvec);
    PMTFirePhotEnIn_nm.push_back(dblvec);
    PMTFireParentID.push_back(dblvec);
  }

  TubName = "";

}

vector< vector< double > >& PMTwin::GetEnSpec(){return PhotEn;}
vector< vector< double > >& PMTwin::GetParentIDs(){return ParentID;}
vector< vector< double > >& PMTwin::GetMeasEnSpec()
{return PMTFirePhotEnIn_nm;}
vector< vector< double > >& PMTwin::GetMeasParentIDs()
{return PMTFireParentID;}
G4double PMTwin::GetTotalPhotons(){return TotPhotons;}
G4double PMTwin::GetMeasPhotons(){return MeasPhotons;}
G4double PMTwin::GetPhotsOnPhotoCathode(){return PCphotons;}


G4bool PMTwin::ProcessHits(G4Step* theStep, G4TouchableHistory*){

  //Get optical photons
  if(theStep->GetTrack()->GetParticleDefinition()->GetParticleName()
     =="opticalphoton"){
    
    //Check the track ID to avoid re-counting particles that don't hit the
    //effective area on their first step.
    if(theStep->GetTrack()->GetTrackID()!=TrackID){
      //Increment counter
      TotPhotons++;
      //Update TrackID
      TrackID = theStep->GetTrack()->GetTrackID();
    }

    DetectorConstruction* myDC = 
      (DetectorConstruction*)(G4RunManager::GetRunManager()->
			      GetUserDetectorConstruction());

    if(theStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()
       =="PMT_T1_phys"){TubName = "T1";}
    else if(theStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()
	    =="PMT_T2_phys"){TubName = "T2";}
    else{
      cout << "Stepping in unkonwn volume: PostStepPoint = "
	   << theStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()
	   << ". PreStepPoint = "
	   << theStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()
	   << endl;
    }

    //Test to see if photons are hitting the 'effective area' of the photo-
    //cathode. The R7723 used has an effective area diameter of 46 mm. The
    //model used is a uniform area characterised entirely by the PMT QE (i.e.
    //doesn't depend on photon angle of incidence), with zero response outside
    //the effective area.
    //Z = beam axis; X = transverse direction to beam axis. So PMT face is in
    //X-Z plane.

    //PMT window is always centred on X, but the Z co-ord of the centre depends
    //upon the tub...
    G4double CentreZ = DBL_MAX;
    G4double EffDiam = 0;
    if(TubName=="T1"){CentreZ = 0; EffDiam = 44*mm;}
    else if(TubName=="T2"){CentreZ = ((250-224)*2.54)*cm; EffDiam = 44*mm;}
    else{ cout << "Warning! Incorrect tub name. TubName = " << TubName << endl;}

    G4double PhotX = theStep->GetPostStepPoint()->GetPosition().x(); 
    G4double AbsPhotZ = theStep->GetPostStepPoint()->GetPosition().z();
    //cout << "PhotX = " << PhotX << ", PhotZ = " << AbsPhotZ << endl;
    G4double PhotZ = AbsPhotZ-CentreZ;
    G4double PhotR = sqrt(PhotX*PhotX+PhotZ*PhotZ);

    //I'll give it 1mm of leeway to avoid spurious warnings.
    if(PhotR>(52*mm/2))
      {cout << "PMTwin::PhotR is too big! PhotR = " << PhotR << endl;}
    
    //Add a semi-arbitrary inefficiency factor to the PMT response, to
    //optimise the output to that measured.
    G4double FFactor = G4UniformRand();

    //For default PMT gap of 0.1 mm, FFactor = 0.905.
    if((PhotR<=(EffDiam/2))&&(FFactor<1)){
      //For 1 mm PMT gap
      //if((PhotR<=(46.*mm/2))&&(FFactor<0.94)){
      //Photon hitting effective area.
      //G4cout << "Photon is hitting effective area!" << G4endl;
      
      G4bool IsDetected =
	PMTHazFired(theStep->GetPostStepPoint()->GetKineticEnergy());
      
      if(theStep->GetTrack()->GetCreatorProcess()->GetProcessName()
	 =="Cerenkov"){
	//Log Cerenkov photons
	PhotEn.at(0).push_back(theStep->GetPostStepPoint()->GetKineticEnergy());
	ParentID.at(0).push_back(theStep->GetTrack()->GetParentID());
	  if(IsDetected){
	    MeasPhotons++;
	    //First, convert En (MeV) to wavelength (nm).
	    G4double Wavelength = 1239.84187/
	      (theStep->GetPostStepPoint()->GetKineticEnergy()/eV);
	    PMTFirePhotEnIn_nm.at(0).push_back(Wavelength);
	    PMTFireParentID.at(0).push_back(theStep->GetTrack()->GetParentID());
	  }
      }
      else if(theStep->GetTrack()->GetCreatorProcess()->GetProcessName()
	      =="OpWLS"){
	//Log scintillation photons.
	PhotEn.at(1).push_back(theStep->GetPostStepPoint()->GetKineticEnergy());
	ParentID.at(1).push_back(theStep->GetTrack()->GetParentID());
	if(IsDetected){
	  MeasPhotons++;
	  //First, convert En (MeV) to wavelength (nm).
	  G4double Wavelength = 1239.84187/
	    (theStep->GetPostStepPoint()->GetKineticEnergy()/eV);
	  PMTFirePhotEnIn_nm.at(1).push_back(Wavelength);
	  PMTFireParentID.at(1).push_back(theStep->GetTrack()->GetParentID());
	}
      }
      else if(theStep->GetTrack()->GetCreatorProcess()->GetProcessName()
	      =="Scintillation"){
	//Log scintillation photons.
	PhotEn.at(2).push_back(theStep->GetPostStepPoint()
			       ->GetKineticEnergy());
	ParentID.at(2).push_back(theStep->GetTrack()->GetParentID());
	if(IsDetected){
	  MeasPhotons++;
	  //First, convert En (MeV) to wavelength (nm).
	  G4double Wavelength = 1239.84187/
	    (theStep->GetPostStepPoint()->GetKineticEnergy()/eV);
	  PMTFirePhotEnIn_nm.at(2).push_back(Wavelength);
	  PMTFireParentID.at(2).push_back(theStep->GetTrack()->GetParentID());
	}
      }
      else{
	//Print a warning.
	G4cout << "WARNING: a photon was incident on the upstream PMT from an"
	       << " unknown process! The process name was: "
	       << theStep->GetTrack()->GetCreatorProcess()->GetProcessName()
	       << G4endl;
      }
      
      theStep->GetTrack()->SetTrackStatus(fStopAndKill);
      
    }
  }
  
  return true;  
}


void PMTwin::EndOfEvent(G4HCofThisEvent*)
{
  //Do nothing
}


//Sample the PMT QE
G4bool PMTwin::PMTHazFired(G4double Lambda){
  //Energy units in QE file are MeV.

  //Get the QE vector.
  DetectorConstruction* myDC = 
    (DetectorConstruction*)(G4RunManager::GetRunManager()->
			    GetUserDetectorConstruction());

  vector< vector< double > > QEdata = myDC->GetQEdata();
  //first column is lambda, second is QE.

  //get a vector iterator, starting at beginning of vector.
  std::vector<double>::reverse_iterator itWL = QEdata.at(0).rbegin();
  std::vector<double>::reverse_iterator itQE = QEdata.at(1).rbegin();

  //G4cout << "QEdata.at(0).size() = " << QEdata.at(0).size() << G4endl;

  G4double prevWL = *itWL;
  G4double prevQE = *itQE;
  G4double thisWL = 0.;
  G4double thisQE = 0.;
  G4double theQE = 0;
  while(itWL != QEdata.at(0).rend()){//Loop shouldn't break with this condition
    // unless I have an error in my code.
    itWL++;
    itQE++;
    thisWL = *itWL;
    thisQE = *itQE;
    if((prevWL<Lambda)&&(Lambda<thisWL)){
      //Interpolate btw QE points and do MC trial of QE.
      theQE = prevQE + (Lambda-prevWL)*(thisQE-prevQE)/(thisWL-prevWL);
      //Now do MC trial to say whether photon is detected.
      //G4cout << "prevQE = " << prevQE << ", thisQE = " << thisQE 
      //     << ", theQE = " << theQE << G4endl;
      G4double trial = G4UniformRand();
      if(trial<=theQE){
	return true;
      }
      else{
	return false;
      }
    }
    else{//Initialise for next iteration.
      prevWL = thisWL;
      prevQE = thisQE;
    }
  }

  //If we've made it this far, the loop has finished, so return a warning.
  //G4cout<<"WARNING: a photon has hit PMTdown that was out of range of the QE "
  //	 << "data! Photon wavelength = " << Lambda << " MeV" << G4endl;
  //After looking at the events that make it through the while loop using the
  //output above; it is only the very long wavelength photons that make it
  //though (<~1.5 eV). These will have zero QE, so return false.
  return false;
}
