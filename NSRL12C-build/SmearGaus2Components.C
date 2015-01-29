//This function will take a 1PE/bin histogram and smear the data.
//The smearing can spread out to the nearest +/-N bins.
//The smearing is achieved with two components; a pulse-height dependent one and
//a fixed one.
//The first component is due to the PMT's gain (in)stability and the second is
//nominally due to the pedestal.
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
//put the resulting histogram, the intrinsic PMT sigma, the pedestal sigma,
//+/- number of bins to smear.
void SmearGaus2Components(TH1F* hSource, TH1F* &hOut,
			  double sigma, double sigma2,int N){
  
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

    //cout << "i = " << i << endl;
    //cout << "LowEdge = " << LowEdge << endl;
    //cout << "nearestInt = " << nearestInt << endl;

    double CurrentVal = hSource->GetBinContent(i);

    //cout << "CurrentVal = " << CurrentVal << endl;

    double RunningTotBelow = 0;
    double RunningTotAbove = 0;

    //Loop over the +/- N bins on either side of the ith bin
    for(int j = (N-1); j>-1; j--){
      //cout << "j = " << j << endl;
      //cout << "CurrentVal = " << CurrentVal << endl;
      //cout << "TMath::Erf(Low value)  = "
      //	   << TMath::Erf(((LowEdge - j*width) - nearestInt)/(sqrt(2)*sqrt(nearestInt)*sigma)) << endl;
      //CDF of a Gaussian from [-inf, x] = 0.5*(1+erf((x-mean)/(sigma*sqrt(2))))
      double NumBelow;
      if(nearestInt!=0){
	NumBelow =
	  CurrentVal*0.5*(1+TMath::Erf(((LowEdge - j*width) - nearestInt)/
				       (sqrt(2)*sqrt(nearestInt*sigma*sigma +
						     sigma2*sigma2))))
	  - RunningTotBelow;
      }
      else{
	NumBelow =
	  CurrentVal*0.5*(1+TMath::Erf(((LowEdge - j*width) - nearestInt)/
				       (sqrt(2)*sqrt(nearestInt*sigma*sigma +
						     sigma2*sigma2))))
	  - RunningTotBelow;
      }

      //cout << "NumBelow = " << NumBelow << endl;

      RunningTotBelow += NumBelow;
      
      //cout << "RunningTotBelow = " << RunningTotBelow << endl;
      
      double NumAbove;
      if(nearestInt!=0){
	NumAbove =
	  CurrentVal*(1-(0.5*(1+TMath::Erf(((UpEdge + j*width) - nearestInt)/
					   (sqrt(2)*sqrt(nearestInt)*sigma)))))
	  - RunningTotAbove;
      }
      else{
	NumAbove =
	  CurrentVal*(1-(0.5*(1+TMath::Erf(((UpEdge + j*width) - nearestInt)/
					   (sqrt(2)*sigma)))))
	  - RunningTotAbove;
      }
      
      //cout << "NumAbove = " << NumAbove << endl;
      
      RunningTotAbove += NumAbove;
      
      //cout << "RunningTotAbove = " << RunningTotAbove << endl;      
      
      //Add NumBelow to the bins (i - (j+1)) and (i + (j+1)).
      //If the bin I'm adding to is <0 or >(nbins + 1), add it to 0 or nbins+1.
      if((i-(j+1))>0){
	double CurrentBelow = hOut->GetBinContent(i-(j+1));
	double CurrentThis = hOut->GetBinContent(i);
	hOut->SetBinContent(i-(j+1), CurrentBelow + NumBelow);
	hOut->SetBinContent(i, CurrentThis - NumBelow);
      }
      else{
	//Dump in underflow bin 0.
	double CurrentBelow = hOut->GetBinContent(0);
	double CurrentThis = hOut->GetBinContent(i);
	hOut->SetBinContent(0, CurrentBelow + NumBelow);
	hOut->SetBinContent(i, CurrentThis - NumBelow);
      }
      
      if((i+(j+1))<(nbins+1)){
	double CurrentAbove = hOut->GetBinContent(i+(j+1));
	double CurrentThis = hOut->GetBinContent(i);
	hOut->SetBinContent(i+(j+1), CurrentAbove + NumAbove);
	hOut->SetBinContent(i, CurrentThis - NumAbove);
      }
      else{
	//Dump in overflow bin nbins+1.
	double CurrentAbove = hOut->GetBinContent(nbins+1);
	double CurrentThis = hOut->GetBinContent(i);
	hOut->SetBinContent(nbins+1, CurrentAbove + NumAbove);
	hOut->SetBinContent(i, CurrentThis - NumAbove);
      }
    }
  }
  return;
}
