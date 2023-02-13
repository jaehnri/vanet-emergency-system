package org.car2x.veins.modules.application.traci;
import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;
import org.car2x.veins.modules.mobility.traci.TraCIMobility;  //added kafe
import org.car2x.veins.base.modules.IRSUApplLayer;
simple HospitalAppl extends DemoBaseApplLayer like IRSUApplLayer
{
    parameters:
        @class(veins::HospitalAppl); 
        int rsuCount = default(0);
        int eruCount = default(0);
        int hospitalCount = default(0);   
      	
	gates:
	    inout rsuGates[rsuCount];
	    inout eruGates[eruCount];
	    inout hospitalGates[hospitalCount];
}
