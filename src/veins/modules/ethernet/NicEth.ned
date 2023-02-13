package org.car2x.veins.modules.ethernet;

simple NicEth
{
    parameters:
        int wireCount = default(1);
    
    gates:
        inout wires[wireCount];
        inout internalWires[wireCount];
}