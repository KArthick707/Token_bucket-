#include <omnetpp.h>
#include <queue>

using namespace omnetpp;

class Server : public cSimpleModule {
private:
    int max_tokens;
    int token_num;
    simtime_t timeout;
    cMessage *event;
    std::queue<cMessage *> queue;
    int max_queue_size;

public:
    Server();
    virtual ~Server();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Server);

Server::Server() : event(nullptr) {}

Server::~Server() {
    cancelAndDelete(event);
}

void Server::initialize() {
    max_tokens = par("token_limit");
    max_queue_size = par("queue_limit");
    token_num = max_tokens;
    WATCH(token_num);
    timeout = 0.05;
    event = new cMessage("event");
    scheduleAt(simTime() + timeout, event);
}

void Server::handleMessage(cMessage *msg) {
    if (msg == event) {
        if (token_num < max_tokens) {
            token_num++;
            EV << "Token count incremented to " << token_num << "\n";
        }

        while (!queue.empty() && token_num > 0) {
            cMessage *new_msg = queue.front();
            queue.pop();
            send(new_msg, "out");
            token_num--;
            EV << "Token count after sending: " << token_num << "\n";
        }

        scheduleAt(simTime() + timeout, event);
    } else {
        EV << "Message received from source\n";

        if (queue.size() < max_queue_size) {
            EV << "Inserting data in queue\n";
            queue.push(msg);
        } else {
            delete msg;
        }

        while (!queue.empty() && token_num > 0) {
            cMessage *new_msg = queue.front();
            queue.pop();
            send(new_msg, "out");
            token_num--;
            EV << "Token count after sending: " << token_num << "\n";
        }
    }
}
