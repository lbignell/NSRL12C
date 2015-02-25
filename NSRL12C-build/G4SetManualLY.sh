#!/bin/bash
#The default behavior will be to start with isWater=true, WbLSfraction=0.0099,
#/gun/energy 2000 MeV, and /run/beamOn 10000. This is located in RunDefault.mac
cp RunManualLY.mac RunSimple.mac
################
#First run
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#echo 'kB = 0.05'
#echo 'LY = 8800'
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#./NSRL12C RunSimple.mac >> log.txt
#echo Finished first run
################
#Loop the others
#kBprev='0.125'
#for i in `seq 0.150 0.025 0.600`
#do
#    kBval=$i
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    echo 'kB = '$kBval
#    echo 'LY = 109'
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    perl -pi -e ''s/$kBprev/$kBval/'' RunSimple.mac
#    kBprev=$kBval
#    ./NSRL12C RunSimple.mac >> log.txt
#done
###############
################
#Second run
#perl -pi -e 's/109/111/' RunSimple.mac
#perl -pi -e 's/0.600/0.125/' RunSimple.mac
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#echo 'kB = 0.125'
#echo 'LY = 111'
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#./NSRL12C RunSimple.mac >> log.txt
#echo Finished first run
################
#Loop the others
#kBprev='0.125'
#for i in `seq 0.150 0.025 0.600`
#do
#    kBval=$i
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    echo 'kB = '$kBval
#    echo 'LY = 111'
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    perl -pi -e ''s/$kBprev/$kBval/'' RunSimple.mac
#    kBprev=$kBval
#    ./NSRL12C RunSimple.mac >> log.txt
#done
###############
###############
#Third run
#perl -pi -e 's/111/113/' RunSimple.mac
#perl -pi -e 's/0.600/0.125/' RunSimple.mac
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#echo 'kB = 0.125'
#echo 'LY = 113'
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#./NSRL12C RunSimple.mac >> log.txt
#echo Finished first run
################
#Loop the others
#kBprev='0.125'
#for i in `seq 0.150 0.025 0.600`
#do
#    kBval=$i
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    echo 'kB = '$kBval
#    echo 'LY = 113'
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    perl -pi -e ''s/$kBprev/$kBval/'' RunSimple.mac
#    kBprev=$kBval
#    ./NSRL12C RunSimple.mac >> log.txt
#done
###############
################
#Fourth run
#perl -pi -e 's/113/115/' RunSimple.mac
#perl -pi -e 's/0.600/0.125/' RunSimple.mac
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#echo 'kB = 0.125'
#echo 'LY = 115'
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#./NSRL12C RunSimple.mac >> log.txt
#echo Finished first run
################
#Loop the others
#kBprev='0.125'
#for i in `seq 0.150 0.025 0.600`
#do
#    kBval=$i
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    echo 'kB = '$kBval
#    echo 'LY = 115'
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    perl -pi -e ''s/$kBprev/$kBval/'' RunSimple.mac
#    kBprev=$kBval
#    ./NSRL12C RunSimple.mac >> log.txt
#done
###############

#Change the LY and kB values back.
#perl -pi -e 's/0.500/0.050/' RunSimple.mac
#perl -pi -e 's/103/107/' RunSimple.mac
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#echo 'kB = 0.050'
#echo 'LY = 107'
#echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#./NSRL12C RunSimple.mac >> log.txt
################
#Loop the others
#kBprev='0.050'
#for i in `seq 0.075 0.025 0.5`
#do
#    kBval=$i
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    echo 'kB = '$kBval
#    echo 'LY = 107'
#    echo '@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@'
#    perl -pi -e ''s/$kBprev/$kBval/'' RunSimple.mac
#    kBprev=$kBval
#    ./NSRL12C RunSimple.mac >> log.txt
#done


#./NSRL12C RunSimple.mac > log2.txt
#echo Finished second run!
################
#Third run
#perl -pi -e 's/475/210/' RunSimple.mac
##./NSRL12C RunSimple.mac > log3.txt
#echo Finished Third run!
################
#Fourth run
#perl -pi -e 's/210/2000/' RunSimple.mac
#Change from water to WbLS
#perl -pi -e 's/true/false/' RunSimple.mac
#./NSRL12C RunSimple.mac > log4.txt
#echo Finished Fourth run!
################
#Fifth run
#perl -pi -e 's/2000/475/' RunSimple.mac
#./NSRL12C RunSimple.mac > log5.txt
#echo Finished Fifth run!
################
#Sixth run
#perl -pi -e 's/475/210/' RunSimple.mac
#./NSRL12C RunSimple.mac > log6.txt
#echo Finished Sixth run!
################
#Seventh run
#perl -pi -e 's/_1pc_/_0p4pc_/' RunSimple.mac
#perl -pi -e 's/210/2000/' RunSimple.mac
#perl -pi -e 's/0.0099/0.004/' RunSimple.mac
#perl -pi -e 's/105/15/' RunSimple.mac
#perl -pi -e 's/0.329/0.15/' RunSimple.mac
#./NSRL12C RunSimple.mac > log7.txt
#echo Finished Seventh run!
################
#Eighth run
#perl -pi -e 's/2000/475/' RunSimple.mac
#./NSRL12C RunSimple.mac > log8.txt
#echo Finished Eighth run!
################
#Ninth run
#perl -pi -e 's/475/210/' RunSimple.mac
#./NSRL12C RunSimple.mac > log9.txt
#echo Finished Ninth run!
#I can add more runs to do LS simulations once I get the data...
################
#PureLS samples
#perl -pi -e 's/_0p4pc_/_PureLS_/' RunSimple.mac
#perl -pi -e 's/210/2000/' RunSimple.mac
#perl -pi -e 's/0.004/1./' RunSimple.mac
#perl -pi -e 's/15/8400/' RunSimple.mac
#perl -pi -e 's/25000/3000/' RunSimple.mac
./NSRL12C RunSimple.mac > log10.txt
#475 MeV protons
perl -pi -e 's/2000/475/' RunSimple.mac
./NSRL12C RunSimple.mac > log11.txt
#210 MeV Protons
perl -pi -e 's/475/210/' RunSimple.mac
./NSRL12C RunSimple.mac > log12.txt
