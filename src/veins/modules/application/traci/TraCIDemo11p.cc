#include "veins/modules/application/traci/TraCIDemo11p.h"
#include "veins/modules/application/traci/AccidentMessage_m.h"
#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"
#include <string.h>
using namespace veins;
using namespace std;
Define_Module(veins::TraCIDemo11p);

void TraCIDemo11p::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
        accidentmessagetinterval = par("ACCIDENTMESSAGETINTERVAL");
        sendAcdntEvt = new cMessage("Accident event at DemoBaseApplLayer", SEND_ACCIDENT_EVT);
        //Get back here
        scheduleAt(simTime() + accidentmessagetinterval + exponential(5.0), sendAcdntEvt);
   }
}
void TraCIDemo11p::onWSM(BaseFrame1609_4 *frame) {

}

void TraCIDemo11p::handleSelfMsg(cMessage *msg)
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
void TraCIDemo11p::sendAccidentMessage() // assigned array indexed values to wsm fields and send it.
{

    //if (mobility->getSpeed()<1)
    //if(traciVehicle->getAcceleration()<1)

    EV << "Seding accident message";

    AccidentMessage *wsm = new AccidentMessage();
    populateWSM(wsm);
    wsm->setA_description("Emergency situation, an accident happens at the location 0.0. 0.0");
    wsm->setA_location(curPosition);
    wsm->setA_speed(traciVehicle->getSpeed());
        //if ((strcmp(findHost()->getFullName(), "node[0]") == 0 && wsm->getA_speed()<1))
        //{
    sendDown(wsm->dup());
    //scheduleAt(simTime() + accidentmessagetinterval, sendAcdntEvt);
    cout << "Vehicle sends Accident Report Message(ARM) at: " << simTime() << " with location=" << wsm->getA_location()<<"speed="<<wsm->getA_speed()<< endl;
    //}
    }
void TraCIDemo11p::finish()
{
    TraCIDemo11p::finish();
}
