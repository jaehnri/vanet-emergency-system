package org.car2x.veins.modules.application.traci;
import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;
import org.car2x.veins.base.modules.IERUApplLayer;
simple ERUApp extends DemoBaseApplLayer like IERUApplLayer
{
    @class(veins::ERUApp);
    string appName = default("My first Veins App!");
    
    gates:
        input firstHospitalIn;
        output firstHospitalOut;
        input secondHospitalIn;
        output secondHospitalOut;

        input rsuIn;
        output rsuOut;
}
