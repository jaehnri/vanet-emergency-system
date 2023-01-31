#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class NicEth: public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    int wireIn;
    int wireOut;
    int internalWireIn;
    int internalWireOut;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(NicEth);


void NicEth::initialize()
{
    cMessage *msg = new cMessage("tictocMsg");
    wireIn = findGate("wire$i");
    wireOut = findGate("wire$o");
    internalWireIn = findGate("internalWireIn");
    internalWireOut = findGate("internalWireOut");
    //sendDelayed(msg, simTime() + exponential(5.0), "internalWireOut");
}

void NicEth::handleMessage(cMessage *msg)
{
    EV << "Entrou no handle message Eth";
    if(msg->getArrivalGateId() == wireIn) {
        send(msg->dup(), "internalWireOut");
    } else if (msg->getArrivalGateId() == internalWireIn) {

        cGate *outGate = gate(wireOut);
        if(outGate->isPathOK()) {
            send(msg->dup(), "wire$o");
        }
        else {
            EV << "\nDiscarted beacon\n";
        }

    } else if (msg->getArrivalGateId() == -1) {
        /* Classes extending this class may not use all the gates, f.e.
         * BaseApplLayer has no upper gates. In this case all upper gate-
         * handles are initialized to -1. When getArrivalGateId() equals -1,
         * it would be wrong to forward the message to one of these gates,
         * as they actually don't exist, so raise an error instead.
         */
        throw cRuntimeError("No self message and no gateID?? Check configuration.");
    }
    else {
        /* msg->getArrivalGateId() should be valid, but it isn't recognized
         * here. This could signal the case that this class is extended
         * with extra gates, but handleMessage() isn't overridden to
         * check for the new gate(s).
         */
        throw cRuntimeError("Unknown gateID?? Check configuration or override handleMessage().");
    }
    //scheduleAt(simTime() + exponential(1.0), msg);

    //send(msg, "wire$o");
}
