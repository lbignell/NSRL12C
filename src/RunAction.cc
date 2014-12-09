//
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SDManager.hh"
//
#include "DetectorConstruction.hh"
#include "G4VSensitiveDetector.hh"
#include <math.h>
#include "TH1D.h"
#include "TFile.h"
#include <sstream>
#include "TTree.h"
#include "TROOT.h"

RunAction::RunAction(DetectorConstruction* DC){
  //
  
  //take the DetectorConstruction pointer given when this object is created (in main) and copy to local member
  myDC = DC;
  //
  
}

RunAction::~RunAction(){

}

void RunAction::BeginOfRunAction(const G4Run* aRun){

  //Arguments:Name of file,type of rewrite option(UPDATE means append),comments
  RootOP = new TFile("Edep.root","RECREATE","NSRL12C Sim Output");
  
  EdepTree = new TTree("Results", "Tree of results from NSRL12C simulation.");

  EdepTree->Branch("KE_T1", &KE_T1);
  EdepTree->Branch("KE_T2", &KE_T2);
  EdepTree->Branch("Edep_H1", &Edep_H1);
  EdepTree->Branch("Edep_H2", &Edep_H2);
  EdepTree->Branch("Edep_H3", &Edep_H3);
  EdepTree->Branch("Edep_T1", &Edep_T1);
  EdepTree->Branch("Edep_T2", &Edep_T2);
  EdepTree->Branch("VertX", &VertX);
  EdepTree->Branch("VertY", &VertY);
  EdepTree->Branch("HazPrimary_H1", &HazPrimary_H1);
  EdepTree->Branch("HazPrimary_H2", &HazPrimary_H2);
  EdepTree->Branch("HazPrimary_H3", &HazPrimary_H3);
  EdepTree->Branch("HazPrimary_T1", &HazPrimary_T1);
  EdepTree->Branch("HazPrimary_T2", &HazPrimary_T2);
  EdepTree->Branch("NumOP_T1", &NumOP_T1);
  EdepTree->Branch("NumOP_T2", &NumOP_T2);
  EdepTree->Branch("OPEn_T1", &OPEn_T1);
  EdepTree->Branch("OPEn_T2", &OPEn_T2);
  EdepTree->Branch("OPProc_T1", &OPProc_T1);
  EdepTree->Branch("OPProc_T2", &OPProc_T2);
  EdepTree->Branch("OPEn_PMTT1", &OPEn_PMTT1);
  EdepTree->Branch("OPEn_PMTT2", &OPEn_PMTT2);
  EdepTree->Branch("OPEnMeas_PMTT1", &OPEnMeas_PMTT1);
  EdepTree->Branch("OPEnMeas_PMTT2", &OPEnMeas_PMTT2);
  EdepTree->Branch("NumPhotons_PMTT1", &NumOP_PMTT1);
  EdepTree->Branch("NumPhotons_PMTT2", &NumOP_PMTT2);
  EdepTree->Branch("MeasNumPhotons_PMTT1", &MeasNumOP_PMTT1);
  EdepTree->Branch("MeasNumPhotons_PMTT2", &MeasNumOP_PMTT2);

}


void RunAction::
TallyEvtData(double theKE_T1, double theKE_T2,
	     double theEdep_H1, double theEdep_H2, double theEdep_H3,
	     double theEdep_T1, double theEdep_T2,
	     double VxX, double VxY,
	     bool theHazPrimary_H1, bool theHazPrimary_H2,bool theHazPrimary_H3,
	     bool theHazPrimary_T1, bool theHazPrimary_T2,
	     unsigned long long int theNumOP_T1,
	     unsigned long long int theNumOP_T2,
	     vector< vector< double > > &theOPEn_T1,
	     vector< vector< double > > &theOPEn_T2,
	     vector< string >& theOPProc_T1, vector< string >& theOPProc_T2,
	     vector< vector< double > >& theOPEn_PMTT1,
	     vector< vector< double > >& theOPEn_PMTT2,
	     vector< vector< double > >& theOPEnMeas_PMTT1,
	     vector< vector< double > >& theOPEnMeas_PMTT2,
	     unsigned long long int theNumOP_PMTT1,
	     unsigned long long int theNumOP_PMTT2,
	     unsigned long long int theMeasNumOP_PMTT1,
	     unsigned long long int theMeasNumOP_PMTT2){
  //Set the branch values and fill the tree.
  KE_T1 = theKE_T1;  KE_T2 = theKE_T2;
  Edep_H1 = theEdep_H1;  Edep_H2 = theEdep_H2;  Edep_H3 = theEdep_H3;
  Edep_T1 = theEdep_T1;  Edep_T2 = theEdep_T2;
  VertX = VxX;  VertY = VxY;
  HazPrimary_H1 = theHazPrimary_H1;  HazPrimary_H2 = theHazPrimary_H2;
  HazPrimary_H3 = theHazPrimary_H3;
  HazPrimary_T1 = theHazPrimary_T1;  HazPrimary_T2 = theHazPrimary_T2;
  NumOP_T1 = theNumOP_T1;  NumOP_T2 = theNumOP_T2;
  OPEn_T1 = theOPEn_T1;  OPEn_T2 = theOPEn_T2;
  OPProc_T1 = theOPProc_T1;  OPProc_T2 = theOPProc_T2;
  OPEn_PMTT1 = theOPEn_PMTT1;  OPEn_PMTT2 = theOPEn_PMTT2;
  OPEnMeas_PMTT1 = theOPEnMeas_PMTT1;  OPEnMeas_PMTT2 = theOPEnMeas_PMTT2;
  NumOP_PMTT1 = theNumOP_PMTT1;  NumOP_PMTT1 = theNumOP_PMTT1;
  MeasNumOP_PMTT1 = theMeasNumOP_PMTT1;  MeasNumOP_PMTT2 = theMeasNumOP_PMTT2;
  
  EdepTree->Fill();
}

//task to be carried out at the end of the run
void RunAction::EndOfRunAction(const G4Run* aRun){
  //get the number of primary particles being simulated for this run
  G4double NumberOfEvents = aRun->GetNumberOfEventToBeProcessed();
 
  RootOP->Write();
  RootOP->Close();
  

}
