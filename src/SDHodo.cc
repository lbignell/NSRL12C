#include "SDHodo.hh"
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


SDHodo::SDHodo(G4String name) : G4VSensitiveDetector(name){
  //Constructor
}

SDHodo::~SDHodo(){;}

void SDHodo::Initialize(G4HCofThisEvent* HCE){
  Edep = 0;
  HazPrimary = false;
}

G4double SDHodo::GetEdep(){return Edep;}
G4bool SDHodo::HadPrimary(){return HazPrimary;}

G4bool SDHodo::ProcessHits(G4Step* theStep, G4TouchableHistory*){

  if(theStep->GetTrack()->GetTrackID()==1){
    HazPrimary = true;
  }
  //Collect the Edep
  Edep += theStep->GetTotalEnergyDeposit()*MeV;

  return true;  
}


void SDHodo::EndOfEvent(G4HCofThisEvent*)
{
  //Currently don't do anything at end of event.
}
