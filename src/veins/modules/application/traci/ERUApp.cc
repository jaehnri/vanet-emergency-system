#include <veins/modules/application/traci/ERUApp.h>
#include "veins/modules/application/traci/AccidentMessage_m.h"
using namespace veins;
Define_Module(veins::ERUApp);
void ERUApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0)
    {
    }
    else if (stage == 1)
    {
    }
}
void ERUApp::handleSelfMsg(cMessage* msg)
{
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
   sendDown(wsm->dup()); //change
   std::cout<<"ERU forward accident information to Hospital"<<endl;
}
void ERUApp::finish()
{
    DemoBaseApplLayer::finish();
}
