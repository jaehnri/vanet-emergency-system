#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
using namespace omnetpp;
namespace veins
{
class VEINS_API TraCIDemo11p : public DemoBaseApplLayer
{
public:
    void initialize(int stage) override;
    void finish() override;
protected:
    simtime_t lastDroveAt;
    bool sentMessage;
    int currentSubscribedServiceId;
    double accidentmessagetinterval; //added
    cMessage* sendAcdntEvt; //added
    void sendAccidentMessage();    //added
    TraCIMobility* mobility;
protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void handleSelfMsg(cMessage* msg) override;
  };
}// namespace veins
