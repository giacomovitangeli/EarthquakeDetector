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

#include "Master.h"
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "Message.h"

namespace earthquakedetector{

Define_Module(Master);

Master::Master() {
    // TODO Auto-generated constructor stub

}

Master::~Master() {
    // TODO Auto-generated destructor stub
}


void Master::initialize()
{
    // Initialize variables
        id = 0;
        initNetwork();
        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
        int kindPower = 0; //power message
        int kindNetDet = 1; //request netdet message

        //POWER to the slaves
        Message *power = generateMessage(kindPower);
        scheduleAt(0.0, power);

        //NET DETECTION
        Message *requestNetDet = generateMessage(kindNetDet);
        scheduleAt(0.01, requestNetDet);

}

void Master::handleMessage(cMessage *cmsg)
{
    Message *msg = check_and_cast<Message *>(cmsg);

        if(msg->getDestination() == this->id)
        {
            if(msg->getKindMsg() == 2)//ack netdet
            {
                int row = msg->getSource() - 1;
                for(int i=0; i<3; i++)
                    this->network[row][i] = msg->getPos()[i];

                delete msg;
                numReceived++;
                bubble("ACK ARRIVED!");
                printNetwork();
            }
        }
        else if(msg->getDestination() == 1000000){
            broadcastMessage(msg);
        }
        else
        {
            // We need to forward the message.
            forwardMessage(msg);
        }
}

Message *Master::generateMessage(int kindMsg)
{
    int src = id;
    int dest;
    char msgname[24];

    //kind==0 --> POWER
    //kind==1 --> NET DETECTION
    if((kindMsg == 0) || (kindMsg == 1))
    {
        dest = 1000000; //broadcast message
        if(kindMsg == 0)
            sprintf(msgname, "power-master-to-all");
        else if(kindMsg == 1)
            sprintf(msgname, "NetDet-master-to-all");
    }

    //char msgname[20];
    //sprintf(msgname, "msg-%d-to-%d", src, dest);

    // Create message object and set source and destination field.
    Message *msg = new Message(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    msg->setKindMsg(kindMsg);
    return msg;
}



void Master::broadcastMessage(Message *msg)
{
    int n = 8; //number of cluster head
    int k = 1;
    if(msg->getKindMsg() == 0)// pwr msg
        n = gateSize("gate");

    for (int i=0; i<n; i++)
    {
        Message *copy = msg->dup();
        if(copy->getKindMsg() == 1) //net detection kind
        {
            copy->setNetDetId(k);
            k++;
        }
        EV << "Broadcasting message " << copy << " on gate[" << i << "]\n";
        numSent++;
        send(copy, "gate$o", i);
    }
    delete msg;
}

void Master::forwardMessage(Message *msg)
{
        // Increment hop count.
        msg->setHopCount(msg->getHopCount()+1);

        // Same routing as before: random gate.
        int n = gateSize("gate");
        int k = intuniform(0, n-1);

        EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
        send(msg, "gate$o", k);
}

void Master::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

void Master::initNetwork()
{
    for(int i=0; i<8; i++){
        for(int j=0; j<3; j++){
            network[i][j] = 0;
        }
    }
}

void Master::printNetwork()
{
    EV <<"network: \n";
    for(int i=0; i<8; i++){
        for(int j=0; j<3; j++){
            EV <<" ["<<network[i][j]<<"] ";
        }
        EV<<"\n";
    }
}


}; // namespace
