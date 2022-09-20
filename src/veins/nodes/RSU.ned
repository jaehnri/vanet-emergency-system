package org.car2x.veins.nodes;
import org.car2x.veins.base.modules.*;
import org.car2x.veins.modules.nic.Nic80211p;
import org.car2x.veins.modules.application.traci.WiredConnection;

module RSU
{
    parameters:
        string applType; //type of the application layer
        string nicType = default("Nic80211p"); // type of network interface card
        int wiredConnections = default(1);
    gates:
        input veinsradioIn; // gate for sendDirect  
        input veinsradioIn2;
        input RSUIngate[];		//added
        output RSUOutgate[];     //added
        inout rsuConnection[wiredConnections];

    submodules:
        appl: <applType> like org.car2x.veins.base.modules.IBaseApplLayer {
            parameters:
                wireNumber=wiredConnections;
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
        wired[wiredConnections]: WiredConnection;

    //connections:
    connections allowunconnected:
        nic.upperLayerOut --> appl.lowerLayerIn;
        nic.upperLayerIn <-- appl.lowerLayerOut;
        nic.upperControlOut --> appl.lowerControlIn;
        nic.upperControlIn <-- appl.lowerControlOut;
        veinsradioIn --> nic.radioIn;
        
        for i=0..wiredConnections-1 {
            wired[i].wire <--> rsuConnection[i];
            wired[i].internalWire <--> appl.wiredConnetion[i];
        }
}
