package org.car2x.veins.base.modules;

// Interface for application layer modules
moduleinterface IERUApplLayer extends IBaseApplLayer
{
    
    gates:
        input firstHospitalIn;
        output firstHospitalOut;
        input secondHospitalIn;
        output secondHospitalOut;
        
        input rsuIn;
        output rsuOut;
}