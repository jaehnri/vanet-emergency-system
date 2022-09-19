#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
//#include "veins/modules/mobility/traci/TraCIMobility.h"
//#include "veins/modules/mobility/traci/TraCICommandInterface.h"
using namespace omnetpp;
//using veins::TraCICommandInterface;
//using veins::TraCIMobility;
namespace veins {

class VEINS_API HospitalApp : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;
    void finish() override;

protected:

      //TraCICommandInterface* traci;
   void onWSM(BaseFrame1609_4* wsm) override;
    cMessage* sendAcdntEvt; //added
    void handleSelfMsg(cMessage* msg) override;
     void setTraCI();
};

} // namespace veins
