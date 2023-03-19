#!/bin/sh
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c RC225 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c RC506 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c RC787 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AS225 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AS506 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AS787 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AP225 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AP506 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AP787 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c EH225 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c EH506 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c EH787 & 
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c SR225 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c SR506 &
sleep 1
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c SR787 &
sleep 1