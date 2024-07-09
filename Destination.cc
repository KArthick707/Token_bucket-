#include <omnetpp.h>

using namespace omnetpp;

class Destination : public cSimpleModule {
protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Destination);

void Destination::handleMessage(cMessage *msg) {
    EV << "MESSAGE_FROM_THE_SERVER_Q&T\n";
    EV << msg << "\n";
    delete msg;
}
