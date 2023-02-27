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
    bool isAmbulance();
    bool isNormalVehicle();
protected:
    //Vehicle identification
    int vehicleVeinsId;
    std::string vehicleSumoId;
    std::string vehicleSumoTypeId;

    simtime_t lastDroveAt;
    bool sentMessage;
    int currentSubscribedServiceId;
    double accidentmessagetinterval; //added
    cMessage* sendAcdntEvt; //added
    TraCIMobility* mobility;

    simtime_t broadcastInterval; /* Interval between broadcasts */
    simtime_t lastBroadcastAt;   /* [AMU] Simulation time of the last message broadcasted */
    int priority;                /* Priority of the vehicle */

    Coord accidentLocation;
protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;
    void sendAccidentMessage();    //added
  };
}// namespace veins
