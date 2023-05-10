
#include <veins/modules/application/traci/HospitalAppl.h>
#include "veins/modules/messages/AccidentMessage_m.h"
#include "veins/modules/messages/TraCIDemo11pMessage_m.h"

//#include "veins/modules/application/traci/VehicleAppl.h"
//#include "veins/modules/mobility/traci/TraCIMobility.h"
#include <string.h>
using namespace veins;
Define_Module(veins::HospitalAppl);
void HospitalAppl::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
                handleSelfMsg(msg);
            }
            else if (msg->getArrivalGateId() == upperLayerIn) {
                recordPacket(PassedMessage::INCOMING, PassedMessage::UPPER_DATA, msg);
                handleUpperMsg(msg);
            }
            else if (msg->getArrivalGateId() == upperControlIn) {
                recordPacket(PassedMessage::INCOMING, PassedMessage::UPPER_CONTROL, msg);
                handleUpperControl(msg);
            }
            else if (msg->getArrivalGateId() == lowerControlIn) {
                recordPacket(PassedMessage::INCOMING, PassedMessage::LOWER_CONTROL, msg);
                handleLowerControl(msg);
            }
            else if (msg->getArrivalGateId() == lowerLayerIn) {
                recordPacket(PassedMessage::INCOMING, PassedMessage::LOWER_DATA, msg);
                handleLowerMsg(msg);
            }
            else if (strcmp(msg->getArrivalGate()->getName(), "eruGates$i") == 0) {
                recordPacket(PassedMessage::INCOMING, PassedMessage::LOWER_DATA, msg);
                handleLowerMsg(msg);
            }
            else if (msg->getArrivalGateId() == -1) {
                /* Classes extending this class may not use all the gates, f.e.
                 * BaseApplLayer has no upper gates. In this case all upper gate-
                 * handles are initialized to -1. When getArrivalGateId() equals -1,
                 * it would be wrong to forward the message to one of these gates,
                 * as they actually don't exist, so raise an error instead.
                 */
                throw cRuntimeError("No self message and no gateID?? Check configuration.");
            }
            else {
                /* msg->getArrivalGateId() should be valid, but it isn't recognized
                 * here. This could signal the case that this class is extended
                 * with extra gates, but handleMessage() isn't overridden to
                 * check for the new gate(s).
                 */
                throw cRuntimeError("Unknown gateID?? Check configuration or override handleMessage().");
            }
}
void HospitalAppl::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    EV << "Hospital Index" << getParentModule()->getIndex() << endl;

}

void HospitalAppl::onWSM(BaseFrame1609_4* frame)
{
   std::cout<<"Hospital received accident information from ERU"<<endl;
   setTraCI();
}
void HospitalAppl::handleSelfMsg(cMessage *msg) {
    switch (msg->getKind()) {
    case SEND_BEACON_EVT: {
        DemoSafetyMessage *bsm = new DemoSafetyMessage();
        populateWSM(bsm);
        sendDown(bsm);
        scheduleAt(simTime() + beaconInterval, sendBeaconEvt);
        break;
    }
    case SEND_WSA_EVT: {
        DemoServiceAdvertisment *wsa = new DemoServiceAdvertisment();
        populateWSM(wsa);
        sendDown(wsa);
        scheduleAt(simTime() + wsaInterval, sendWSAEvt);
        break;
    }

    default: {
        if (msg)
            EV_WARN << "APP: Error: Got Self Message of unknown kind! Name: "
            << msg->getName() << endl;
        break;
    }
    }
}
void HospitalAppl::finish()
{
    DemoBaseApplLayer::finish();
}
void HospitalAppl::setTraCI()
{
    veins::TraCIScenarioManager* manager = veins::TraCIScenarioManagerAccess().get();
    traci = manager->getCommandInterface();
    if(getParentModule()->getIndex() == 0)
        traci->addVehicle("testvehicle", "emergency", "amu_route_1");
    else
        traci->addVehicle("testvehicle", "emergency", "amu_route_2");
    traci->DEPART_POSITION_RANDOM;
    std::cout<<"Hospital sent out an ambulance to the accident location"<<endl;
}

