#!/bin/sh
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c RC225 &
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AS225 &
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AP225 & 
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c EH225 & 
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c SR225 &