package org.car2x.veins.nodes;
import org.car2x.veins.base.modules.*;
import org.car2x.veins.modules.nic.Nic80211p;
import org.car2x.veins.modules.ethernet.NicEth;
module ERURSU 
{
    parameters:
        string applType; //type of the application layer
        string nicType = default("Nic80211p"); // type of network interface card
    gates:
        input veinsradioIn; // gate for sendDirect  
        inout rsuConnection;
        inout firstHospitalConnection;
        inout secondHospitalConnection;
    submodules:
        appl: <applType> like org.car2x.veins.base.modules.IERUApplLayer {
            parameters:
                @display("p=60,50");
        }

        nic: <nicType> like org.car2x.veins.modules.nic.INic80211p {
            parameters:
                @display("p=60,166");
        }

        mobility: BaseMobility {
            parameters:
                @display("p=130,172;i=block/cogwheel");
        }
		wireNic[3]: NicEth {
            @display("p=154,60;i=block;i=block/ifcard");
        }
    connections allowunconnected:
        nic.upperLayerOut --> appl.lowerLayerIn;
        nic.upperLayerIn <-- appl.lowerLayerOut;
        nic.upperControlOut --> appl.lowerControlIn;
        nic.upperControlIn <-- appl.lowerControlOut;
        veinsradioIn --> nic.radioIn;
        
        wireNic[0].wire <--> rsuConnection;
		wireNic[0].internalWireIn <-- appl.rsuOut;
        wireNic[0].internalWireOut --> appl.rsuIn;
        
        wireNic[1].wire <--> firstHospitalConnection;
		wireNic[1].internalWireIn <-- appl.firstHospitalOut;
        wireNic[1].internalWireOut --> appl.firstHospitalIn;
        
        wireNic[2].wire <--> secondHospitalConnection;
		wireNic[2].internalWireIn <-- appl.secondHospitalOut;
        wireNic[2].internalWireOut --> appl.secondHospitalIn;
        
        
}
