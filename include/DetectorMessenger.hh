#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithAString;

//Inherits from G4UImessenger
class DetectorMessenger: public G4UImessenger
{
  public:
  DetectorMessenger(DetectorConstruction* );
  ~DetectorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
  private:
  DetectorConstruction* Detector;
  
  G4UIdirectory*             Dir;
  G4UIdirectory*             detDir;
  G4UIcmdWithADoubleAndUnit* BeamHeightCmd;
  G4UIcmdWithABool* isWaterCmd;
  G4UIcmdWithADoubleAndUnit* PMTGapCmd;
  G4UIcmdWithADouble* ManualYieldCmd;
  G4UIcmdWithoutParameter* CalculateYieldCmd;
  G4UIcmdWithoutParameter*   UpdateCmd;
  G4UIcmdWithADouble*        WbLSfractionCmd;
  G4UIcmdWithADouble* BirksCmd;
  G4UIcmdWithAString* FnameCmd;
};

#endif
