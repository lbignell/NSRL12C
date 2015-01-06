#ifndef RunAction_hh
#define RunAction_hh 1
//
#include "G4UserRunAction.hh"
#include "G4UnitsTable.hh"
#include "DetectorConstruction.hh"

#include "TH1D.h"
#include <fstream>

//declare the DetectorConstruction class as we will define a pointer later
class DetectorConstruction;
class TTree;
class TFile;

//needed for using standard libraries
using namespace std;

//run action class, carries out tasks at the begin and end of each run
//the concept of a run incorporates a fixed geometry, fixed beam conditions, simulation of number of primaries
//begins with /run/beamOn command and finishes with tracking of last secondary to zero energy 

class RunAction : public G4UserRunAction {
//
public:
//run action class needs pointer ot the detector construction class in order to get details of the readout geometry
//accepts pointer to detector construction class

  RunAction(DetectorConstruction*);
  ~RunAction();

    //

private:
//an ofstream to access the output file
  ofstream outfile;
  TFile* RootOP;
  
  TTree* EdepTree;

  double KE_T1;
  double KE_T2;
  double Edep_H1;
  double Edep_H2;
  double Edep_H3;
  double Edep_T1;
  double Edep_T2;
  double VertX;
  double VertY;
  bool HazPrimary_H1;
  bool HazPrimary_H2;
  bool HazPrimary_H3;
  bool HazPrimary_T1;
  bool HazPrimary_T2;
  unsigned long long int NumOP_T1;
  unsigned long long int NumOP_T2;
  vector< vector< double > > OPEn_T1;
  vector< vector< double > > OPEn_T2;
  vector< string > OPProc_T1;
  vector< string > OPProc_T2;
  vector< vector< double > > OPEn_PMTT1;
  vector< vector< double > > OPEn_PMTT2;
  vector< vector< double > > OPEnMeas_PMTT1;
  vector< vector< double > > OPEnMeas_PMTT2;
  unsigned long long int NumOP_PMTT1;
  unsigned long long int NumOP_PMTT2;
  unsigned long long int MeasNumOP_PMTT1;
  unsigned long long int MeasNumOP_PMTT2;
  vector<string> LVatVertex_PMTT1;
  vector<string> LVatVertex_PMTT2;
  vector<double> OPTrackLength_PMTT1;
  vector<double> OPTrackLength_PMTT2;

//local pointer for detector construction class
    DetectorConstruction* myDC;

public:

//note argument of these methods is a pointer to a G4Run object
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  //Argument list:
  //Kinetic Energy (T1/T2), Edep (H1/H2/H3/T1/T2), vertex X, vertex Y,
  //Primary? (H1/H2/H3/T1/T2), Tot # of opt photons (T1/T2),
  //OP energy on production (T1/T2),
  //OP creator process (T1/T2), OP energy at PMT (T1/T2),
  //measured OP energy at PMT (T1/T2),
  //# OPs incident on PMT (T1/T2), # OPs measured by PMT (T1/T2).
  //Note: 'Measured' below means hitting Photocathode and after QE has been
  //accounted for.
  //All vectors of vectors have idx[0] = Ckov, idx[1] = WLS, idx[2] = Scint.
  void TallyEvtData(double, double, double, double, double, double, double,
		    double, double, bool, bool, bool, bool, bool,
		    unsigned long long int, unsigned long long int,
		    vector< vector< double > >&, vector< vector< double > >&,
		    vector< string >&, vector< string >&,
		    vector< vector< double > >&, vector< vector< double > >&,
		    vector< vector< double > >&, vector< vector< double > >&,
		    unsigned long long int, unsigned long long int,
		    unsigned long long int, unsigned long long int,
		    vector<string>&, vector<string>&,
		    vector<double>&, vector<double>&);

};

#endif
