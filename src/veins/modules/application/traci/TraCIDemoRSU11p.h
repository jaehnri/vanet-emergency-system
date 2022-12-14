#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"  //added kafe

namespace veins {

class VEINS_API TraCIDemoRSU11p : public DemoBaseApplLayer {
public:
    void initialize(int stage) override;

    //kafe code
    int ID;
    int category;//change
    opp_string name;
    double x_cord;
    double y_cord;
    opp_string address;
    opp_string description;
    int lifeTimeofService;
    int counting;
    int count_service;
    //end
    void finish() override;

protected:
        //Additions
        void handleMessage(cMessage *msg) override;
        int eruIn;
        int eruOut;
        //End of additions
        void handleSelfMsg(cMessage* msg) override;
        bool sentMessage;
        int firstService;
        int serviceSendNow;
        int numRSU;
        int lastService;
        int ttl;
        double serviceInterval;
        //cMessage* serviceAdvertisementEvent; //need to change to cMessage* sendAdvEvt
        void sendAdvertisement(int var);
        void onWSM(BaseFrame1609_4* wsm) override;


public:
    void prepareServices();
    //end
};
} // namespace veins
