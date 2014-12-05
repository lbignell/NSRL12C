/*G4VSensitiveDetector is an abstract base class which represents a detector. The principal mandate of a sensitive detector is the construction of hit objects using information from steps along a particle track. The ProcessHits() method of G4VSensitiveDetector  performs this task using G4Step objects as input*/
#ifndef SDHodo_h
#define SDHodo_h 1

#include "G4VSensitiveDetector.hh"
#include "G4Run.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class SDHodo : public G4VSensitiveDetector
{

public:
    SDHodo(G4String name);
    ~SDHodo();

    /*This method is invoked at the beginning of each event. The argument of this method is an object of the G4HCofThisEvent class. Hits collections, where hits produced in this particular event are stored, can be associated to the G4HCofThisEvent object in this method. The hits collections associated with theG4HCofThisEvent  object during this method can be used for ``during the event processing'' digitization.G4Event has a G4HCofThisEvent class object, that is a container class of collections of hits. Hits collections are stored by their pointers, of the type of the base class.*/
    void Initialize(G4HCofThisEvent*HCE);
    /*This method is invoked by G4SteppingManager when a step is composed in the G4LogicalVolume which has the pointer to this sensitive detector. The firstargument of this method is a G4Step  object of the current step. The second argument is a G4TouchableHistory object for the ``Readout geometry'' describedin the next section. The second argument is NULL for the case ``Readout geometry'' is not assigned to this sensitive detector. In this method, one or moreG4VHit objects should be constructed if the current step is meaningful for your detector.*/
    G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
    /*This method is invoked at the end of each event. The argument of this methd is the same object as the previous method. Hits collections occasionally created in your sensitive detector can be associated to the G4HCofThisEvent object.*/
    void EndOfEvent(G4HCofThisEvent*HCE);

  //This function will accept an energy, apply Birk's correction for Ionisation
  //quenching, and return the quenched energy.

  G4double GetEdep();
  G4bool HadPrimary();

private:

  G4bool HazPrimary;
  G4double Edep;

};

#endif
