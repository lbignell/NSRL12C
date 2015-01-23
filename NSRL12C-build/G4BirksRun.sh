#!/bin/bash
#The default behavior will be to start with isWater=true, WbLSfraction=0.0099,
#/gun/energy 2000 MeV, and /run/beamOn 10000. This is located in RunDefault.mac
cp RunBirks.mac RunSimple.mac
################
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.1_210MeV.root
################
#perl -pi -e 's/0.1/0.125/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.125_210MeV.root
################
#perl -pi -e 's/0.125/0.15/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.15_210MeV.root
################
#perl -pi -e 's/0.15/0.175/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.175_210MeV.root
################
#perl -pi -e 's/0.175/0.2/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.2_210MeV.root
################
#perl -pi -e 's/0.2/0.225/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.225_210MeV.root
################
#perl -pi -e 's/0.225/0.25/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.25_210MeV.root
################
#perl -pi -e 's/0.25/0.275/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.275_210MeV.root
################
#perl -pi -e 's/0.275/0.3/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.3_210MeV.root
################
#perl -pi -e 's/0.3/0.325/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.325_210MeV.root
################
#perl -pi -e 's/0.325/0.35/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.35_210MeV.root
################
#perl -pi -e 's/0.35/0.375/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.375_210MeV.root
################
#perl -pi -e 's/0.375/0.4/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.4_210MeV.root
################
#perl -pi -e 's/0.4/0.425/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.425_210MeV.root
################
#perl -pi -e 's/0.425/0.45/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.45_210MeV.root
################
#perl -pi -e 's/0.45/0.475/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.475_210MeV.root
################
#perl -pi -e 's/0.475/0.5/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_1pc_kB0.5_210MeV.root
################
#perl -pi -e 's/0.5/0.1/' RunSimple.mac
perl -pi -e 's/0.0099/0.004/' RunSimple.mac
perl -pi -e 's/105/15/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.1_210MeV.root
################
#perl -pi -e 's/0.1/0.125/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.125_210MeV.root
################
#perl -pi -e 's/0.125/0.15/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.15_210MeV.root
################
#perl -pi -e 's/0.15/0.175/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.175_210MeV.root
################
#perl -pi -e 's/0.175/0.2/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.2_210MeV.root
################
#perl -pi -e 's/0.2/0.225/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.225_210MeV.root
################
#perl -pi -e 's/0.225/0.25/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.25_210MeV.root
################
#perl -pi -e 's/0.25/0.275/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.275_210MeV.root
################
#perl -pi -e 's/0.275/0.3/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.3_210MeV.root
################
#perl -pi -e 's/0.3/0.325/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.325_210MeV.root
################
#perl -pi -e 's/0.325/0.35/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.35_210MeV.root
################
#perl -pi -e 's/0.35/0.375/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.375_210MeV.root
################
#perl -pi -e 's/0.375/0.4/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_0p4pc_kB0.4_210MeV.root
################
#PureLS samples
perl -pi -e 's/0.004/1./' RunSimple.mac
#perl -pi -e 's/0.4/0.1/' RunSimple.mac
perl -pi -e 's/15/8400/' RunSimple.mac
perl -pi -e 's/7000/3000/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_PureLS_kB0.1_210MeV.root
################
perl -pi -e 's/0.1/0.05/' RunSimple.mac
./NSRL12C RunSimple.mac
mv Edep_.root WbLS_PureLS_kB0.05_210MeV.root
################
perl -pi -e 's/0.05/0.0/' RunSimple.mac
./NSRL12C RunSimple.mac
mv Edep_.root WbLS_PureLS_kB0.0_210MeV.root
################
#perl -pi -e 's/0.1/0.15/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_PureLS_kB0.15_210MeV.root
################
#perl -pi -e 's/0.15/0.2/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_PureLS_kB0.2_210MeV.root
################
#perl -pi -e 's/0.2/0.25/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_PureLS_kB0.25_210MeV.root
################
#perl -pi -e 's/0.25/0.3/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_PureLS_kB0.3_210MeV.root
################
#perl -pi -e 's/0.3/0.35/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_PureLS_kB0.35_210MeV.root
################
#perl -pi -e 's/0.35/0.4/' RunSimple.mac
#./NSRL12C RunSimple.mac
#mv Edep.root WbLS_PureLS_kB0.4_210MeV.root
#The End.#
