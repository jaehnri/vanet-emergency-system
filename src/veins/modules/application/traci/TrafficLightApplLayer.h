#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
using namespace omnetpp;
namespace veins
{
class VEINS_API TrafficLightApplLayer : public DemoBaseApplLayer
{
protected:
    simtime_t lastDroveAt;
    bool sentMessage;
    int currentSubscribedServiceId;
    double accidentmessagetinterval; //added
    cMessage* sendAcdntEvt; //added
    TraCIMobility* mobility;
  };
}// namespace veins

