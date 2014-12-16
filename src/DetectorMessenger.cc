//Detector Messenger Class controls UI Commands for adjusting detector params
#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
//#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
//#include "G4UIcmdWithADouble.hh"


DetectorMessenger::DetectorMessenger(
                                           DetectorConstruction* Det)
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
  BeamHeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle,G4State_GeomClosed,G4State_EventProc);  

  PMTGapCmd = new G4UIcmdWithADoubleAndUnit("/CustomCommands/det/setPMTGap",this);  
  PMTGapCmd->SetGuidance("Set gap between PMT and UVT Acrylic");
  PMTGapCmd->SetParameterName("Size",false);
  PMTGapCmd->SetRange("Size>=0.");
  PMTGapCmd->SetUnitCategory("Length");
  PMTGapCmd->AvailableForStates(G4State_PreInit,G4State_Idle,G4State_GeomClosed,G4State_EventProc);  


  //UGCompCCmd = new G4UIcmdWithADouble("/CustomCommands/det/setUGCompC", this);
  //UGCompCCmd->SetGuidance("Set percentage carbon of UG Scintillant, value must be between 0 and 1");
  //UGCompCCmd->AvailableForStates(G4State_PreInit,G4State_Idle,G4State_GeomClosed,G4State_EventProc);


  //ScintillantSetCmd = new G4UIcmdWithAString("/CustomCommands/det/setScintillant",this);  
  //ScintillantSetCmd->SetGuidance("Set Scintillant");
  //ScintillantSetCmd->SetGuidance("This Command was cut for causing problems and DOES NOT WORK!");
  //ScintillantSetCmd->SetParameterName("choice",false);
  //ScintillantSetCmd->AvailableForStates(G4State_PreInit,G4State_Idle,G4State_GeomClosed,G4State_EventProc);  

  UpdateCmd = new G4UIcmdWithoutParameter("/CustomCommands/det/update",this);
  UpdateCmd->SetGuidance("Update calorimeter geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_PreInit,G4State_Idle,G4State_GeomClosed,G4State_EventProc);
      
}


DetectorMessenger::~DetectorMessenger()
{
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

}
