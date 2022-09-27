#include "veins/modules/application/traci/TraCIDemoRSU11p.h"
#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"
#include "veins/modules/application/traci/AccidentMessage_m.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"



using namespace veins;
Define_Module(veins::TraCIDemoRSU11p);
void TraCIDemoRSU11p::handleMessage(cMessage *msg)
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
        else if (msg->getArrivalGateId() == eruIn) {
            EV << "Pacote veio pelo fio";
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

void TraCIDemoRSU11p::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    eruIn = findGate("eruIn");
    eruOut = findGate("eruOut");
    if (stage == 0)
    {
        //mobility= TraCIMobilityAccess().get(getParentModule());
        //traci=mobility->getCommandInterface();
        //traciVehicle=mobility->getVehicleCommandInterface();


     }
    else if (stage == 1)
    {

    }
}
void TraCIDemoRSU11p::handleSelfMsg(cMessage* msg)
{
    EV << "HandleSelfMsg()";
    //DemoBaseApplLayer::handleSelfMsg(msg);
    {
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
void TraCIDemoRSU11p::onWSM(BaseFrame1609_4* frame)
{
   std::cout<<"RSU received accident information from vehicle"<<endl;
   AccidentMessage* wsm = check_and_cast<AccidentMessage*>(frame);
   sendDelayedDown(wsm->dup(), 2 + uniform(0.01, 0.2)); //change
  //send(wsm->dup(), "radioin");
   std::cout<<"RSU forward accident information to Emergency Center"<<endl;
   //traci->addVehicle("testvehicle", "car", "left2right-traffic");


}



void TraCIDemoRSU11p::finish()
{
    DemoBaseApplLayer::finish();
}



