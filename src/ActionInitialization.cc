#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* detector)
  : G4VUserActionInitialization(), myDetector(detector){}

ActionInitialization::~ActionInitialization(){}

void ActionInitialization::BuildForMaster() const {
  //Register RunAction.
  SetUserAction(new RunAction(myDetector));
}

void ActionInitialization::Build() const {
  //Set PGA
  SetUserAction(new PrimaryGeneratorAction());

  //Do I need to re-register RunAction here?
  SetUserAction(new RunAction(myDetector));
}
