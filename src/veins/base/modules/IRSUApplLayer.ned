package org.car2x.veins.base.modules;

// Interface for application layer modules
moduleinterface IRSUApplLayer extends IBaseApplLayer
{
    parameters:
        int rsuCount;
        int eruCount;
        int hospitalCount;   
    gates:
        inout rsuGates[rsuCount];
        inout eruGates[eruCount];
        inout hospitalGates[hospitalCount];
}