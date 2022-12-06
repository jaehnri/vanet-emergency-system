#include <veins/modules/application/traci/TrafficLightRSU.h>
#include <veins/modules/application/traci/A2TMessage11p_m.h>


using namespace veins;

Define_Module(veins::TrafficLightRSU);

void TrafficLightRSU::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0)
    {
        // ---------------------- Simulation parameters ----------------------
        /**
         * <!> These parameters are set in the omnetpp.ini file <!>
         */
        reinitializationDelay = 3;
        // ---------------------- Simulation parameters ----------------------

        initialized = false;
        lastMessageTreeId = 0;
        lastUpdate = simTime();
        highestPriority = 0;
    }
}

void TrafficLightRSU::onWSM(BaseFrame1609_4* frame) {
    if (frame->getKind() == SEND_OPEN_TRAFFIC_LIGHT_EVT) {
        A2TMessage11p* wsm = check_and_cast<A2TMessage11p*>(frame);

        if (!initialized) {
            setTraCI();
            associateTrafficlight();

            initialized = true;
        }

        if (!associatedTlId.empty()) {
            TraCICommandInterface::Trafficlight associatedTl = traci->trafficlight(associatedTlId);

            long messageTreeId = wsm->getTreeId();

            if (lastMessageTreeId != messageTreeId) // The message has not been processed yet
            {
                lastMessageTreeId = messageTreeId;

                EV << "Traffic light state:" << endl;
                EV << "  - Cooldown: " << simTime()-lastUpdate << endl;
                EV << "  - Highest priority: " << highestPriority << endl;
                EV << "  - Last ambulance ID: " << memorizedAmuId << endl;
                EV << "  - Last update: " << lastUpdate << endl;

                if (simTime()-lastUpdate >= reinitializationDelay)
                {
                    lastUpdate = simTime();
                    memorizedAmuId = -1;
                    highestPriority = 0;
                    associatedTl.reinitialize(); // Check if the traffic light has to be set back to its normal state
                }

                if (wsm->isFromAmbulance())
                {
                    std::cout << "Sent from ambulance";
                    std::string amuLaneId = wsm->getAmuLaneId();
                    std::string amuRoadId = traci->lane(amuLaneId).getRoadId();

                    if (associatedTl.isControlling(amuRoadId))
                    {
                        int wsmPriority = wsm->getPriority();
                        int wsmAmuId = wsm->getAmuId();

                        if (wsmPriority == highestPriority)
                        {
                            if (wsmAmuId == memorizedAmuId || memorizedAmuId == -1)
                            {
                                associatedTl.prioritizeRoad(amuRoadId);
                                update(wsmAmuId, wsmPriority);
                            }
                        }
                        else if (wsmPriority > highestPriority)
                        {
                            associatedTl.prioritizeRoad(amuRoadId);
                            update(wsmAmuId, wsmPriority);
                        }
                    }
                }
            }
            else EV << "<!> This message has already been processed." << endl;
        }
    }
}

void TrafficLightRSU::setTraCI()
{
    veins::TraCIScenarioManager* manager = veins::TraCIScenarioManagerAccess().get();
    traci = manager->getCommandInterface();
}

void TrafficLightRSU::associateTrafficlight() {

    for (std::string junctionId: traci->getJunctionIds()) {

        TraCICommandInterface::Junction junction = traci->junction(junctionId);
        double distanceFromJunction = traci->getDistance(curPosition, junction.getPosition(), false);

        if (distanceFromJunction < 40) {
            for (std::string tlId: traci->getTrafficlightIds()) {
                if (junctionId == tlId) {
                    EV << "TL associated with junctionId" << tlId << endl;
                    associatedTlId = tlId;
                }
            }
        }
    }
}

void TrafficLightRSU::update(int memorizedAmuId, int highestPriority)
{
    this->memorizedAmuId = memorizedAmuId;
    this->highestPriority = highestPriority;
    lastUpdate = simTime();
}



