package org.car2x.veins.modules.application.traci;
import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;
import org.car2x.veins.base.modules.IRSUApplLayer;
simple RSUAppl extends DemoBaseApplLayer like IRSUApplLayer
{
        @class(veins::RSUAppl);
        @display("i=block/app2");
        
	gates:
        input eruIn;
        output eruOut;
       
}
