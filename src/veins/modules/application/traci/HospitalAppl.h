#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
//#include "veins/modules/mobility/traci/TraCIMobility.h"
//#include "veins/modules/mobility/traci/TraCICommandInterface.h"
using namespace omnetpp;
//using veins::TraCICommandInterface;
//using veins::TraCIMobility;
namespace veins {

class VEINS_API HospitalAppl : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;
    void finish() override;

protected:
    //Additions
    void handleMessage(cMessage *msg) override;
      //TraCICommandInterface* traci;
   void onWSM(BaseFrame1609_4* wsm) override;
    cMessage* sendAcdntEvt; //added
    void handleSelfMsg(cMessage* msg) override;
     void setTraCI();
};

} // namespace veins
