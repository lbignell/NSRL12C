
//once again, fairly simple - copied off the UOW tute
#include "PrimaryGeneratorAction.hh"
#include "TRandom3.h"
#include "TROOT.h"

//include class definition for the particle gun
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"

//include header file for particle 
#include "G4Proton.hh"
//#include "G4Electron.hh"
#include "Randomize.hh"
#include "G4Event.hh"
#define _USE_MATH_DEFINES
#include <math.h>

#include "PGAMessenger.hh"

using namespace std;

void PrimaryGeneratorAction::SetYDisplacement(G4double theYDisplacement){
  YDisplacement = theYDisplacement;
}

G4double PrimaryGeneratorAction::GetYDisplacement(){return YDisplacement;}

PrimaryGeneratorAction::PrimaryGeneratorAction(){
  //Initialize the YDisplacement variable
  YDisplacement = 0;
  PGAMess = new PGAMessenger(this);


//we need to use dynamic memory allocation for the G4ParticleGun object
  gun = new G4ParticleGun(1);
  gun->SetParticleDefinition(G4Proton::ProtonDefinition());
  G4double EnergySigma = 0.3*MeV;
  G4double BeamEn = 0.475*GeV;
  G4double EnSpread = 
    EnergySigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());
  gun->SetParticleEnergy(BeamEn+EnSpread);
  

  //y = vertical direction; x = horizontal direction.
  //Get a Gaussian random number using the Box-Muller method.
  G4double beamsigma = 20*mm;
  G4double X =
    beamsigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());
  G4double Y =
    beamsigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());

  //Ensure beam is ~going to hit the hodoscope
  while(abs(X)>10*mm)
    {X = beamsigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());}
  while(abs(Y)>10*mm)
    {Y = beamsigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());}

  //Assume beam window is 30 cm from the first vial's centre
  gun->SetParticlePosition(G4ThreeVector(X,Y + YDisplacement,-570*cm));

  gun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
  //momentum directional cosines


}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
//free the dynamically allocated memory
  delete gun;

}

//this method will be called by the RunManager at the beginning of each particle history
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  
  //Need to randomise the beam energy.
  //G4double EnergySigma = 0.3*MeV;
  //G4double BeamEn = 0.475*GeV;
  //G4double EnSpread = 
  //EnergySigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());
  //gun->SetParticleEnergy(BeamEn+EnSpread);

  //Get a Gaussian random number using the Box-Muller method.
  G4double beamsigma = 20*mm;
  G4double X =
    beamsigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());
  G4double Y =
    beamsigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());

  //Ensure beam is ~going to hit the hodoscope
  while(abs(X)>10*mm)
    {X = beamsigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());}
  while(abs(Y)>10*mm)
    {Y = beamsigma*sqrt(-2*log(G4UniformRand()))*cos(2*M_PI*G4UniformRand());}

  //Assume beam window is 30 cm from the first vial's centre
  gun->SetParticlePosition(G4ThreeVector(X,Y+YDisplacement,-570*cm));

  //hopefully G4UniformRand gives a new random number each call.

  gun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
  //momentum directional cosines


  //this gets the particle firing
  gun->GeneratePrimaryVertex(anEvent);

}
