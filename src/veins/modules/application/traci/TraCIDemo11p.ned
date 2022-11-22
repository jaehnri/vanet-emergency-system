package org.car2x.veins.modules.application.traci;
import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;
import org.car2x.veins.modules.mobility.traci.TraCIMobility;  //added kafe

simple TraCIDemo11p extends DemoBaseApplLayer
{
    @class(veins::TraCIDemo11p);
    @display("i=block/app2");
    double ACCIDENTMESSAGETINTERVAL =default (1s) @unit(s);   //added
    double broadcastInterval = default (4s) @unit(s);
}
