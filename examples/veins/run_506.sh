#!/bin/sh
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c RC506 &
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AS506 &
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AP506 & 
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c EH506 & 
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c SR506 &