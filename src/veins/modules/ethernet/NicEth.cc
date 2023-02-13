#include <string.h>
#include <omnetpp.h>
#include "veins/modules/messages/AccidentMessage_m.h"

using namespace omnetpp;

class NicEth: public cSimpleModule
{
  protected:
    int wireCount;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  private:
    void forwardMessage(cMessage *msg, std::string outGateName, int gateIndex);
};

// The module class needs to be registered with OMNeT++
Define_Module(NicEth);


void NicEth::initialize()
{
    /*
     * Get wireCount parameter and find gates;
     */
    wireCount = par("wireCount");

}

/*
 * Forwards message to application layer or to the external wires
 */
void NicEth::forwardMessage(cMessage *msg, std::string outGateName, int gateIndex) {
    const std::string outGatePath = outGateName + "$o";
    cGate* outGate = gate(findGate(outGatePath.c_str(), gateIndex));
    if(outGate->isPathOK()) {
        send(msg->dup(), outGate);
    } else {
        EV << "\nDiscarted Message";
    }
}

void NicEth::handleMessage(cMessage *msg)
{
    cGate *msgGate = msg->getArrivalGate();
    int gateIndex = msgGate->getIndex();
    // Send message through external wires
    if(strcmp(msgGate->getName(), "internalWires$i") == 0) {
        forwardMessage(msg, "wires", gateIndex);
    // Send message through internal wires
    } else if (strcmp(msgGate->getName(), "wires$i") == 0) {
        forwardMessage(msg, "internalWires", gateIndex);
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
