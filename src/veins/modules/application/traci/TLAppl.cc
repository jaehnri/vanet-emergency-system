#include <veins/modules/application/traci/TLAppl.h>
#include <veins/modules/messages/A2TMessage11p_m.h>


using namespace veins;

Define_Module(veins::TLAppl);

void TLAppl::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    canOpenTraffic = getParentModule()->par("canOpenTraffic");
    //mobility = TraCIMobilityAccess().get(getParentModule());
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

void TLAppl::onWSM(BaseFrame1609_4* frame) {
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
                    std::cout << "Sent from ambulance" << endl;
                    std::string amuLaneId = wsm->getAmuLaneId();
                    std::string amuRoadId = traci->lane(amuLaneId).getRoadId();
                    std::cout << "amuRoadId: " << amuRoadId << endl;
                    if(canOpenTraffic) {
                        openTraffic(amuRoadId);
                    }


                    if (associatedTl.isControlling(amuRoadId))
                    {
                        int wsmPriority = wsm->getPriority();
                        int wsmAmuId = wsm->getAmuId();

                        if (wsmPriority == highestPriority)
                        {
                            if ((wsmAmuId == memorizedAmuId || memorizedAmuId == -1) && canOpenTraffic)
                            {
                                associatedTl.prioritizeRoad(amuRoadId);
                                update(wsmAmuId, wsmPriority);
                            }
                        }
                        else if (wsmPriority > highestPriority && canOpenTraffic)
                        {
                            associatedTl.prioritizeRoad(amuRoadId);
                            update(wsmAmuId, wsmPriority);
                        }
                    }
                }
                else {
                    std::cout << "Sent from otherTL";
                }
            }
            else EV << "<!> This message has already been processed." << endl;
        }
    }
}

void TLAppl::openTraffic(std::string amuRoadId) {
    for (std::string id: traci->getTrafficlightIds()) {
            TraCICommandInterface::Trafficlight tl = traci->trafficlight(id);
            std::cout << "analysing tl: " <<  id << endl;
            if(tl.isControlling(amuRoadId)) {
                std::cout << id << " is controlling" << endl;
                tl.prioritizeRoad(amuRoadId);
            }
    }
}

void TLAppl::setTraCI()
{
    veins::TraCIScenarioManager* manager = veins::TraCIScenarioManagerAccess().get();
    traci = manager->getCommandInterface();
}

void TLAppl::associateTrafficlight() {


    for (std::string junctionId: traci->getJunctionIds()) {

        TraCICommandInterface::Junction junction = traci->junction(junctionId);

        double distanceFromJunction = traci->getDistance(curPosition, junction.getPosition(), false);

        if (distanceFromJunction < 40) {
            for (std::string tlId: traci->getTrafficlightIds()) {
                if (junctionId == tlId) {
                    EV << "TL associated with junctionId" << tlId << endl;
                    associatedTlId = tlId;


                    //TraCIMobility* mobility;
                    //TraCICommandInterface* traci;

                    //mobility = TraCIMobilityAccess().get(getParentModule());
                    //traci = mobility->getCommandInterface();
                    //traci->trafficlight("n33");
                    //mobility = TraCIMobilityAccess().get(getParentModule());
                    //mobility->getExternalId();
                    //traciTl = mobility->getTlCommandInterface(associatedTlId);
                }
            }
            //mobility->getExternalId();

        }
    }
    TraCICommandInterface::Trafficlight tl = traci->trafficlight(associatedTlId);
}

void TLAppl::update(int memorizedAmuId, int highestPriority)
{
    this->memorizedAmuId = memorizedAmuId;
    this->highestPriority = highestPriority;
    lastUpdate = simTime();
}



