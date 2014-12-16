//This ROOT function will collect up all of the .root files in the current
//directory and add them to a new tree that has all; with the additional
//branches of the primary particle energy and the beam displacement.
#include "tinydir.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include "TChain.h"
using namespace std;

//Arguments: a comma-separated list of energies, a comma-separated list of
//beam heights.
void CollectRuns(string Energies, string Heights){
  vector<string> theEnergy;
  vector<string> theHeight;
  vector<double> valEnergy;
  vector<double> valHeight;

  string line;
  //Get the energies
  istringstream ssEn(Energies);
  //ssEn << (Energies);
  while(getline(ssEn, line, ',')){
    theEnergy.push_back(line);
    //now cast line to a double:
    stringstream ss;
    double dummy;
    ss << line;
    ss >> dummy;
    valEnergy.push_back(dummy);
  }
  //Get the heights
  istringstream ssHgt(Heights);
  while(getline(ssHgt, line, ',')){
    theHeight.push_back(line);
    //now cast line to a double:
    stringstream ss;
    double dummy;
    ss << line;
    ss >> dummy;
    valHeight.push_back(dummy);
  }

  //Initialise the output tree.
  TChain* OutChain = new TChain("ChainResults", "The collected run results");

  for(size_t i=0; i<theEnergy.size(); i++){
    for(size_t j=0; j<theHeight.size(); j++){

      string fname = "Edep_" + theEnergy.at(i) + "MeV_" + theHeight.at(j)
	+ "cm.root";

      cout << "Processing File: " << fname << "... ";

      TFile* infile = TFile::Open(fname.c_str(), "update");
      TTree* inTree = (TTree*)infile->Get("Results");

      //Clean up any old branches...
      //TBranch* OldBranch;
      //if(inTree->GetListOfBranches()->FindObject("BeamEn")){
      //OldBranch = inTree->GetBranch("BeamEn");
      //inTree->GetListOfBranches()->Remove(OldBranch);
      //inTree->Write();
      //}
      //if(inTree->GetListOfBranches()->FindObject("BeamHgt")){
      //OldBranch = inTree->GetBranch("BeamHgt");
      //inTree->GetListOfBranches()->Remove(OldBranch);
      //inTree->Write();
      //}
      //if(inTree->GetListOfBranches()->FindObject("MeanPE_T1")){
      //OldBranch = inTree->GetBranch("MeanPE_T1");
      //inTree->GetListOfBranches()->Remove(OldBranch);
      //inTree->Write();
      //}
      //if(inTree->GetListOfBranches()->FindObject("MeanPE_T2")){
      //OldBranch = inTree->GetBranch("MeanPE_T2");
      //inTree->GetListOfBranches()->Remove(OldBranch);
      //inTree->Write();
      //}
      

      float BeamEn = 0;
      float BeamHgt = 0;
      float MeanT1 = 0;
      float MeanT2 = 0;
      //Add an energy and beam height branch to the tree.
      TBranch* EnBranch = inTree->Branch("BeamEn", &BeamEn, "BeamEn/F");
      TBranch* HgtBranch = inTree->Branch("BeamHgt", &BeamHgt, "BeamHgt/F");
      TBranch* MeanPE_T1 = 
	inTree->Branch("MeanPE_T1", &MeanT1, "MeanPE_T1/F");
      TBranch* MeanPE_T2 =
	inTree->Branch("MeanPE_T2", &MeanT2, "MeanPE_T2/F");
      unsigned long long int measPE_T1 = 0;
      unsigned long long int measPE_T2 = 0;
      double Edep_H1 =0;
      double Edep_H2 = 0;

      inTree->SetBranchAddress("MeasNumPhotons_PMTT1", &measPE_T1);
      inTree->SetBranchAddress("MeasNumPhotons_PMTT2", &measPE_T2);
      inTree->SetBranchAddress("Edep_H1", &Edep_H1);      
      inTree->SetBranchAddress("Edep_H2", &Edep_H2);
      Long64_t nentries = inTree->GetEntries();
      int numAvg = 0;
      for(int k = 0; k<nentries; k++){
	inTree->GetEntry(k);
	//Calculate means
	if((Edep_H1!=0)&&(Edep_H2!=0)){
	  MeanT1 += measPE_T1;
	  MeanT2 += measPE_T2;
	  numAvg++;
	}
      }

      MeanT1 = MeanT1/numAvg;
      MeanT2 = MeanT2/numAvg;

      for(int k = 0; k<nentries; k++){
	BeamEn = valEnergy.at(i);
	BeamHgt = valHeight.at(j);
	EnBranch->Fill();
	HgtBranch->Fill();
	MeanPE_T1->Fill();
	MeanPE_T2->Fill();
      }

      inTree->Write("", TObject::kOverwrite);
	
      fname = fname + "/Results";
      OutChain->Add(fname.c_str());
      infile->Close();
      cout << "Done!" << endl;
    }
  }
  cout << "OutChain has " << OutChain->GetEntries() << " entries." << endl;
  TFile* OutFile = new TFile("ChainedRuns.root", "RECREATE");
  OutChain->Write();
  OutFile->Close();
  return;
}
