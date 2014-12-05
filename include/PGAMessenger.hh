#ifndef PGAMessenger_hh
#define PGAMessenger_hh 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

class PGAMessenger: public G4UImessenger{

public:
  PGAMessenger(PrimaryGeneratorAction*);
  ~PGAMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  PrimaryGeneratorAction* PGA;
  G4UIdirectory* Dir;
  G4UIdirectory* PGADir;
  G4UIcmdWithADoubleAndUnit* YDisplacementCmd;

};

#endif
