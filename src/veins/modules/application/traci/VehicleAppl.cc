#include "veins/modules/application/traci/VehicleAppl.h"
#include "veins/modules/messages/AccidentMessage_m.h"
#include "veins/modules/messages/TraCIDemo11pMessage_m.h"
#include <veins/modules/messages/A2TMessage11p_m.h>
#include <string.h>
using namespace veins;
using namespace std;
Define_Module(veins::VehicleAppl);

void VehicleAppl::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;

        accidentmessagetinterval = par("ACCIDENTMESSAGETINTERVAL");
        broadcastInterval = par("broadcastInterval");

        lastBroadcastAt = simTime();
        priority = 0;

        // Set SUMO and VEINS Ids
        veins::TraCIScenarioManager* manager = veins::TraCIScenarioManagerAccess().get();
        // For some reason mobility doesnt work
        mobility = TraCIMobilityAccess().get(getParentModule());
        vehicleSumoId = mobility->getExternalId();
        vehicleVeinsId = getParentModule()->getIndex();
        vehicleSumoTypeId = traciVehicle->getVType();



        std::cout << "vehicle sumo id " << vehicleSumoId << endl;
        std::cout << "vehicle sumo type id " << vehicleSumoTypeId << endl;
        //vehicleSumoTypeId = traci->getVType();


        // Only the "accident car" should send the accident message
        if (!isAmbulance() && !isNormalVehicle()) {
            sendAcdntEvt = new cMessage("Accident event at DemoBaseApplLayer", SEND_ACCIDENT_EVT);
            DemoBaseApplLayer::accidentStartTime = simTime().dbl();
            scheduleAt(simTime() + accidentmessagetinterval + exponential(5.0), sendAcdntEvt);
        }
   }
}
void VehicleAppl::onWSM(BaseFrame1609_4 *frame) {
    if (frame->getKind() == SEND_OPEN_TRAFFIC_LIGHT_EVT) {
        A2TMessage11p* wsm = check_and_cast<A2TMessage11p*>(frame);

        if (wsm->isFromAmbulance()) {
            traciVehicle->changeLane(0, 5.0);
        }
    }
}

void VehicleAppl::handleSelfMsg(cMessage *msg)
{
    switch (msg->getKind())
    {
        case SEND_BEACON_EVT:
        {
            DemoSafetyMessage *bsm = new DemoSafetyMessage();
            populateWSM(bsm);
            sendDown(bsm);
            scheduleAt(simTime() + beaconInterval, sendBeaconEvt);
            break;
        }
        case SEND_WSA_EVT:
        {
            DemoServiceAdvertisment *wsa = new DemoServiceAdvertisment();
            populateWSM(wsa);
            sendDown(wsa);
            scheduleAt(simTime() + wsaInterval, sendWSAEvt);
            break;
        }
        case SEND_ACCIDENT_EVT:
        {
            sendAccidentMessage();
            break;
        }
        default:
        {
            if (msg)
                EV_WARN << "APP: Error: Got Self Message of unknown kind! Name: "
                << msg->getName() << endl;
            break;
        }
    }
}

void VehicleAppl::handlePositionUpdate(cObject* obj) {
    DemoBaseApplLayer::handlePositionUpdate(obj);

    // checks if ambulance should send another OPEN_TRAFFIC_LIGHT message
    if (isAmbulance() && simTime() - lastBroadcastAt >= broadcastInterval) {
        A2TMessage11p* wsm = new A2TMessage11p();
        populateWSM(wsm);

        wsm->setIsFromAmbulance(true);
        wsm->setAmuId(vehicleVeinsId);
        wsm->setAmuLaneId(traciVehicle->getLaneId().c_str());
        wsm->setPriority(priority);
        wsm->setKind(SEND_OPEN_TRAFFIC_LIGHT_EVT);

        lastBroadcastAt = simTime();
        sendDown(wsm->dup());
    }

    // checks if ambulance arrived at the destination
    if (isAmbulance()) {

    }
}

void VehicleAppl::sendAccidentMessage() // assigned array indexed values to wsm fields and send it.
{
    EV << "Sending accident message";

    AccidentMessage *wsm = new AccidentMessage();
    populateWSM(wsm);
    wsm->setA_description("Emergency situation, an accident happens at the location 0.0. 0.0");
    wsm->setA_location(curPosition);
    wsm->setA_speed(traciVehicle->getSpeed());
    wsm->setKind(SEND_ACCIDENT_EVT);

    sendDown(wsm->dup());
    cout << "Vehicle sends Accident Report Message(ARM) at: " << simTime() << " with location=" << wsm->getA_location()<<"speed="<<wsm->getA_speed()<< endl;
}

void VehicleAppl::finish()
{
    VehicleAppl::finish();
}

bool VehicleAppl::isAmbulance() {
    return vehicleSumoTypeId == "emergency";
}

bool VehicleAppl::isNormalVehicle() {
    return vehicleSumoTypeId == "normal";
}
