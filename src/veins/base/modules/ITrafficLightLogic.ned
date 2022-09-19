package org.car2x.veins.base.modules;

// Interface for signal controller logic of traffic lights
moduleinterface ITrafficLightLogic
{
    parameters:
        @display("i=block/classifier");
    gates:
        inout interface;
        inout applLayer;
}
