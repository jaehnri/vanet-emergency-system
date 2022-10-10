package org.car2x.veins.nodes;
import org.car2x.veins.base.modules.*;
import org.car2x.veins.modules.nic.Nic80211p;
import org.car2x.veins.modules.application.traci.NicEth;

module RSU
{
    parameters:
        string applType; //type of the application layer
        string nicType = default("Nic80211p"); // type of network interface card
    gates:
        input veinsradioIn; // gate for sendDirect  
        inout eruConnection;

    submodules:
        appl:   <applType> like org.car2x.veins.base.modules.IRSUApplLayer {
            parameters:
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
            @display("p=154,60;i=block/ifcard");
        }
    //connections:
    connections allowunconnected:
        nic.upperLayerOut --> appl.lowerLayerIn;
        nic.upperLayerIn <-- appl.lowerLayerOut;
        nic.upperControlOut --> appl.lowerControlIn;
        nic.upperControlIn <-- appl.lowerControlOut;
        veinsradioIn --> nic.radioIn;

		wireNic.wire <--> eruConnection;
		wireNic.internalWireIn <-- appl.eruOut;
        wireNic.internalWireOut --> appl.eruIn;
}
