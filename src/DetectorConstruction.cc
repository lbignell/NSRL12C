//This will be a simple goemetry just to check and see if I can get it working

#include "DetectorConstruction.hh"
//include header files for all classes used in the methods
#include "globals.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4RotationMatrix.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Isotope.hh"
#include "G4SystemOfUnits.hh"
#include <math.h>

//for sensitive detector definition
#include "SensitiveDetector.hh"
#include "SDHodo.hh"
#include "PMTwinUp.hh"
#include "PMTwinDown.hh"
#include "G4SDManager.hh"

#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "DetectorMessenger.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4LogicalBorderSurface.hh"

using namespace std;

//constructor / destructor do nothing
DetectorConstruction::DetectorConstruction(){
  BeamHeight = 0.*mm;
  PMTGap = 1*mm;
  DetMess = new DetectorMessenger(this);
  //QEdata.clear();
}

DetectorConstruction::~DetectorConstruction(){ 

}

void DetectorConstruction::SetBeamHeight(G4double value){
  BeamHeight = value;
}

G4double DetectorConstruction::GetBeamHeight(){
  return BeamHeight;
}

void DetectorConstruction::SetPMTGap(G4double value){
  PMTGap = value;
}

G4double DetectorConstruction::GetPMTGap(){
  return PMTGap;
}

vector< vector< double > >& DetectorConstruction::GetQEdata(){
  return QEdata;
}

vector< vector< double > >& DetectorConstruction::GetQYdata(){
  return QYdata;
}

void DetectorConstruction::UpdateGeometry(){
  //My original code.
  //G4RunManager::GetRunManager()->DefineWorldVolume(Construct(), true);
  //G4RunManager::GetRunManager()->GeometryHasBeenModified();


  //Code taken from:
  //http://hypernews.slac.stanford.edu/HyperNews/geant4/get/eventtrackmanage/970/1/2.html?inline=-1
  //Delete existing geom.
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
 
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  //G4RunManager::GetRunManager->PhysicsHasBeenModified();
  //G4RegionStore::GetInstance()->UpdateMaterialList(experimentalHall_phys);

}

