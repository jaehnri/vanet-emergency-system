package org.car2x.veins.base.modules;

// Interface for application layer modules
moduleinterface IERUApplLayer extends IBaseApplLayer
{
    
    gates:
        input hospitalIn;
        output hospitalOut;
        input rsuIn;
        output rsuOut;
}