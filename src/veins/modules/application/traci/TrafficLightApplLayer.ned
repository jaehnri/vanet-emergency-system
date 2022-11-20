package org.car2x.veins.modules.application.traci;
import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;
import org.car2x.veins.base.modules.ITrafficLightApplLayer;
simple TrafficLightApplLayer extends DemoBaseApplLayer like ITrafficLightApplLayer
{
    @class(veins::TrafficLightApplLayer);
    gates:
        inout logic;
}

