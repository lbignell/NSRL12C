//This function will get the Chi2 values for each kB value.
#include "tinydir.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include "TChain.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TMath.h"

using namespace std;

//Arguments: Pointer to a TH1D histogram, pointer to a histogram into which to
//put the resulting histogram, the single PE sigma.
void SmearGaus(TH1F* hSource, TH1F* &hOut, double sigma){
  
  double width = hSource->GetBinWidth(1);
  if((width>1.001)||(width<0.999)){
    cout << "Bin width must equal 1 PE! Exiting..." << endl;
    return;
  }

  cout << "Before clone: hOut = " << hOut << endl;  

  hOut = (TH1F*)hSource->Clone("Smeared");

  cout << "After clone: hOut = " << hOut << endl;

  //Get the size of hSource.
  int nbins = hOut->GetNbinsX();

  for(Long64_t i = 0; i<(nbins+2); i++){
    //Get the bin edges.
    double LowEdge = hOut->GetBinLowEdge(i);
    double UpEdge = LowEdge + width;

    int nearestInt = floor(UpEdge);

    double CurrentVal = hSource->GetBinContent(i);

    //CDF of a Gaussian from [-inf, x] = 0.5*(1+erf((x-mean)/(sigma*sqrt(2))))
    double NumBelow =
      CurrentVal*0.5*(1+TMath::Erf((LowEdge - nearestInt)/
			(sqrt(2)*sqrt(nearestInt)*sigma)));

    double NumAbove =
      CurrentVal*(1-(0.5*(1+TMath::Erf((UpEdge - nearestInt)/
				       (sqrt(2)*sqrt(nearestInt)*sigma)))));

    //Add NumBelow to the previous bin.
    if(i!=0){
      double CurrentBelow = hOut->GetBinContent(i-1);
      double CurrentThis = hOut->GetBinContent(i);
      hOut->SetBinContent(i-1, CurrentBelow + NumBelow);
      hOut->SetBinContent(i, CurrentThis - NumBelow);
    }

    if(i!=(nbins+1)){
      double CurrentAbove = hOut->GetBinContent(i+1);
      double CurrentThis = hOut->GetBinContent(i);
      hOut->SetBinContent(i+1, CurrentAbove + NumAbove);
      hOut->SetBinContent(i, CurrentThis - NumAbove);
    }
  }
  return;
}


//Arguments: % WbLS, comma-separated list of kB values. I'll assume it is
//210 MeV beam energy. Valid values of pcWbLS are "1pc", "0p4pc", and "PureLS".
//The bins are for rebinning the histogram.
void GetChi2Vals(string pcWbLS, string kBVals, int nbins, double startbin, TTree* outTree){

  if(!((pcWbLS=="1pc")||(pcWbLS=="0p4pc")||(pcWbLS=="PureLS"))){
    cout << "Error: your choice of % WbLS is inappropriate." << endl
	 << "Valid values of pcWbLS are \"1pc\", \"0p4pc\", and \"PureLS\""
	 << ", exiting..." << endl;
    return;
  }

  vector<string> strkB;
  vector<double> valkB;
  cout << "Parsing arguments..." ;
  //Separate out the comma-separated list.
  string line;
  istringstream sskB(kBVals);
  while(getline(sskB, line, ',')){
    strkB.push_back(line);
    stringstream ss;
    double dummy;
    ss << line;
    ss >> dummy;
    valkB.push_back(dummy);
  }

  cout << "Done!" << endl << "Reading Tree...";
  //Open up the data tree
  TFile* f = TFile::Open("../AllResults_NewSinglePECal.root");
  string hname = "WbLS_" + pcWbLS + "_T2_210";
  TH1D* rawdata = (TH1D*)f->Get(hname.c_str());
  cout << "Done!" << endl << "Drawing data... ";

  //Create a TCanvas
  TCanvas theCanvas;
  //rawdata->Draw("");
  //return NULL;

  double binedges[(nbins+1)];
  for(int i = 0; i<(nbins+1); i++){binedges[i] = i + startbin;}
  cout << "Creating histogram...";
  TH1D* hdata = (TH1D*)rawdata->Rebin(nbins, "hdata", binedges);
  cout << "Done! ";
  hdata->Draw("");
  hdata->SetLineColor(1);
  hdata->SetLineWidth(3);
  

  cout<< "Done!" << endl << "Creating tree...";
  double theMean = 0;
  bool isData = false;
  double theChi2 = -1;
  double thekB = -1;
  double theIntegral = -1;


  outTree->Branch("Mean", &theMean);
  outTree->Branch("IsData", &isData);
  outTree->Branch("Chi2", &theChi2);
  outTree->Branch("kB", &thekB);
  outTree->Branch("Integral", &theIntegral);

  cout << "Done!" << endl << "Filling data vals...";
  //Fill the tree with the data result.
  theMean = hdata->GetMean();
  theIntegral = hdata->Integral();
  isData = true;
  outTree->Fill();
  //Store the data integral and reinitialize variables.
  double DataIntegral = theIntegral;
  theIntegral = -1;
  theMean = 0;
  isData = false;

  cout << "Done!" << endl << "Running loop..";
  for(int i = 0; i<strkB.size(); i++){
    //Open up the simulation files.
    string simfname = "WbLS_" + pcWbLS + "_kB" + strkB.at(i) + "_210MeV.root";
    TFile* simfile = TFile::Open(simfname.c_str());
    TTree* simtree = (TTree*)simfile->Get("Results");
    TH1F* theHistRaw;
    simtree->Draw("MeasNumPhotons_PMTT2>>theHistRaw",
		  "(Edep_H1!=0)&&(Edep_H2!=0)", "SAME");
    theHistRaw = (TH1F*)gDirectory->Get("theHistRaw");
    //Smear the hist with a gaussian.
    TH1F* theHist;
    SmearGaus(theHistRaw, theHist, 0.32);
    theMean = theHist->GetMean();
    theHist->SetLineColor(i+2);
    theIntegral = theHist->Integral();
    theHist->Scale(DataIntegral/theIntegral);
    theChi2 = theHist->Chi2Test(hdata, "WUPCHI2");
    thekB = valkB.at(i);
    outTree->Fill();
    theMean = 0;
    theIntegral = -1;
    theChi2 = -1;
    thekB = -1;
    simfile->Close();
  }
  cout << "Done!" << endl;
  return;
}

