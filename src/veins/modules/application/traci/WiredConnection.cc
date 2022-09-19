#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class WiredConnection: public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(WiredConnection);


void WiredConnection::initialize()
{
    cMessage *msg = new cMessage("tictocMsg");
    sendDelayed(msg, simTime() + exponential(5.0), "wire$o");
}

void WiredConnection::handleMessage(cMessage *msg)
{
    sendDelayed(msg, simTime() + exponential(5.0), "wire$o");
    //scheduleAt(simTime() + exponential(1.0), msg);

    //send(msg, "wire$o");
}
