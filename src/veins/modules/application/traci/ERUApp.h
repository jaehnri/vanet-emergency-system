#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/application/traci/HospitalInfo.h"

using namespace omnetpp;
namespace veins {

class VEINS_API ERUApp : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;
    void finish() override;
    HospitalInfo firstHospital;
    HospitalInfo secondHospital;

protected:
    //Additions
    void handleMessage(cMessage *msg) override;
    int rsuIn;
    int rsuOut;
    int firstHospitalIn;
    int firstHospitalOut;
    int secondHospitalIn;
    int secondHospitalOut;

    //void onBSM(DemoSafetyMessage* bsm) override;
    void onWSM(BaseFrame1609_4* wsm) override;
    //void onWSA(DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    //void handlePositionUpdate(cObject* obj) override;

    int getNearestHospital(Coord accidentLocation, HospitalInfo first, HospitalInfo second);
};

} // namespace veins
