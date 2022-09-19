package org.car2x.veins.nodes;
import org.car2x.veins.base.modules.*;
import org.car2x.veins.modules.nic.Nic80211p;
import org.car2x.veins.modules.world.traci.trafficLight.TraCITrafficLightInterface;
module TrafficLight
{
    parameters:
        string logicType;
        string applType; //type of the application layer
        string nicType = default("Nic80211p"); // type of network interface card
        string externalId; // TraCI server's id of the junction/tls managed by this module
    gates:
        input veinsradioIn; // gate for sendDirect
    submodules:
        appl: <applType> like org.car2x.veins.base.modules.ITrafficLightApplLayer {
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
        tlInterface: TraCITrafficLightInterface {
            @display("p=200,50");
        }

        logic: <logicType> like org.car2x.veins.base.modules.ITrafficLightLogic {
            @display("p=130,50");
        }

    connections:
        tlInterface.logic <--> logic.interface;
        appl.logic <--> logic.applLayer;

        nic.upperLayerOut --> appl.lowerLayerIn;
        nic.upperLayerIn <-- appl.lowerLayerOut;
        nic.upperControlOut --> appl.lowerControlIn;
        nic.upperControlIn <-- appl.lowerControlOut;

        veinsradioIn --> nic.radioIn;
}
