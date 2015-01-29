//This function will take a 1PE/bin histogram and smear the data with a Gaussian
//I'll monte-carlo sample the PDF of the Gaussian to broaden it.
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
#include "TRandom.h"
#include <algorithm>

using namespace std;

//Arguments: Pointer to a TH1D histogram, pointer to a histogram into which to
//put the resulting histogram, the single PE sigma.
void SmearGausMultibin(TH1F* hSource, TH1F* &hOut, double sigma){
  
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

  TRandom rand;

  //Loop over the bins; including the overflow bins.
  for(Long64_t i = 1; i<(nbins+2); i++){
    //cout << "Processing bin " << i << endl;
    //Get the bin edges.
    double LowEdge = hOut->GetBinLowEdge(i);
    double UpEdge = LowEdge + width;

    int nearestInt = floor(UpEdge);

    //Note that I'm getting it from hSource, not hOut!
    double CurrentVal = hSource->GetBinContent(i);

    //cout << "CurrentVal = " << CurrentVal << endl;

    //Here's where I need to sample a gaussian centred on nearestInt with a
    //width of sqrt(nearestInt)*sigma, CurrentVal times.
    //I'll store the results in a vector.
    vector<double> SmearVals;
    //cout << "Filling vector... ";
    for(int j = 0; j<CurrentVal; j++){
	double theNum = rand.Gaus(nearestInt, (sqrt(nearestInt)*sigma));
	SmearVals.push_back(theNum);}
    //cout << "Done!" << endl;

    //Sort the vector to make processing easier.
    std::sort(SmearVals.begin(), SmearVals.end());

    double nearestLowEdge = hOut->GetBinLowEdge(0);
    int theIndex = 0;

    //Get the bin appropriate to the first entry in the vector.
    if(SmearVals.size()!=0){
      //Determine the nearest bin low edge
      while(nearestLowEdge<SmearVals.at(0)){
	theIndex++;
	nearestLowEdge = hOut->GetBinLowEdge(theIndex);
      }
    }

    //cout << "Number of entries in vector = " << SmearVals.size() << endl;

    //Now loop through and add the values to the appropriate bin.
    for(size_t j = 0; j<SmearVals.size(); j++){
      //cout << "Processing vector entry: " << j << "... ";
      bool isFilled = false;
      while(!isFilled){
	//if this SmearVals is less than bin upper edge, add to hOut at theIndex
	if(SmearVals.at(j)<(nearestLowEdge + width)){
	  hOut->AddBinContent(theIndex);
	  isFilled = true;
	}
	else if(theIndex==(nbins+1)){
	  //We've reached the overflow bin, just dump the data here.
	  hOut->AddBinContent(theIndex);
	  isFilled = true;
	}
	else{
	  //go to the next highest bin and try that.
	  theIndex++;
	  nearestLowEdge = hOut->GetBinLowEdge(theIndex);
	}
      }
    }
  }//End of loop on original histogram bins 
  return;
}
