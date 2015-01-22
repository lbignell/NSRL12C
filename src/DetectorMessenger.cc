//Detector Messenger Class controls UI Commands for adjusting detector params
#include "DetectorMessenger.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4RunManager.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* Det)
:Detector(Det)
{ 
  //Set up Directories
  Dir = new G4UIdirectory("/CustomCommands");
  Dir->SetGuidance("UI commands to modify this simulation");
  
  detDir = new G4UIdirectory("/CustomCommands/det/");
  detDir->SetGuidance("Detector Geometry Commands");
       
  BeamHeightCmd = new G4UIcmdWithADoubleAndUnit("/CustomCommands/det/setBeamHeight",this);  
  BeamHeightCmd->SetGuidance("Set the vertical displacement of the beam.");
  BeamHeightCmd->SetParameterName("Size",false);
  //BeamHeightCmd->SetRange("Size>0.");
  BeamHeightCmd->SetUnitCategory("Length");
  BeamHeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle,
				    G4State_GeomClosed,G4State_EventProc);  

  PMTGapCmd = new G4UIcmdWithADoubleAndUnit("/CustomCommands/det/setPMTGap",this);  
  PMTGapCmd->SetGuidance("Set gap between PMT and UVT Acrylic");
  PMTGapCmd->SetParameterName("Size",false);
  PMTGapCmd->SetRange("Size>=0.");
  PMTGapCmd->SetUnitCategory("Length");
  PMTGapCmd->AvailableForStates(G4State_PreInit,G4State_Idle,
				G4State_GeomClosed,G4State_EventProc);  

  isWaterCmd = new G4UIcmdWithABool("/CustomCommands/det/isWater", this);
  isWaterCmd->SetGuidance("Set detector medium as water or WbLS");
  isWaterCmd->SetParameterName("isWater", false);
  isWaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle,
				 G4State_GeomClosed,G4State_EventProc);  


  WbLSfractionCmd = new G4UIcmdWithADouble("/CustomCommands/det/setWbLSfraction"
					   , this);
  WbLSfractionCmd->SetGuidance("Set fraction of WbLS, must be between 0 and 1");
  WbLSfractionCmd->AvailableForStates(G4State_PreInit,G4State_Idle,
				      G4State_GeomClosed,G4State_EventProc);

  ManualYieldCmd = new G4UIcmdWithADouble("/CustomCommands/det/setManualYield",
					  this);
  ManualYieldCmd->
    SetGuidance("Manually set the scintillation light yield (Ph/MeV)");
  ManualYieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle,
				     G4State_GeomClosed,G4State_EventProc);

  CalculateYieldCmd =
    new G4UIcmdWithoutParameter("/CustomCommands/det/CalculateYield", this);
  CalculateYieldCmd->
    SetGuidance("Call to calculate the light yield by scaling WbLS fraction");
  CalculateYieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle,
					G4State_GeomClosed,G4State_EventProc);


  UpdateCmd = new G4UIcmdWithoutParameter("/CustomCommands/det/update",this);
  UpdateCmd->SetGuidance("Update calorimeter geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_PreInit,G4State_Idle,G4State_GeomClosed,G4State_EventProc);

  BirksCmd = new G4UIcmdWithADouble("/CustomCommands/det/setBirks",this);  
  BirksCmd->SetGuidance("Set the Birks constant, in units of mm/MeV");
  BirksCmd->SetParameterName("Size",false);
  BirksCmd->SetRange("Size>=0.");
  BirksCmd->AvailableForStates(G4State_PreInit,G4State_Idle,
				G4State_GeomClosed,G4State_EventProc);  

  FnameCmd = new G4UIcmdWithAString("/CustomCommands/RA/setFileName", this);
  FnameCmd->SetGuidance("Set the name of the root output file.");
  FnameCmd->SetParameterName("FileName", false);
  FnameCmd->AvailableForStates(G4State_PreInit, G4State_Idle, G4State_GeomClosed
			       ,G4State_EventProc);
}


DetectorMessenger::~DetectorMessenger()
{
  delete isWaterCmd;
  delete BirksCmd;
  delete FnameCmd;
  delete UpdateCmd;
  delete BeamHeightCmd;
  delete PMTGapCmd;
  delete detDir;
  delete Dir;
}


void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == UpdateCmd)
    { Detector->UpdateGeometry(); }

  if( command == BeamHeightCmd)
    { Detector->SetBeamHeight(BeamHeightCmd->GetNewDoubleValue(newValue));}

  if( command == PMTGapCmd)
    { Detector->SetPMTGap(PMTGapCmd->GetNewDoubleValue(newValue));}

  if( command == isWaterCmd)
    { Detector->SetWater(isWaterCmd->GetNewBoolValue(newValue));}

  if( command == WbLSfractionCmd)
    { Detector->SetWbLSfraction(WbLSfractionCmd->GetNewDoubleValue(newValue));}

  if( command == ManualYieldCmd)
    { Detector->
	SetManualYield(true, ManualYieldCmd->GetNewDoubleValue(newValue));}

  if( command == CalculateYieldCmd)
    { Detector->SetManualYield(false,105.);}

  if( command == BirksCmd)
    { Detector->SetBirksConstant(BirksCmd->GetNewDoubleValue(newValue));}

  if( command == FnameCmd){
    RunAction* myRunAction =
      (RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
    myRunAction->SetFileName(newValue);
  }
}
