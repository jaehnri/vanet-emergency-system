package org.car2x.veins.modules.nic;

moduleinterface INic80211p
{
    @display("i=block/ifcard");
    gates:
        input upperLayerIn; // to upper layers
        output upperLayerOut; // from upper layers
        output upperControlOut; // control information
        input upperControlIn; // control information
        input radioIn; // radioIn gate for sendDirect      
}
