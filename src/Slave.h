//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SLAVE_H_
#define SLAVE_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "Message.h"
#include "State.h"

using namespace omnetpp;


namespace earthquakedetector {

int knowledge = 0;
int interactivity = 0;

class Slave : public cSimpleModule{
    public:
        Slave();
        virtual ~Slave();

    private:
        simsignal_t energySignal;
        simsignal_t knowledgeSignal;
        simsignal_t interactivitySignal;
        State* state;
        long numSent;
        long numReceived;
        long numLost;
        bool isClusterHead = false;
        //int** network;
        int id;
        int numCH; //number of Cluster Head
        int numCHnear;
        int numSN;
        int numACKsn;
        int numACKch;
        int gateCHConfig[4]{0};
        int gateSNConfig[2]{0};
        int rowNet;
        int colNet;
        int sendEnergy;

    protected:
        virtual Message *generateMessage(int kindMsg);
        virtual void broadcastInCluster(Message *msg);
        virtual void broadcastToNearCH(Message *msg);
        virtual void forwardMessage(Message *msg);
        virtual void initialize() override;
        virtual void handleMessage(cMessage *cmsg) override;
        virtual void refreshDisplay() const override;
        //virtual int** createNetwork(int **&net, int row, int col);
        //virtual void fillNetwork();
        //virtual void printNetwork() const;
        virtual float retransmitMsg(Message *msg, float delay);
};

} /* namespace earthquakedetector */

#endif /* SLAVE_H_ */