G4VPhysicalVolume* DetectorConstruction::Construct(){
/* materials definition */

/*define the elements that will be used in our materials*/
//define hydrogen 
  G4double A = 1.01 * g/mole;
  G4double Z = 1;
  G4Element* elH = new G4Element ("Hydrogen", "H", Z, A);

  //define oxygen
  A = 16.0 * g/mole;
   Z = 8;
  G4Element* elO = new G4Element ("Oxygen", "O", Z, A);

  //define nitrogen
  A = 14.0 * g/mole;
  Z = 7;
  G4Element* elN = new G4Element("Nitrogen", "N", Z, A);

  //define carbon
  A = 12.0107 * g/mole;
  Z = 6;
  G4Element* elC = new G4Element("Carbon", "C", Z, A);

  //define Silicon
  A = 28.086 * g/mole;
  Z = 14;
  G4Element* elSi = new G4Element("Silicon", "Si", Z, A);

  //define sodium
  A = 22.990 * g/mole;
  Z = 11;
  G4Element* elNa = new G4Element("Sodium", "Na", Z, A);

  //define Calcium
  A = 40.08 * g/mole;
  Z = 20;
  G4Element* elCa = new G4Element("Calcium", "Ca", Z, A);

  //define Phosphorus
  A = 30.973761*g/mole;
  Z = 15;
  G4Element* elP = new G4Element("Phosphorus", "P", Z, A);

  //define Sulphur
  A = 32.065*g/mole;
  Z = 16;
  G4Element* elS = new G4Element("Sulphur", "S", Z, A);

  //define Aluminium
  A = 26.961538*g/mole;
  Z = 13;
  G4Element* elAl = new G4Element("Aluminium", "Al",Z,A);

  //define Iron
  A = 55.845*g/mole;
  Z = 26;
  G4Element* elFe = new G4Element("Iron", "Fe",Z,A);
 
  //Define Copper
  A = 63.546*g/mole;
  Z = 29;
  G4Element* elCu = new G4Element("Copper", "Cu",Z,A);

  //Define Manganese
  A = 54.938045*g/mole;
  Z = 25;
  G4Element* elMn = new G4Element("Manganese", "Mn", Z, A);

  //Define Magnesium
  A = 24.3050*g/mole;
  Z = 12;
  G4Element* elMg = new G4Element("Magnesium", "Mg", Z, A);

  //Define Titanium
  A = 47.867*g/mole;
  Z = 22;
  G4Element* elTi = new G4Element("Titanium", "Ti", Z, A);

  //Define Chromium
  A = 51.9961*g/mole;
  Z = 24;
  G4Element* elCr = new G4Element("Chromium", "Cr",Z,A);

  //Define Zinc
  A = 65.409*g/mole;
  Z = 30;
  G4Element* elZn = new G4Element("Zinc", "Zn",Z,A);

  //Define Boron
  A = 10.811*g/mole;
  Z = 5;
  G4Element* elB = new G4Element("Boron", "B",Z,A);

  //Define Potassium
  A = 39.0983*g/mole;
  Z = 19;
  G4Element* elK = new G4Element("Potassium", "K",Z,A);

  //constructor of the G4Material class requires arguments: string 
  //conG4OpticalSurfacetaining name of material, density, number of elements
  G4Material* water = new G4Material("water", 1.0 * g/cm3, 2);
  water->AddElement(elH,2);
  water->AddElement(elO,1);

  /*now we define air for the world volume*/
  G4Material* air = new G4Material("dry air", 0.01*mg/cm3, 2, kStateGas, 293*kelvin, 1*atmosphere);
  //we can also specify the percentage (by mass) composition
  air->AddElement(elN, 75*perCent);
  air->AddElement(elO, 25*perCent);

  //High Density Polyethylene
  //G4Material* HDPE = new G4Material("HD Poly-Ethylene", 0.941*g/cm3, 2);
  //G4Material* HDPE = new G4Material("HD Poly-Ethylene", 0.93*g/cm3, 2);
  G4Material* HDPE = new G4Material("HD Poly-Ethylene", 0.97*g/cm3, 2);
  HDPE->AddElement(elC, 33.33333*perCent);
  HDPE->AddElement(elH, 66.66667*perCent);

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* water_nist = nist->FindOrBuildMaterial("G4_WATER");
  G4Material* air_nist = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* HDPE_nist = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* Polystyrene_nist = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
  G4Material* Acrylic_nist = nist->FindOrBuildMaterial("G4_POLYACRYLONITRILE");
  G4Material* glass_nist = nist->FindOrBuildMaterial("G4_Pyrex_Glass");
  G4Element* C_nist = nist->FindOrBuildElement("C");
  G4Element* H_nist = nist->FindOrBuildElement("H");
  G4Material* PFTE_white_nist = nist->FindOrBuildMaterial("G4_TEFLON");
  G4Material* PFTE_black_nist = nist->FindOrBuildMaterial("G4_TEFLON");


  G4Material* Scint = new G4Material("LABscintillator", 0.86*g/cm3, 2);
  //Scint->AddElement(C_nist, (18/(18+30)));
  //Scint->AddElement(H_nist, (30/(18+30)));
  Scint->AddElement(C_nist, 18*12);
  Scint->AddElement(H_nist, 30*1);


  //Make WbLS as used in expt.
  G4double WbLSfraction = 0.0099;
  G4double WbLSdensity = (water_nist->GetDensity())*(1-WbLSfraction) + 
    (Scint->GetDensity())*WbLSfraction;
  G4Material* WbLS = new G4Material("WbLS", WbLSdensity, 2);
  //kStateLiquid, 293*kelvin, 1*atmosphere);
  WbLS->AddMaterial(water_nist, (1-WbLSfraction));
  WbLS->AddMaterial(Scint, WbLSfraction);

  //Aluminium Alloy used in the walls Alloy #6063
  G4Material* AlAlloy=new G4Material("Al Alloy", 2680.*kg/m3, 9, kStateSolid);
  //Adding elements in this way seems pointless now but is useful for later
  AlAlloy->AddElement(elAl, 98.5*perCent);
  AlAlloy->AddElement(elSi, 0.40*perCent);
  AlAlloy->AddElement(elFe, 0.175*perCent);
  AlAlloy->AddElement(elCu, 0.05*perCent);
  AlAlloy->AddElement(elMn, 0.05*perCent);
  AlAlloy->AddElement(elMg, 0.675*perCent);
  AlAlloy->AddElement(elCr, 0.05*perCent);
  AlAlloy->AddElement(elZn, 0.05*perCent);
  AlAlloy->AddElement(elTi, 0.05*perCent);



  //Getting data to fill the acrylic MPT.
  G4MaterialPropertiesTable* MPTacrylic = new G4MaterialPropertiesTable();

  //Test out the capability of the function to read out the data from the opt
  //property files.
  //cout << "Reading data from optical property file" << G4endl;
  FILE* FilePtr = fopen("/home/lbignell/ScintData/acrylic_abslength.vec", "r");
  //FILE* FilePtr = fopen("r7723.vec", "r");
  cout << "File open! Pointer = " << FilePtr << G4endl;
  //vector < vector < double > >& thedata;
  if(FilePtr!=0){
    //call the function
    GetOptInfo(FilePtr, 1*mm);
  }
  else{
    G4cout << "ERROR: could not open file!" << G4endl;
  }

  G4cout << "Successfully read file!" << G4endl;
  G4int cols = thedata.size();
  G4cout << "Number of columns = " << cols << G4endl;
  for(int i=0; i < cols; i++){
    G4cout << "Number of entries in column # " << i << " = "
	   << thedata.at(i).size() << G4endl;
  }


  //Writing data to material properties table. Arguments: variable name, photon
  //energy, property values, number of entries.
  //Geant4 requires that the optical properties be passed as arrays, so I'll 
  //copy the vectors to arrays.
  const G4int size1 = thedata.at(0).size();
  G4double En1[size1];
  //std::copy(thedata.at(0).begin(), thedata.at(0).end(), En1);
  G4double AbsLen1[size1];//can assume vectors are same size
  //std::copy(thedata.at(1).begin(), thedata.at(1).end(), AbsLen1);
  for(int i = 0; i<size1; i++){
    En1[i] = thedata.at(0).at(i);
    AbsLen1[i] = thedata.at(1).at(i);
    //G4cout << "RINDEX[" << i << "] = " << Rindex2[size2] << G4endl;
  }
  MPTacrylic->AddProperty("ABSLENGTH", En1, AbsLen1, size1);

  thedata.clear();

  //Read out the acryling refractive index data
  FilePtr = fopen("/home/lbignell/ScintData/acrylic_rindex.vec", "r");
  if(FilePtr!=0){
    GetOptInfo(FilePtr, 1);
  }
  else{
    G4cout << "ERROR: Could not open file!" << G4endl;
  }
  G4cout << "Successfully read file!" << G4endl;
  cols = thedata.size();
  G4cout << "Number of columns = " << cols << G4endl;
  for(int i=0; i < cols; i++){
    G4cout << "Number of entries in column # " << i << " = "
	   << thedata.at(i).size() << G4endl;
  }

  const G4int size2 = thedata.at(0).size();
  G4double En2[size2];
  //std::copy(thedata.at(0).begin(), thedata.at(0).end(), En2);
  G4double Rindex2[size2];
  for(int i = 0; i<size2; i++){
    En2[i] = thedata.at(0).at(i);
    Rindex2[i] = thedata.at(1).at(i);
    //G4cout << "RINDEX[" << i << "] = " << Rindex2[size2] << G4endl;
  }
  //std::copy(thedata.at(1).begin(), thedata.at(1).end(), Rindex2);
  MPTacrylic->AddProperty("RINDEX", En2, Rindex2, size2);

  //MPTacrylic->AddProperty("FASTCOMPONENT",PhotonEnergy, ScintilFast,     nEntries);
  //MPTacrylic->AddProperty("SLOWCOMPONENT",PhotonEnergy, ScintilSlow,     nEntries);
  
  //MPTacrylic->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  //MPTacrylic->AddConstProperty("RESOLUTIONSCALE",1.0);
  //MPTacrylic->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  //MPTacrylic->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  //MPTacrylic->AddConstProperty("YIELDRATIO",0.8);
  
  Acrylic_nist->SetMaterialPropertiesTable(MPTacrylic);

  G4MaterialPropertiesTable* MPTwater = new G4MaterialPropertiesTable();
  G4MaterialPropertiesTable* MPTWbLS = new G4MaterialPropertiesTable();

  thedata.clear();
  //FilePtr = fopen("/home/lbignell/ScintData/water_abslength.vec", "r");
  //FilePtr = fopen("/home/lbignell/ScintData/WaterAbsSeg_FULL.csv", "r");
  FilePtr = fopen("/home/lbignell/ScintData/WaterAbsSeg_PARTIAL2.csv", "r");

  if(FilePtr!=0){
    GetOptInfo(FilePtr, 1*mm);
  }
  else{
    G4cout << "ERROR: Could not open file!" << G4endl;
  }
  G4cout << "Successfully read file!" << G4endl;
  cols = thedata.size();
  G4cout << "Number of columns = " << cols << G4endl;
  for(int i=0; i < cols; i++){
    G4cout << "Number of entries in column # " << i << " = "
	   << thedata.at(i).size() << G4endl;
  }

  G4cout << "thedata.at(0).at(0) = " << thedata.at(0).at(0) << G4endl;
  G4cout << "thedata.at(0).at(1) = " << thedata.at(0).at(1) << G4endl;
  G4cout << "thedata.at(1).at(0) = " << thedata.at(1).at(0) << G4endl;
  G4cout << "thedata.at(1).at(1) = " << thedata.at(1).at(1) << G4endl;

  const G4int size3 = thedata.at(0).size();
  G4double En3[size3];
  //std::copy(thedata.at(0).begin(), thedata.at(0).end(), En3);
  G4double AbsLen3[size3];
  //std::copy(thedata.at(1).begin(), thedata.at(1).end(), AbsLen3);
  for(int i = 0; i<size3; i++){
    En3[i] = thedata.at(0).at(i);
    AbsLen3[i] = thedata.at(1).at(i);
    //G4cout << "RINDEX[" << i << "] = " << Rindex2[size2] << G4endl;
  }
  MPTwater->AddProperty("ABSLENGTH", En3, AbsLen3, size3);
  MPTWbLS->AddProperty("ABSLENGTH", En3, AbsLen3, size3);

  thedata.clear();
  //FilePtr = fopen("/home/lbignell/ScintData/water_rindex.vec", "r");
  //FilePtr = fopen("/home/lbignell/ScintData/water_rindex_edit.vec", "r");
  //FilePtr = fopen("/home/lbignell/ScintData/WaterRindexSeg_FULL.csv", "r");
  FilePtr = fopen("/home/lbignell/ScintData/WaterRindexSeg_PARTIAL2.csv", "r");
  //FilePtr = fopen("/home/lbignell/ScintData/WaterRindexSeg_Sub10pc.csv", "r");

if(FilePtr!=0){

    GetOptInfo(FilePtr, 1);
  }
  else{
    G4cout << "ERROR: Could not open file!" << G4endl;
  }
  G4cout << "Successfully read file!" << G4endl;
  cols = thedata.size();
  G4cout << "Number of columns = " << cols << G4endl;
  for(int i=0; i < cols; i++){
    G4cout << "Number of entries in column # " << i << " = "
	   << thedata.at(i).size() << G4endl;
  }

  G4cout << "thedata.at(0).at(0) = " << thedata.at(0).at(0) << G4endl;
  G4cout << "thedata.at(0).at(1) = " << thedata.at(0).at(1) << G4endl;
  G4cout << "thedata.at(1).at(0) = " << thedata.at(1).at(0) << G4endl;
  G4cout << "thedata.at(1).at(1) = " << thedata.at(1).at(1) << G4endl;


  const G4int size4 = thedata.at(0).size();
  G4double En4[size4];
  //std::copy(thedata.at(0).begin(), thedata.at(0).end(), En4);
  G4double Rindex4[size4];
  //std::copy(thedata.at(1).begin(), thedata.at(1).end(), Rindex4);
  for(int i = 0; i<size4; i++){
    En4[i] = thedata.at(0).at(i);
    Rindex4[i] = thedata.at(1).at(i);
    //G4cout << "RINDEX[" << i << "] = " << Rindex4[i] << G4endl;
  }
  MPTwater->AddProperty("RINDEX", En4, Rindex4, size4);
  MPTWbLS->AddProperty("RINDEX", En4, Rindex4, size4);

  G4MaterialPropertyVector* theRindex = MPTwater->GetProperty("RINDEX");
  G4cout << "Rindex max value = " << theRindex->GetMaxValue() << G4endl;
  G4cout << "Rindex min value = " << theRindex->GetMinValue() << G4endl;
  G4cout << "Rindex at 200 nm (6.1992 eV): "
	 << theRindex->Value(6.1992*eV) << G4endl;
  G4cout << "MinLowEdgeEnergy = " << theRindex->GetMinLowEdgeEnergy() << G4endl;
  G4cout << "MaxLowEdgeEnergy = " << theRindex->GetMaxLowEdgeEnergy() << G4endl;

  //This is the WLS photon energy spectrum.
  //It has not been normalised.
  thedata.clear();
  FilePtr = fopen("/home/lbignell/ScintData/WbLSem.csv", "r");
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSemExtrap.csv", "r");
  //FilePtr = fopen("/home/lbignell/ScintData/scintillator_fastcomponent.vec", "r");
  if(FilePtr!=0){
    GetOptInfo(FilePtr, 1);
  }
  else{
    G4cout << "ERROR: Could not open file!" << G4endl;
  }
  G4cout << "Successfully read file!" << G4endl;
  cols = thedata.size();
  G4cout << "Number of columns = " << cols << G4endl;
  for(int i=0; i < cols; i++){
    G4cout << "Number of entries in column # " << i << " = "
	   << thedata.at(i).size() << G4endl;
  }
  
  const G4int size5 = thedata.at(0).size();
  G4double En5[size5];
  //std::copy(thedata.at(0).begin(), thedata.at(0).end(), En5);
  G4double WLSEm5[size5];
  //std::copy(thedata.at(1).begin(), thedata.at(1).end(), WLSEm5);
  for(int i = 0; i<size5; i++){
    En5[i] = thedata.at(0).at(i);
    WLSEm5[i] = thedata.at(1).at(i);
    //G4cout << "RINDEX[" << i << "] = " << Rindex2[size2] << G4endl;
  }
  MPTWbLS->AddProperty("WLSCOMPONENT", En5, WLSEm5, size5);


  //This is the Scint photon energy spectrum.
  //It has not been normalised.
  thedata.clear();
  FilePtr = fopen("/home/lbignell/ScintData/WbLSFluorSpecNew.csv", "r");//New data taken on the fluor spec.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSem.csv", "r");
  //FilePtr = fopen("/home/lbignell/ScintData/scintillator_fastcomponent.vec", "r");
  if(FilePtr!=0){
    GetOptInfo(FilePtr, 1);
  }
  else{
    G4cout << "ERROR: Could not open file!" << G4endl;
  }
  G4cout << "Successfully read file!" << G4endl;
  cols = thedata.size();
  G4cout << "Number of columns = " << cols << G4endl;
  for(int i=0; i < cols; i++){
    G4cout << "Number of entries in column # " << i << " = "
	   << thedata.at(i).size() << G4endl;
  }


  //The relevant property name is "FASTCOMPONENT".
  const G4int size6 = thedata.at(0).size();
  G4double En6[thedata.at(0).size()];
  std::copy(thedata.at(0).begin(), thedata.at(0).end(), En6);
  G4double ScintEm6[thedata.at(1).size()];
  std::copy(thedata.at(1).begin(), thedata.at(1).end(), ScintEm6);
  for(int i = 0; i<size6; i++){
    En6[i] = thedata.at(0).at(i);
    ScintEm6[i] = thedata.at(1).at(i);
    //G4cout << "RINDEX[" << i << "] = " << Rindex2[size2] << G4endl;
  }

  //G4MaterialPropertiesTable* Scnt_MPT = new G4MaterialPropertiesTable();

  MPTWbLS->AddProperty("FASTCOMPONENT", En6, ScintEm6, size6);
  //Scnt_MPT->AddProperty("SLOWCOMPONENT", Scnt_PP, Scnt_SLOW, NUMENTRIES);

  MPTWbLS->AddConstProperty("SCINTILLATIONYIELD", 100./MeV);
  //The resolution yield is indeterminate. It will affect the breadth of the
  //photon number distribution, and can therefore be tuned to the measured value
  //if that makes sense.
  MPTWbLS->AddConstProperty("RESOLUTIONSCALE", 2.0);
  MPTWbLS->AddConstProperty("FASTTIMECONSTANT",  1.*ns);
  //Scnt_MPT->AddConstProperty("SLOWTIMECONSTANT", 10.*ns);
  MPTWbLS->AddConstProperty("YIELDRATIO", 1.);

  //Scnt->SetMaterialPropertiesTable(Scnt_MPT);



  water_nist->SetMaterialPropertiesTable(MPTwater);
  
  //Now set the properties for air...
  const G4int nEntries = 32 + 26;
  G4double PhotonEnergy[nEntries] =
    { 1.5*eV, 1.6*eV, 1.7*eV, 1.8*eV, 1.9*eV,
      2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV,
      4.2*eV, 4.3*eV, 4.4*eV, 4.5*eV, 4.6*eV,
      4.7*eV, 4.8*eV, 4.9*eV, 5.0*eV, 5.1*eV,
      5.2*eV, 5.3*eV, 5.4*eV, 5.5*eV, 5.6*eV,
      5.7*eV, 5.8*eV, 5.9*eV, 6.0*eV, 6.1*eV,
      6.2*eV};

  //Now set the properties for air...
  //extra values have been added arbritrarily
  G4double RindexAir[nEntries] =
    { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00};

  G4double AbsLenAir[nEntries] =
    { 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km,
      1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km,
      1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km,
      1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km,
      1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km,
      1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km,
      1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km,
      1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km, 1.00*km,
      1.00*km, 1.00*km};

  G4MaterialPropertiesTable* MPTair = new G4MaterialPropertiesTable();
  MPTair->AddProperty("RINDEX", PhotonEnergy, RindexAir, nEntries);
  MPTair->AddProperty("ABSLENGTH", PhotonEnergy, AbsLenAir, nEntries);

  air_nist->SetMaterialPropertiesTable(MPTair);


  //Calculate the refractive index of fused silica (from 
  //http://refractiveindex.info/legacy/?group=GLASSES&material=F_SILICA
  //).
  G4double RindexSilica[nEntries];
  for(int i = 0; i<nEntries; i++){
    //calculate the wavelength in micrometers.
    G4double WLum = (1239.84187/PhotonEnergy[i])/1000;
    RindexSilica[i] =
      sqrt( 1 +
	    (0.6961663*WLum*WLum)/(WLum*WLum-0.0684043*0.0684043) +
	    (0.4079426*WLum*WLum)/(WLum*WLum-0.1162414*0.1162414) +
	    (0.8974794*WLum*WLum)/(WLum*WLum-9.896161*9.896161) );
  }
  
  G4double AbsLenSilica[nEntries] =
    { 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m,
      1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m,
      1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m,
      1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m,
      1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m,
      1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m,
      1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m,
      1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m, 1.00*m,
      1.00*m, 1.00*m};

  G4MaterialPropertiesTable* MPTsilica = new G4MaterialPropertiesTable();
  MPTsilica->AddProperty("RINDEX", PhotonEnergy, RindexSilica, nEntries);
  MPTsilica->AddProperty("ABSLENGTH", PhotonEnergy, AbsLenSilica, nEntries);

  glass_nist->SetMaterialPropertiesTable(MPTsilica);

  //Set the white teflon's optical properties.
  G4double Rindex_T1[nEntries];
  G4double AbsLen_T1[nEntries];
  G4double Refl_T1[nEntries];
  G4double TransmitEff_T1[nEntries];
  for(int i = 0; i<nEntries; i++){
    Rindex_T1[i] = 1.36;
    AbsLen_T1[i] = 4*cm;
    Refl_T1[i] = 0.9;//0.5% reflectance
    //    TransmitEff_T1[i] = 0.5;
  }

  G4MaterialPropertiesTable* MPT_T1 = new G4MaterialPropertiesTable();
  MPT_T1->AddProperty("REFLECTIVITY", PhotonEnergy, Refl_T1, nEntries);
  //MPT_T1->AddProperty("EFFICIENCY", PhotonEnergy, TransmitEff_T1, nEntries);
  MPT_T1->AddProperty("RINDEX", PhotonEnergy, Rindex_T1, nEntries);
  MPT_T1->AddProperty("ABSLENGTH", PhotonEnergy, AbsLen_T1, nEntries);

  PFTE_white_nist->SetMaterialPropertiesTable(MPT_T1);

  //Implement QE data grab here.
  thedata.clear();
  FilePtr = fopen("/home/lbignell/ScintData/r7723.vec", "r");
  if(FilePtr!=0){
    GetOptInfo(FilePtr, 1);
  }
  else{
    G4cout << "ERROR: Could not open file!" << G4endl;
  }
  G4cout << "Successfully read file!" << G4endl;
  cols = thedata.size();
  G4cout << "Number of columns = " << cols << G4endl;
  for(int i=0; i < cols; i++){
    G4cout << "Number of entries in column # " << i << " = "
	   << thedata.at(i).size() << G4endl;
  }
  QEdata = thedata;

  //Implement QY data grab here
  thedata.clear();
  //FilePtr = fopen("/home/lbignell/ScintData/QYDayaBay.csv", "r");
  //FilePtr = fopen("/home/lbignell/ScintData/QYDayaBayZeroBelow200nm.csv", "r");
  //FilePtr = fopen("/home/lbignell/ScintData/QYDayaBayZeroBelow211nm.csv", "r");
  //Double the QY for optimal agreement with expt.
  FilePtr = fopen("/home/lbignell/ScintData/QYDayaBayZeroBelow211nm_Double.csv", "r");
  if(FilePtr!=0){
    GetOptInfo(FilePtr, 1);
  }
  else{
    G4cout << "ERROR: Could not open file!" << G4endl;
  }
  G4cout << "Successfully read file!" << G4endl;
  cols = thedata.size();
  G4cout << "Number of columns = " << cols << G4endl;
  for(int i=0; i < cols; i++){
    G4cout << "Number of entries in column # " << i << " = "
	   << thedata.at(i).size() << G4endl;
  }
  QYdata = thedata;

  const G4int sizeQY = thedata.at(0).size();
  G4double EnQY[sizeQY];
  G4double WLDepQY[sizeQY];
  for(int i = 0; i<sizeQY; i++){
    EnQY[i] = thedata.at(0).at(i);
    WLDepQY[i] = thedata.at(1).at(i);
  }

  MPTWbLS->AddProperty("QUANTUMYIELD", EnQY, WLDepQY, sizeQY);


  //WbLS implementation:
  // -- Absorption  = water absorption.
  // -- Rindex = water Rindex.
  // -- WLS absorption = WbLSExtraAbs.
  // -- WLS emission = scint spec.
  // -- WLS time constant = 1*ns (arbitrary for now).

  //Now get the WbLS absorption
  thedata.clear();
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs.csv", "r");
  //Extrap to benzene abs data, then approximate benzene trend.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs_ExtrapExtrapDown.csv", "r");
  //Extrap to scaled benzene data, then follow water abs.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs_ExtrapFollowWater.csv", "r");
  //Extrap short wavelength absorption, then assume constant for shorter.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs_ExtrapFlat.csv", "r");
  //Extrap to unscaled benzene data, then remain constant.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs_ExtrapFlatScaleOnlyDilution.csv", "r");
  //Assume 4x concentration of abs data, benzene @ short w/L then flat
  //FilePtr = fopen("/home/lbignell/ScintData/WbLS4xAbs_BenzeneShortWLFlat.csv", "r");
  //Assume 8x concentration of abs data, benzene @ short w/L then flat
  //FilePtr = fopen("/home/lbignell/ScintData/WbLS8xAbs_BenzeneShortWLFlat.csv", "r");
  //Assume 100x concentration of abs data, benzene @ short w/L then flat
  //FilePtr = fopen("/home/lbignell/ScintData/WbLS100xAbs_BenzeneShortWLFlat.csv", "r");
  //Assume 1000x concentration of abs data, benzene @ short w/L then flat
  //FilePtr = fopen("/home/lbignell/ScintData/WbLS1000xAbs_BenzeneShortWLFlat.csv", "r");
  //Assume 10000x concentration of abs data, benzene @ short w/L then flat
  //FilePtr = fopen("/home/lbignell/ScintData/WbLS10000xAbs_BenzeneShortWLFlat.csv", "r");
  //Normalise to DAYA BAY water, extrap to Benzene@short w/L then flat.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbsDBwater_ExtrapFlatBenzene.csv", "r");
  //Normalise to 10x DAYA BAY water, extrap to Benzene@short w/L then flat.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs10xDBwater_ExtrapFlatBenzene.csv", "r");
  //Normalise to 100x DAYA BAY water, extrap to Benzene@short w/L then flat.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs100xDBwater_ExtrapFlatBenzene.csv", "r");
  //Normalise to 500x DAYA BAY water, extrap to Benzene@short w/L then flat.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs500xDBwater_ExtrapFlatBenzene.csv", "r");
  //Normalise to 500x DAYA BAY water, extrap to Benzene@short w/L then flat.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs700xDBwater_ExtrapFlatBenzene.csv", "r");
  //Normalise to 1000x DAYA BAY water, extrap to Benzene@short w/L then flat.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSExtraAbs1000xDBwater_ExtrapFlatBenzene.csv", "r");
  //2011 WbLS, normalise to DB water.
  //FilePtr = fopen("/home/lbignell/ScintData/2011WbLS_DBwater.csv", "r");
  //Corrected 2011 WbLS for fluorescence
  //FilePtr = fopen("/home/lbignell/ScintData/DBScintAbsorption2011_corrected.csv", "r");
  //Corrected 2011 WbLS for fluorescence, with correct units and DB water
  //FilePtr = fopen("/home/lbignell/ScintData/1pcScintAbsorption2011_corrected_2_140826.csv", "r");
  //New measurements of the 2011 WbLS in the 1 cm Cell.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSAbs_NewMeas_140908.csv", "r");
  //New measurements in 1 cm cell, corrected for fluorescence.
  //FilePtr = fopen("/home/lbignell/ScintData/WbLSAbs_NewMeas_Corrected_140908.csv", "r");
  FilePtr = fopen("/home/lbignell/ScintData/WbLSAbs_NewMeas_AllDilutions_140910.csv", "r");



  if(FilePtr!=0){
    GetOptInfo(FilePtr, 1*mm);
  }
  else{
    G4cout << "ERROR: Could not open file!" << G4endl;
  }
  G4cout << "Successfully read file!" << G4endl;
  cols = thedata.size();
  G4cout << "Number of columns = " << cols << G4endl;
  for(int i=0; i < cols; i++){
    G4cout << "Number of entries in column # " << i << " = "
	   << thedata.at(i).size() << G4endl;
  }

  const G4int size7 = thedata.at(0).size();
  G4double En7[size7];
  //std::copy(thedata.at(0).begin(), thedata.at(0).end(), En7);
  G4double Rindex7[size7];
  //std::copy(thedata.at(1).begin(), thedata.at(1).end(), Rindex7);
  for(int i = 0; i<size7; i++){
    En7[i] = thedata.at(0).at(i);
    Rindex7[i] = thedata.at(1).at(i);
    //G4cout << "RINDEX[" << i << "] = " << Rindex2[size2] << G4endl;
  }
  MPTWbLS->AddProperty("WLSABSLENGTH", En7, Rindex7, size7);

  G4MaterialPropertyVector* theWLSabs = MPTWbLS->GetProperty("WLSABSLENGTH");
  G4cout << "WLSAbs max value = " << theWLSabs->GetMaxValue() << G4endl;
  G4cout << "WLSAbs min value = " << theWLSabs->GetMinValue() << G4endl;
  G4cout << "WLSAbs at 200 nm (6.1992 eV): "
	 << theWLSabs->Value(6.1992*eV) << G4endl;
  G4cout << "WLSAbs at 165 nm (7.51419315151515 eV): "
	 << theWLSabs->Value(7.51419315151515*eV) << G4endl;
  G4cout << "WLSAbs at 700 nm (1.77120267142857 eV): "
	<< theWLSabs->Value(1.77120267142857*eV) << G4endl;
  G4cout << "MinLowEdgeEnergy = " << theWLSabs->GetMinLowEdgeEnergy() << G4endl;
  G4cout << "MaxLowEdgeEnergy = " << theWLSabs->GetMaxLowEdgeEnergy() << G4endl;


  MPTWbLS->AddConstProperty("WLSTIMECONSTANT", 1.*ns);

  WbLS->SetMaterialPropertiesTable(MPTWbLS);
  WbLS->GetIonisation()->SetBirksConstant(0.1*mm/MeV);


/*the volumes: */

  G4double worldx = 1 * m;
  G4double worldy = 1 * m;
  G4double worldz = 1 * m;

//the whole simulation must be contained within a "world" volume
//defining a volume requires definition of solid, logical, and physical volume
//solid volume is the shape, has dimensions
  G4Box* world = new G4Box("world_box", worldx, worldy, worldz);

//logical volume: has a solid volume as a member, a material, last 3???
  G4LogicalVolume* logical_world = new G4LogicalVolume(world, air_nist, "world_log", 0,0,0);

  //make the world invisible!
  logical_world->SetVisAttributes(G4VisAttributes::Invisible);

  //physical volume: G4PVPlacement class, represents a logical volume that is
  //placed somewhere in the mother volume.
  G4VPhysicalVolume* physical_world =
    new G4PVPlacement(0, G4ThreeVector(), logical_world, "world_phys",
		      0, false, 0, false);
  //The final argument is a flag to check the geometry for overlaps.


  //Define the geometry: H1  T1  H2  T2  H3. (I'm not modeling the VC).
  //H1, H2, and H3 are assumed to be perfectly aligned.
  //The beam centre is assumed to be centred on and normal to H1, H2, and H3.
  //(This means H1, H2, and H3 will need to move with the beam as I change the
  // beam height).
  //H1, H2, and H3 are assumed to be centred on the tubs.
  //I will add info on the PMTs once I get technical drawings.
  //THE ORIGIN will be placed in the centre of tub H1.
  //The following are based in scribblings in lab book; pasted on back of pg 29.
  //Gap between H1 centre and T1 centre:
  double GapH1T1 = ((224 - 214)*2.54)*cm;
  //Gap between T1 centre and H2 centre
  double GapT1H2 = ((242 - 224)*2.54)*cm;
  //Gap between H2 centre and T2 centre
  double GapH2T2 = ((250 - 242)*2.54)*cm;
  //Gap between T2 centre and H3 centre
  double GapT2H3 = ((261 - 250)*2.54)*cm;
  //Dimensions
  //All hodoscopes are 2x2x0.5 cm
  G4Box* hodo = new G4Box("hodoscope", 10*mm, 10*mm, 0.25*mm);

  G4LogicalVolume* H1_log =
    new G4LogicalVolume(hodo, Polystyrene_nist, "H1_log", 0,0,0);

  //G4RunManager to see which sensitive detectors there are
  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  //create SensitiveDetector object
  SDHodo* SDH1 = new SDHodo("H1_log");
  //pass new sensitive detector to manager
  SDman->AddNewDetector(SDH1);
  H1_log->SetSensitiveDetector(SDH1);

  G4VPhysicalVolume* H1_phys =
    new G4PVPlacement(0, G4ThreeVector(0, BeamHeight, -GapH1T1), H1_log,
		      "H1_phys", logical_world, false, 0, false);

  G4LogicalVolume* H2_log =
    new G4LogicalVolume(hodo, Polystyrene_nist, "H2_log", 0,0,0);
  
  //create SensitiveDetector object
  SDHodo* SDH2 = new SDHodo("H2_log");
  //pass new sensitive detector to manager
  SDman->AddNewDetector(SDH2);
  H2_log->SetSensitiveDetector(SDH2);

  G4VPhysicalVolume* H2_phys = 
    new G4PVPlacement(0, G4ThreeVector(0, BeamHeight, GapT1H2), H2_log,
		      "H2_phys", logical_world, false, 0, false);

  G4LogicalVolume* H3_log =
    new G4LogicalVolume(hodo, Polystyrene_nist, "H3_log", 0,0,0);
  
  //create SensitiveDetector object
  SDHodo* SDH3 = new SDHodo("H3_log");
  //pass new sensitive detector to manager
  SDman->AddNewDetector(SDH3);
  H3_log->SetSensitiveDetector(SDH3);

  G4VPhysicalVolume* H3_phys = 
    new G4PVPlacement(0, G4ThreeVector(0, BeamHeight,
				       (GapT1H2 + GapH2T2 + GapT2H3)),
		      H3_log,"H3_phys", logical_world, false, 0, false);


  //Define the Tub volumes:
  //A right cylinder; 6 inches diameter; 6 inches tall (both outer dimensions).
  //The wall thickness is 0.25 inches all around.
  //The dimensions of the Al are unknown, it looks to be ~10mm on inspection.
  //There is a hole in the top of each, centrally located and 2.215 inches diam.
  //This is filled with UVT acrylic; and there is a 2" PMT above this.
  //The black tub actually has a couple of screws in this UVT acrylic that
  //obstruct the PMT's view. I could model this as optically absorbing circles
  //on the UVT acrylic or as a lower PMT eff area for this tube. I think I'll go
  //with the latter.
  G4double TubOuterDiam = 6*2.54*cm;
  G4double TubHeight = 6*2.54*cm;
  G4double AlOuterDiam = TubOuterDiam + (2*1*cm);
  G4double AlHeight = TubHeight + (2*1*cm);
  G4double LiquidDiam = TubOuterDiam - (2*0.25*2.54*cm);
  G4double LiquidHeight = TubHeight - (2*0.25*2.54*cm);
  G4double UVTdiam = 2.215*2.54*cm;
  G4double T1UVTheight = (TubHeight - LiquidHeight)/2;
  G4double T1UVTdisp = (TubHeight - T1UVTheight)/2;
  G4double T2UVTheight = (AlHeight - LiquidHeight)/2;
  G4double T2UVTdisp = (AlHeight - T2UVTheight)/2;
  //G4double UVTinsensitiveDiam = 5*mm;

  //The tubs are normal to the beam direction, so I need to include a rotation.
  G4RotationMatrix* RotMat = new G4RotationMatrix();
  RotMat->rotateX(90*deg);

  //Create T1
  G4Tubs* Tub = new G4Tubs("Tub", 0, TubOuterDiam/2, TubHeight/2, 0, 360*deg);
  G4LogicalVolume* T1_log = new G4LogicalVolume(Tub, PFTE_white_nist, "T1_log",
						0,0,0);
  G4VPhysicalVolume* T1_phys =
    new G4PVPlacement(RotMat, G4ThreeVector(0, 0, 0), T1_log, "T1_phys",
		      logical_world, false, 0, false);

  //Create the liquid in T1 (it will need to be sensitive).
  G4Tubs* liquid = new G4Tubs("liquid", 0, LiquidDiam/2, LiquidHeight/2,
			      0, 360*deg);
  G4LogicalVolume* T1_liq_log =
    new G4LogicalVolume(liquid, water_nist, "T1_liq_log", 0,0,0);//For Water
  //new G4LogicalVolume(liquid, WbLS, "T1_liq_log", 0,0,0);//For WbLS
  G4VPhysicalVolume* T1_liq_phys =
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), T1_liq_log, "T1_liq_phys",
		      T1_log, false, 0, false);

  //Create SD for T1 liquid

  //Create the UVT acrylic window.
  G4Tubs* T1_win = new G4Tubs("T1_win", 0, UVTdiam/2, T1UVTheight/2, 0,360*deg);
  G4LogicalVolume* T1_win_log =
    new G4LogicalVolume(T1_win, Acrylic_nist, "T1_win_log", 0,0,0);
  G4VPhysicalVolume* T1_win_phys =
    new G4PVPlacement(0, G4ThreeVector(0 , 0, T1UVTdisp), T1_win_log,
		      "T1_win_phys", T1_log, false, 0, false);

  //Vis attributes for the window.
  G4VisAttributes* VA_T1_win = new G4VisAttributes();
  VA_T1_win->SetColor(1,0,0);
  VA_T1_win->SetForceSolid(true);
  T1_win_log->SetVisAttributes(VA_T1_win);


  //Now to make T2 (with the Al housing).
  G4Tubs* AlHousing = new G4Tubs("Al Housing", 0, AlOuterDiam/2, AlHeight/2,	
				 0, 360*deg);
  G4LogicalVolume* AlT2_log = 
    new G4LogicalVolume(AlHousing, AlAlloy, "AlT2_log", 0,0,0);
  G4VPhysicalVolume* AlT2_phys =
    new G4PVPlacement(RotMat, G4ThreeVector(0,0, (GapT1H2 + GapH2T2)), AlT2_log,
		      "AlT2_phys", logical_world, false, 0, false);

  //Make window on black teflon tub.
  G4Tubs* T2_win = new G4Tubs("T2_win", 0, UVTdiam/2, T2UVTheight/2, 0,360*deg);
  G4LogicalVolume* T2_win_log =
    new G4LogicalVolume(T2_win, Acrylic_nist, "T2_win_log", 0,0,0);
  G4VPhysicalVolume* T2_win_phys =
    new G4PVPlacement(0, G4ThreeVector(0 , 0, T2UVTdisp), T2_win_log,
		      "T2_win_phys", AlT2_log, false, 0, false);

  //Vis attributes for the window.
  G4VisAttributes* VA_T2_win = new G4VisAttributes();
  VA_T2_win->SetColor(1,0,0);
  VA_T2_win->SetForceSolid(true);
  T2_win_log->SetVisAttributes(VA_T2_win);

  //Make black teflon interior using same geometry as white PFTE tub.
  //I need to put a hole in this teflon to make room for the window.
  G4SubtractionSolid* T2Tub =
    new G4SubtractionSolid("T2Tub", Tub, T2_win, 0,
			   G4ThreeVector(0, 0, T2UVTdisp));
  G4LogicalVolume* T2_log = 
    new G4LogicalVolume(T2Tub, PFTE_black_nist, "T2_log", 0,0,0);
  G4VPhysicalVolume* T2_phys =
    new G4PVPlacement(0, G4ThreeVector(0,0,0), T2_log,
		      "T2_phys", AlT2_log, false, 0, false);

  //Create the liquid in T2 (it will need to be sensitive).
  //It is the same geometry as T1's liquid.
  G4LogicalVolume* T2_liq_log =
    new G4LogicalVolume(liquid, water_nist, "T2_liq_log", 0,0,0);//For Water
  //new G4LogicalVolume(liquid, WbLS, "T2_liq_log", 0,0,0);//For WbLS
  G4VPhysicalVolume* T2_liq_phys =
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), T2_liq_log, "T2_liq_phys",
		      T2_log, false, 0, false);

  //Create SD for T2 liquid

  //Create PMTs. 
  //According to Hamamatsu, diam = 52 mm.
  //Thickness is indeterminate, so I'll make it 5 mm.
  G4double PMTglassDiam = 51*mm;
  G4double PMTglassThick = 5*mm;
  G4double PMTT1Disp = ((TubHeight + PMTglassThick)/2) + PMTGap;
  G4double PMTT2Disp = ((AlHeight + PMTglassThick)/2) + PMTGap;

  G4Tubs* PMTglass = new G4Tubs("PMT glass", 0, PMTglassDiam/2, PMTglassThick/2,
				0, 360*deg);

  G4LogicalVolume* PMT_T1_log =
    new G4LogicalVolume(PMTglass, glass_nist, "PMT_T1_log",0,0,0);

  G4LogicalVolume* PMT_T2_log =
    new G4LogicalVolume(PMTglass, glass_nist,"PMT_T2_log",0,0,0);

  //Vis attributes for the PMTs.
  G4VisAttributes* VA_PMT_T1 = new G4VisAttributes();
  VA_PMT_T1->SetColor(0,1,0);
  VA_PMT_T1->SetForceSolid(true);
  PMT_T1_log->SetVisAttributes(VA_PMT_T1);

  G4VisAttributes* VA_PMT_T2 = new G4VisAttributes();
  VA_PMT_T2->SetColor(0,1,0);
  VA_PMT_T2->SetForceSolid(true);
  PMT_T2_log->SetVisAttributes(VA_PMT_T2);


  G4VPhysicalVolume* PMT_T1_phys =
    new G4PVPlacement(RotMat, G4ThreeVector(0, PMTT1Disp, 0), PMT_T1_log,
		      "PMT_T1_phys", logical_world, false, 0, false);

  G4VPhysicalVolume* PMT_T2_phys =
    new G4PVPlacement(RotMat, G4ThreeVector(0, PMTT2Disp, (GapT1H2 + GapH2T2)),
		      PMT_T2_log,"PMT_T2_phys", logical_world, false, 0, false);


  //Make the PMTs sensitive

  /////////////////////////////////////////////////////////////////////////////

  //Create the scintillating volume box.
  //To make this I need to make a box equal in dimensions to the outer walls of
  //ABS plastic box, then make another box equal in dimensions to the inner
  //walls of the ABS plastic box. Then I need to subtract some circular holes
  //from the wall of this solid, where the UV acrylic goes.
  //from the technical drawings, the thickness of the ABS is different in
  //different locations, making my life more difficult...
  //Outer dimensions:
  G4double widthOuter = 88.9*mm;
  G4double heightOuter = 139.48*mm;// = 126.78+12.70 mm
  G4double depthOuter = 136.36*mm;// = 130 mm (measured) + 2*3.18 mm
  //Inner dimensions:
  G4double widthInner =63.5*mm;// = 88.9 - 2*12.7 mm (both walls same thickness)
  G4double heightInner = 117.25*mm;// = 139.48 - 12.7 - 7.94 - 1.59 mm
  //(bottom is 12.7 mm, top is 9.53 mm thick, offset by +3.17 mm along y).
  G4double heightInnerOffset = 3.17*mm;
  G4double depthInner = 130*mm;//(measured, both walls same thickness).
  G4double PMTHoleDiam = 57.15*mm;
  //PMT centre is offset from BOTTOM of vessel by +43.98 mm. This corresponds to
  //being offset from the centre of the vessel by -25.76 mm.
  G4double PMTHoleOffset = -25.76*mm;


  //create SensitiveDetector object
  //Upstream PMT
  //  PMTwinUp* SDPMTup = new PMTwinUp("PMTwinUp_log");
  //pass new sensitive detector to manager
  //SDman->AddNewDetector(SDPMTup);
  //PMTglass_log_1->SetSensitiveDetector(SDPMTup);

  //Downstream PMT
  //PMTwinDown* SDPMTdown = new PMTwinDown("PMTwinDown_log");
  //pass new sensitive detector to manager
  //SDman->AddNewDetector(SDPMTdown);
  //PMTglass_log_2->SetSensitiveDetector(SDPMTdown);

  //PMT glass has same y-axis offset as acrylic window.
  //Z offset = +/- (depthOuter/2 + OuterWinThick + PMTglassThick/2)
  //G4double PMTglassOffset = (depthOuter/2) + OuterWinThick + (PMTglassThick/2);

  //G4VPhysicalVolume* PMTglassUp_phys =
  //new G4PVPlacement(0, G4ThreeVector(0, (theBoxOffset + PMTHoleOffset),
  //				       -(PMTglassOffset+PMTGap)),
  //		      PMTglass_log_1, "PMTglassUp_phys",
  //		      logical_world, false, 0);

  //G4VPhysicalVolume* PMTglassDown_phys = 
  //new G4PVPlacement(0, G4ThreeVector(0, (theBoxOffset + PMTHoleOffset),
  //				       (PMTglassOffset+PMTGap)), PMTglass_log_2,
  //		      "PMTglassDown_phys", logical_world, false, 0);
  

  //Now to add the WbLS/water to the mix...
  //The dimensions of the liquid are identical to those of the inner box volume.
  //Water case
  //G4LogicalVolume* liquid_log = new G4LogicalVolume(InnerBox, water_nist,
  ///						    "liquid_log", 0,0,0);
  //WbLS case
  //G4LogicalVolume* liquid_log = new G4LogicalVolume(InnerBox, WbLS,
  //						    "liquid_log", 0,0,0);

  //Need to register liquid as sensitive detector...
  //SensitiveDetector* SDLiquid = new SensitiveDetector("liquid_log");
  //get pointer to the sensitive detector manager: this class is used by
  //pass to manager
  //SDman->AddNewDetector(SDLiquid);

  //now we pass the sensitive detector pointer to the logical volume of our 
  //scoring volume
  //liquid_log->SetSensitiveDetector(SDLiquid);


  //The liquid placement vector will be the same as the subtraction solid used
  //to create the space for it in the first place.
  //G4VPhysicalVolume* liquid_phys =
  //new G4PVPlacement(0, G4ThreeVector(0, theBoxOffset + heightInnerOffset, 0),
  //		      liquid_log, "liquid_phys", logical_world, false, 0);


  //////////Do optical surfaces...////////////
  G4OpticalSurface* OptSurf_T1 =
    new G4OpticalSurface("Optical surface, Liquid-White PFTE");//,unified,
  //groundfrontpainted,//Only lambertian reflection + abs. 
  //			 dielectric_dielectric);
  //Unified model  
  OptSurf_T1->SetModel(unified);
  OptSurf_T1->SetType(dielectric_dielectric);
  OptSurf_T1->SetFinish(ground);
  //Using a LUT
  //OptSurf_T1->SetType(dielectric_LUT);
  //OptSurf_T1->SetModel(LUT);
  //OptSurf_T1->SetFinish(polishedteflonair);
  //Glisur model
  //OptSurf_T1->SetModel(glisur);
  //OptSurf_T1->SetType(dielectric_metal);
  //OptSurf_T1->SetFinish(ground);
  G4LogicalBorderSurface* WaterToT1 =
    new G4LogicalBorderSurface("WaterToT1", T1_liq_phys, T1_phys,
  			       OptSurf_T1);
 

  G4OpticalSurface* OptSurf_T1_outer =
    new G4OpticalSurface("Optical surface, White PFTE-Air");
  //Unified model  
  OptSurf_T1_outer->SetModel(unified);
  OptSurf_T1_outer->SetType(dielectric_metal);
  OptSurf_T1_outer->SetFinish(ground);
  G4LogicalBorderSurface* WaterToT1_outer =
    new G4LogicalBorderSurface("WaterToT1_outer", T1_phys, physical_world,
  			       OptSurf_T1_outer);

  G4OpticalSurface* OptSurf_T2 =
    new G4OpticalSurface("Optical surface, Liquid-Black PFTE");
  //Unified model  
  OptSurf_T2->SetModel(unified);
  OptSurf_T2->SetType(dielectric_metal);
  OptSurf_T2->SetFinish(ground);
  G4LogicalBorderSurface* WaterToT2 =
    new G4LogicalBorderSurface("WaterToT2", T2_liq_phys, T2_phys,
  			       OptSurf_T2);


  G4OpticalSurface* OptSurf_WaterAcrylic =
    new G4OpticalSurface("Optical surface, Water-Acrylic");
  OptSurf_WaterAcrylic->SetModel(unified);
  OptSurf_WaterAcrylic->SetType(dielectric_dielectric);
  OptSurf_WaterAcrylic->SetFinish(polished);
  OptSurf_WaterAcrylic->SetPolish(0.1);
  OptSurf_WaterAcrylic->SetSigmaAlpha(1.);  

  G4LogicalBorderSurface* WaterToAcrylicT1 =
    new G4LogicalBorderSurface("WaterToAcrylicT1", T1_liq_phys, T1_win_phys,
  			       OptSurf_WaterAcrylic);
  
  G4LogicalBorderSurface* WaterToAcrylicT2 =
    new G4LogicalBorderSurface("WaterToAcrylicT2", T2_liq_phys, T2_win_phys,
			       OptSurf_WaterAcrylic);
  
  
  //G4OpticalSurface* OptSurf_AcrylicAir =
  //new G4OpticalSurface("Optical surface, Acrylic-Air");
