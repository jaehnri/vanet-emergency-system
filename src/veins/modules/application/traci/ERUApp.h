#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
using namespace omnetpp;
namespace veins {

class VEINS_API ERUApp : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;
    void finish() override;

protected:
    //Additions
    void handleMessage(cMessage *msg) override;
    int rsuIn;
    int rsuOut;
    int hospitalIn;
    int hospitalOut;
    //void onBSM(DemoSafetyMessage* bsm) override;
    void onWSM(BaseFrame1609_4* wsm) override;
    //void onWSA(DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    //void handlePositionUpdate(cObject* obj) override;
};

} // namespace veins
