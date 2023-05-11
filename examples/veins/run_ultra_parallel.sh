#!/bin/sh
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c RC225 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c RC450 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c RC675 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AS225 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AS450 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AS675 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AP225 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AP450 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AP675 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c EH225 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c EH450 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c EH675 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c SR225 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c SR450 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c SR675 &
sleep 1
