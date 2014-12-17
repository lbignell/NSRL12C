//preprocessor directives to prevent multiple includes of the same file
#ifndef DetectorConstruction_H 
#define DetectorConstruction_H 1

//preprocessor directive to include the header file for the base class
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

using namespace std;

//class declaration, we don't need to tell the compiler how big it is, yet
class G4VPhysicalVolume;
class DetectorMessenger;

//this is the user defined class that inherits behaviour from the virtual base class of the geant4 toolkit
class DetectorConstruction : public G4VUserDetectorConstruction{

public:
  //declare the constructor for this class
    DetectorConstruction();
  //declare the destructor of this class
    ~DetectorConstruction();

  //the one method that MUST be defined in this class, it is called "Construct",
  //takes no arguments, and returns a pointer to a G4VPhysicalVolume
    G4VPhysicalVolume* Construct();

  G4double BeamHeight;
  G4double PMTGap;
  DetectorMessenger* DetMess;
  bool isWater;
  G4VPhysicalVolume* physical_world;
  double WbLSfraction;

  void SetWbLSfraction(double);
  void SetWater(bool);
  void SetBeamHeight(G4double);
  G4double GetBeamHeight();
  void UpdateGeometry();
  void SetPMTGap(G4double);
  G4double GetPMTGap();
  vector< vector< double > > QEdata;
  vector< vector< double > >& GetQEdata();
  vector< vector< double > > QYdata;
  vector< vector< double > >& GetQYdata();

  //This method will read out the file specified by G4string and return the
  //pointer to a vector of vector of doubles (containing the data).
  void GetOptInfo(FILE*, G4double);

private:
  vector< vector < double > > thedata;

};
#endif
