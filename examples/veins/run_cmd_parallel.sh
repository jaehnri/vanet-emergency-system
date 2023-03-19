#!/bin/sh
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c RC &
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AS &
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c AP & 
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c EH & 
opp_run -m -n .:../../src/veins --image-path=../../images -l ../../src/veins omnetpp.ini -u Cmdenv -c SR &