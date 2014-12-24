#!/bin/bash
#The default behavior will be to start with isWater=true, WbLSfraction=0.0099,
#and /run/beamOn 1. This is located in RunDefault.mac
cp RunDefault.mac RunSimple.mac
#Make the first substitution
./NSRL12C RunSimple.mac > log1.txt
echo Finished first run; move Edep.root if required...
#Make the second substitution
perl -pi -e 's/true/false/' RunSimple.mac
./NSRL12C RunSimple.mac > log2.txt
echo Finished second run!