//OptSurf_AcrylicAir->SetModel(glisur);
//OptSurf_AcrylicAir->SetType(dielectric_dielectric);
//OptSurf_AcrylicAir->SetFinish(ground);
//OptSurf_AcrylicAir->SetPolish(0.5);
 
//G4LogicalBorderSurface* AcrylicUpToAir =
//new G4LogicalBorderSurface("AcrylicUpToAir", windowUp_phys, physical_world,
//			       OptSurf_AcrylicAir);
  
//G4LogicalBorderSurface* AcrylicDownToAir =
//new G4LogicalBorderSurface("AcrylicDownToAir", windowDown_phys,
//			       physical_world, OptSurf_AcrylicAir);
  
  
//G4OpticalSurface* OptSurf_AirPMT =
//new G4OpticalSurface("Optical surface, Air-PMT");
//OptSurf_AirPMT->SetModel(glisur);
//OptSurf_AirPMT->SetType(dielectric_dielectric);
//OptSurf_AirPMT->SetFinish(ground);
//OptSurf_AirPMT->SetPolish(0.5);
  
//G4LogicalBorderSurface* AirToPMTUp =
//new G4LogicalBorderSurface("AirToPMTUp", physical_world, PMTglassUp_phys,
//			       OptSurf_AirPMT);
  
