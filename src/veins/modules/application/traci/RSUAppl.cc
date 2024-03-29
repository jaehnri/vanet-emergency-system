#include "veins/modules/application/traci/RSUAppl.h"
#include "veins/modules/messages/TraCIDemo11pMessage_m.h"
#include "veins/modules/messages/AccidentMessage_m.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include <veins/modules/messages/A2TMessage11p_m.h>
#include <veins/veins.h>



using namespace veins;
Define_Module(veins::RSUAppl);
void RSUAppl::handleMessage(cMessage *msg)
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
        else if (strcmp(msg->getArrivalGate()->getName(), "rsuGates$i") == 0) {
            lastGateReceived = msg->getArrivalGate()->getIndex();
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

void RSUAppl::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    rsuConnections = par("rsuCount");
    eruConnections = par("eruCount");

}
void RSUAppl::handleSelfMsg(cMessage* msg)
{
    EV << "HandleSelfMsg()";
    {    //DemoBaseApplLayer::handleSelfMsg(msg);

        switch (msg->getKind())
        {
        case SEND_BEACON_EVT:
        {
            DemoSafetyMessage* bsm = new DemoSafetyMessage();
            //TraCIDemo11pMessage* bsm= new TraCIDemo11pMessage();
            populateWSM(bsm);
            sendDown(bsm);
            scheduleAt(simTime() + beaconInterval, sendBeaconEvt);
            std::cout<<"RSU is sending a Beacon event"<<endl;
            EV<<"RSU is sending a Beacon event"<<endl;
            break;
        }
        case SEND_WSA_EVT:
        {
            DemoServiceAdvertisment* wsa = new DemoServiceAdvertisment();
            populateWSM(wsa);
            sendDown(wsa);
            scheduleAt(simTime() + wsaInterval, sendWSAEvt);
            std::cout<<"RSU is sending a WSA event"<<endl;
            EV<<"RSU is sending a WSA event"<<endl;
            break;
        }

        default:
        {
            if (msg) EV_WARN << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
        }
    }
}

/*
 * Forwards message to all rsu gates except one.
 */
void RSUAppl::forwardAccidentMsgExcept(AccidentMessage* wsm, int receivedFromIndex) {
    for(int i = 0; i < rsuConnections; i++) {
        if(i != receivedFromIndex) send(wsm->dup(), "rsuGates$o", i);
    }

}

/*
 * Forwards message to all rsu gates.
 */
void RSUAppl::forwardAccidentMsgAll(AccidentMessage* wsm) {
    for(int i = 0; i < rsuConnections; i++) {
        send(wsm->dup(), "rsuGates$o", i);
    }

}

void RSUAppl::onWSM(BaseFrame1609_4* frame) {
    if (frame->getKind() == SEND_ACCIDENT_EVT) {
        AccidentMessage* wsm = check_and_cast<AccidentMessage*>(frame);
        EV << "Received Accident Message from Gate: " << lastGateReceived << endl;
        AccidentMessage* newWsm = wsm->dup();
        newWsm->setA_isFromVehicle(false);
        if(eruConnections > 0) {
            EV << "RSU with ERU\n";
            send(newWsm, "eruGates$o", 0);
        }

        else
            if(!wsm->getA_isFromVehicle())
                forwardAccidentMsgExcept(newWsm, lastGateReceived);
            else
                forwardAccidentMsgAll(newWsm);
        std::cout<<"RSU forward accident message"<<endl;
    }
    if (frame->getKind() == SEND_OPEN_TRAFFIC_LIGHT_EVT) {
            A2TMessage11p* wsm = check_and_cast<A2TMessage11p*>(frame);
            sendDown(wsm->dup());
    }
}



void RSUAppl::finish()
{
    DemoBaseApplLayer::finish();
}



