#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

namespace veins {

class VEINS_API TrafficLightRSU : public DemoBaseApplLayer {

public:
    void initialize(int stage) override;

protected:
    // ---------------------- Simulation parameters ----------------------
    /**
     * <!> These parameters are set in the omnetpp.ini file <!>
     */
    simtime_t reinitializationDelay; /* Time after which the RSU resets if it has not been updated (in seconds) */
    // ---------------------- Simulation parameters ----------------------

    bool initialized;           /* Initialization state of the RSU */
    std::string associatedTlId; /* ID of the traffic light associated to the RSU */
    long lastMessageTreeId;     /* Tree ID of the last message received */
    simtime_t lastUpdate;       /* Time of the last update */
    int memorizedAmuId; /* Ambulance ID memorized by the RSU */
    int highestPriority;        /* Highest priority recorded */

    //
    TraCICommandInterface::Trafficlight* traciTl;

protected:
    void onWSM(BaseFrame1609_4* wsm) override;

private:
    /**
     * Set up the TraCI interface
     */
    void setTraCI();

    /**
     * Associate a close traffic light with the RSU
     */
    void associateTrafficlight();

    /**
     * Update the RSU information
     * @param memorizedAmuId Ambulance ID memorized
     * @param highestPriority Highest priority recorded
     */
    void update(int memorizedAmuId, int highestPriority);

    /**
     * Open other traffic lights that
     * control lane in the Ambulance's
     * route
     */
    void openTraffic(std::string amuLaneId);
};

} // namespace Veins

