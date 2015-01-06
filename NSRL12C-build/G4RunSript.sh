#!/bin/bash
#The default behavior will be to start with isWater=true, WbLSfraction=0.0099,
#/gun/energy 2000 MeV, and /run/beamOn 10000. This is located in RunDefault.mac
#cp RunDefault.mac RunSimple.mac
################
#First run
#./NSRL12C RunSimple.mac > log1.txt
#echo Finished first run; move Edep.root if required...
#mv Edep.root Water_2000MeV.root
################
#Second run
#perl -pi -e 's/2000/475/' RunSimple.mac
#./NSRL12C RunSimple.mac > log2.txt
#echo Finished second run!
#mv Edep.root Water_475MeV.root
################
#Third run
#perl -pi -e 's/475/210/' RunSimple.mac
#./NSRL12C RunSimple.mac > log3.txt
#echo Finished Third run!
#mv Edep.root Water_210MeV.root
################
#Fourth run
#perl -pi -e 's/210/2000/' RunSimple.mac
#Change from water to WbLS
#perl -pi -e 's/true/false/' RunSimple.mac
#./NSRL12C RunSimple.mac > log4.txt
#echo Finished Fourth run!
#mv Edep.root WbLS_1pc_2000MeV.root
################
#Fifth run
#perl -pi -e 's/2000/475/' RunSimple.mac
#./NSRL12C RunSimple.mac > log5.txt
#echo Finished Fifth run!
#mv Edep.root WbLS_1pc_475MeV.root
################
#Sixth run
#perl -pi -e 's/475/210/' RunSimple.mac
#./NSRL12C RunSimple.mac > log6.txt
#echo Finished Sixth run!
#mv Edep.root WbLS_1pc_210MeV.root
################
#Seventh run
#perl -pi -e 's/210/2000/' RunSimple.mac
#perl -pi -e 's/0.0099/0.004/' RunSimple.mac
#./NSRL12C RunSimple.mac > log7.txt
#echo Finished Seventh run!
#mv Edep.root WbLS_0p4pc_2000MeV.root
################
#Eighth run
#perl -pi -e 's/2000/475/' RunSimple.mac
#./NSRL12C RunSimple.mac > log8.txt
#echo Finished Eighth run!
#mv Edep.root WbLS_0p4pc_475MeV.root
################
#Ninth run
#perl -pi -e 's/475/210/' RunSimple.mac
#./NSRL12C RunSimple.mac > log9.txt
#echo Finished Ninth run!
mv Edep.root WbLS_0p4pc_210MeV.root
#I can add more runs to do LS simulations once I get the data...
################
#PureLS samples
cp RunPureLS.mac RunSimple.mac
./NSRL12C RunSimple.mac > log10.txt
mv Edep.root PureLS_2000MeV.root
#475 MeV protons
perl -pi -e 's/2000/475/' RunSimple.mac
./NSRL12C RunSimple.mac > log11.txt
mv Edep.root PureLS_475MeV.root
#210 MeV Protons
perl -pi -e 's/475/210/' RunSimple.mac
./NSRL12C RunSimple.mac > log12.txt
mv Edep.root PureLS_210MeV.root
