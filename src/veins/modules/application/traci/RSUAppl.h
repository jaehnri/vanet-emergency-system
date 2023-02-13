#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"  //added kafe
#include "veins/modules/messages/AccidentMessage_m.h"

namespace veins {

class VEINS_API RSUAppl : public DemoBaseApplLayer {
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

    // number of rsu's connected to this rsu.
    int rsuConnections;
    int eruConnections;
    int lastGateReceived;

protected:
        //Additions
        void handleMessage(cMessage *msg) override;
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
        void forwardAccidentMsgExcept(AccidentMessage* wsm, int receivedFromIndex);
        void forwardAccidentMsgAll(AccidentMessage* wsm);


public:
    void prepareServices();
    //end
};
} // namespace veins
