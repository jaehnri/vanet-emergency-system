package org.car2x.veins.nodes;
import org.car2x.veins.base.modules.*;
import org.car2x.veins.modules.nic.Nic80211p;
import org.car2x.veins.modules.ethernet.NicEth;

module RSU
{
    parameters:
        string applType; //type of the application layer
        string nicType = default("Nic80211p"); // type of network interface card
        int rsuCount = default(0);
        int eruCount = default(0);
        int hospitalCount = default(0);
    gates:
        input veinsradioIn; // gate for sendDirect  
        inout rsuGates[rsuCount];
        inout eruGates[eruCount];
        inout hospitalGates[hospitalCount];

    submodules:
        appl:   <applType> like org.car2x.veins.base.modules.IRSUApplLayer {
            parameters:
                rsuCount = rsuCount;
                eruCount = eruCount;
                hospitalCount = hospitalCount;
                @display("p=60,50");
        }
        nic: <nicType> like org.car2x.veins.modules.nic.INic80211p {
            parameters:
                @display("p=60,166");
        }
        mobility: BaseMobility {
            parameters:
                @display("p=170,172;i=block/cogwheel");
        }
        wireNic: NicEth {
            parameters:
                wireCount = rsuCount + eruCount + hospitalCount;
            	@display("p=154,60;i=block/ifcard");
        }
    //connections:
    connections allowunconnected:
        nic.upperLayerOut --> appl.lowerLayerIn;
        nic.upperLayerIn <-- appl.lowerLayerOut;
        nic.upperControlOut --> appl.lowerControlIn;
        nic.upperControlIn <-- appl.lowerControlOut;
        veinsradioIn --> nic.radioIn;
        
        for i = 0..(rsuCount - 1) {
            appl.rsuGates[i] <--> wireNic.internalWires[i];
            rsuGates[i] <--> wireNic.wires[i];
        }

        for i = 0..(eruCount - 1) {
            appl.eruGates[i] <--> wireNic.internalWires[i + rsuCount];
            eruGates[i] <--> wireNic.wires[i + rsuCount];
        }
        
        for i = 0..(hospitalCount - 1) {
            appl.hospitalGates[i] <--> wireNic.internalWires[i + rsuCount + eruCount];
            hospitalGates[i] <--> wireNic.wires[i + rsuCount + eruCount];
        }
}
