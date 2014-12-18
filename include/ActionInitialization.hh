#ifndef ActionInitialization_hh
#define ActionInitialization_hh 1

#include "G4VUserActionInitialization.hh"

class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization
{
public:
  ActionInitialization(DetectorConstruction* detector);
  virtual ~ActionInitialization();
  virtual void BuildForMaster() const;
  virtual void Build() const;

private:
  DetectorConstruction* myDetector;
};
#endif
