#include <omnetpp.h>
#include <cmath>
#include <string>

using namespace omnetpp;

class Source : public cSimpleModule {
private:
    cMessage *event;
    simtime_t timeout;
    int pConstant;
    double pLambda;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Source);

void Source::initialize() {
    event = new cMessage("event");
    pConstant = 5;
    pLambda = 0.1;
    scheduleAt(simTime(), event);
}

void Source::handleMessage(cMessage *msg) {
    if (msg == event) {
        // Generate a random time interval using exponential distribution
        double pRandomTime = exponential(1 / pLambda);
        scheduleAt(simTime() + pRandomTime, event);

        // Adjust the constant parameter
        pConstant = (pConstant == 0) ? 10 : pConstant - 1;

        // Create and send a new message
        cMessage *msg = new cMessage("MESSAGE_FROM_SOURCE");
        send(msg, "out");
    }
}
