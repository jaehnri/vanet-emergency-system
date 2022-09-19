#include <veins/modules/application/traci/HospitalApp.h>
#include "veins/modules/application/traci/AccidentMessage_m.h"
#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"

//#include "veins/modules/application/traci/TraCIDemo11p.h"
//#include "veins/modules/mobility/traci/TraCIMobility.h"
#include <string.h>
using namespace veins;
Define_Module(veins::HospitalApp);
void HospitalApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0)
    {

    }
    else if (stage == 1)
    {
    }
}

void HospitalApp::onWSM(BaseFrame1609_4* frame)
{
   std::cout<<"Hospital received accident information from ERU"<<endl;
   setTraCI();
}
void HospitalApp::handleSelfMsg(cMessage *msg) {
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
void HospitalApp::finish()
{
    DemoBaseApplLayer::finish();
}
void HospitalApp::setTraCI()
{
    veins::TraCIScenarioManager* manager = veins::TraCIScenarioManagerAccess().get();
    traci = manager->getCommandInterface();
    traci->addVehicle("testvehicle", "car", "right2left-traffic");
    traci->DEPART_POSITION_RANDOM;
    std::cout<<"Hospital Send out an ambulance to the accident location"<<endl;
}

