package org.car2x.veins.modules.application.traci;
import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;
import org.car2x.veins.modules.mobility.traci.TraCIMobility;  //added kafe
simple HospitalApp extends DemoBaseApplLayer
{
    @class(veins::HospitalApp);
    string appName = default("Hospital App!");
    
    gates:
        input eruIn;
        output eruOut;
}