//G4LogicalBorderSurface* AirToPMTDown =
//new G4LogicalBorderSurface("AirToPMTDown", physical_world,
//			       PMTglassDown_phys, OptSurf_AirPMT);
  
    
  return physical_world;
}


void DetectorConstruction::GetOptInfo(FILE* pfile, G4double unit){
  //Create the container for the data.
  vector < double > wl;
  vector < double > prop;
  int nvals = 0;
  float wavelength;
  float property;  
  //G4cout << "Entering while loop" << G4endl;
  //now loop through the file until EOF
  while(1){
    //file format is, wavelength [whitespace] property. 
    //G4cout << "Calling fscanf" << G4endl;
    nvals = fscanf(pfile, "%f %f ", &wavelength, &property);
    //G4cout << "fscanf called; nvals = " << nvals << G4endl;
    if(nvals == 2){
      //store in vectors.
      wl.push_back((1239.84187/wavelength)*eV);//convert from nm to eV
      prop.push_back(property*unit);
      //G4cout << "wavelength = " << wavelength << ", property = " << property
      //     << G4endl;
    }
    else if(nvals == -1){
      break;
    }
    else{
      printf("FILE READ ERROR.\n");
    }
  }
  //G4cout << "Finished reading file, outputting" << G4endl;
  //finished file, return the vector
  thedata.push_back(wl);
  thedata.push_back(prop);
}
