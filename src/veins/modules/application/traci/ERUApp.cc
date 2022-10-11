#include <cmath>
#include <veins/modules/application/traci/ERUApp.h>
#include "veins/modules/application/traci/AccidentMessage_m.h"

using namespace veins;
Define_Module(veins::ERUApp);
void ERUApp::handleMessage(cMessage *msg)
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
            else if (msg->getArrivalGateId() == rsuIn) {
                EV << "Pacote veio pela rsu" << endl;
                handleLowerMsg(msg);
            }
            else if (msg->getArrivalGateId() == firstHospitalIn || msg->getArrivalGateId() == secondHospitalIn) {
                            EV << "Pacote veio por um dos hospitais" << endl;
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
void ERUApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    rsuIn = findGate("rsuIn");
    rsuOut = findGate("rsuOut");
    firstHospitalIn = findGate("firstHospitalIn");
    firstHospitalOut = findGate("firstHospitalOut");
    secondHospitalIn = findGate("secondHospitalIn");
    secondHospitalOut = findGate("secondHospitalOut");

    firstHospital.x = 5000;
    firstHospital.y = 200;
    secondHospital.x = 5000;
    secondHospital.y = 3000;
}

void ERUApp::handleSelfMsg(cMessage* msg)
{
    EV << "Entrou aqui!" << std::endl;
    DemoBaseApplLayer::handleSelfMsg(msg);
    {
        switch (msg->getKind())
        {
        case SEND_BEACON_EVT:
        {
            std::cout<<"ERU handleselfmsg on beacon evnt"<<endl;
            EV<<"ERU handleselfmsg on beacon evnt"<<endl;
            break;
        }
        case SEND_WSA_EVT:
        {
            std::cout<<"ERU handleselfmsg on wsa evnt"<<endl;
            EV<<"ERU handleselfmsg on wsa evnt"<<endl;
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
void ERUApp::onWSM(BaseFrame1609_4* frame)
{
   std::cout<<"ERU received accident information from RSU"<<endl;
   AccidentMessage* wsm = check_and_cast<AccidentMessage*>(frame);

   int nearestHospital = getNearestHospital(wsm->getA_location(), firstHospital, secondHospital);
   if (nearestHospital == 1) {
       send(wsm->dup(), "firstHospitalOut");
   }
   if (nearestHospital == 2) {
       send(wsm->dup(), "secondHospitalOut");
   }
   std::cout<<"ERU forward accident information to first Hospital"<<endl;
}
void ERUApp::finish()
{
    DemoBaseApplLayer::finish();
}


int ERUApp::getNearestHospital(Coord accidentLocation, Coord first, Coord second) {
    double distanceFromFirst = sqrt(
            pow(std::abs(accidentLocation.x - first.x), 2) +
            pow(std::abs(accidentLocation.y - first.y), 2));
    EV << "First hospital's distance from accident is " << distanceFromFirst << endl;
    double distanceFromSecond = sqrt(
                pow(std::abs(accidentLocation.x - second.x), 2) +
                pow(std::abs(accidentLocation.y - second.y), 2));
    EV << "Second hospital's distance from accident is " << distanceFromSecond << endl;

    if (distanceFromFirst < distanceFromSecond) {
        return 1;
    }

    return 2;
}
