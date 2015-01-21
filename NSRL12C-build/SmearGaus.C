//This function will take a 1PE/bin histogram and smear the data with a Gaussian
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
