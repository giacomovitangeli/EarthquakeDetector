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

#include "Slave.h"
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "Message.h"

namespace earthquakedetector{

Define_Module(Slave);

Slave::Slave() {
    // TODO Auto-generated constructor stub

}

Slave::~Slave() {
    // TODO Auto-generated destructor stub
}


void Slave::initialize()
{
    // Initialize variables

        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
        batteryState = intuniform(0, 75);
        numCS = 8;
        numSN = 2;
        numACKsn = 0;
}

void Slave::handleMessage(cMessage *cmsg)
{
    Message *msg = check_and_cast<Message *>(cmsg);

        if(msg->getDestination() == 1000000) //dest == 1000000 -> broadcast
        {
            numReceived++;

            if(msg->getKindMsg() == 0) //kind == 0 -> power
            {
                batteryState += 25;
                if(batteryState > 100)
                    batteryState = 100;

                delete msg;
                bubble("Power Arrived! +25%");
                EV << "Battery state: " << batteryState << "%"<<"\n";

            }
            else if(msg->getKindMsg() == 1) //kind == 1 -> net detection
            {
                this->id = msg->getNetDetId();
                this->isClusterHead = true;
                delete msg;

                if(id == 1){
                    position[0] = 624.275;
                    position[1] = 200;
                    position[2] = 3;//(float)(intuniform(0, 10));
                }else if(id == 2){
                    position[0] = 800;
                    position[1] = 374.275;
                    position[2] = 3;//(float)(intuniform(0, 10));

                }else if(id == 3){
                    position[0] = 800;
                    position[1] = 624.275;
                    position[2] = 3;//(float)(intuniform(0, 10));

                }else if(id == 4){
                    position[0] = 624.275;
                    position[1] = 800;
                    position[2] = 3;

                }else if(id == 5){
                    position[0] = 374.275;
                    position[1] = 800;
                    position[2] = 3;//(float)(intuniform(0, 10));

                }else if(id == 6){
                    position[0] = 200;
                    position[1] = 624.275;
                    position[2] = 3;//(float)(intuniform(0, 10));

                }else if(id == 7){
                    position[0] = 200;
                    position[1] = 374.275;
                    position[2] = 3;//(float)(intuniform(0, 10));

                }else if(id == 8){
                    position[0] = 374.275;
                    position[1] = 200;
                    position[2] = 3;//(float)(intuniform(0, 10));

                }else{
                    position[0] = 0;//(float)(intuniform(0, 1000));
                    position[1] = 0;//(float)(intuniform(0, 1000));
                    position[2] = 0;//(float)(intuniform(0, 10));
                }

                bubble("Request NetDet Arrived!");
                EV << "Slave "<< id <<" is in position: [" << position[0] <<", "<< position[1] <<", "<< position[2] <<"] "<<"\n";


                //todo inoltrare la req netdet ai sottonodi

                int kindNetDetsn = 3; //kind net det subnode
                Message *reqNetDetsn = generateMessage(kindNetDetsn);
                scheduleAt(0.1, reqNetDetsn);

            }
        }else if(msg->getDestination() == 2000000){ //dest == 2000000 --> broadcast in cluster

            if(msg->getKindMsg() == 3)
            {
                if(isClusterHead)
                {
                    broadcastInCluster(msg);

                }else{//is sub-node
                    this->id = msg->getNetDetId();
                    this->idClusterHead = (int)((id -numCS)/2);
                    EV << "Handling broadcast in cluster"<<id<<"\n";
                    bubble("Request NetDet Arrived!");
                    numReceived++;
                    delete msg;
                    //todo set random position

                    //EV << "Sub-Node "<< id <<" is in position: [" << position[0] <<", "<< position[1] <<", "<< position[2] <<"] "<<"\n";
                    int kindAcksn = 5; //ack sub-nodes
                    Message *acksn = generateMessage(kindAcksn);
                    float delay = (float)(intuniform(0, 1000))/(float)1000;
                    EV << "Sub-Node "<<id<<" have delay: "<<delay<<"\n";
                    scheduleAt(delay, acksn);
                }
            }

        }else if(msg->getDestination() == 3000000){ //dest == 3000000 --> return ack to cluster head

            if(msg->getKindMsg() == 5)
            {
                if(!isClusterHead)
                {
                numSent++;
                send(msg, "gate$o", 1);
                }else if(isClusterHead)
                {
                    numReceived++;
                    numACKsn++;
                    delete msg;
                    bubble("ACK sn Arrived!");

                    if(numACKsn == numSN){
                        int kindAck = 2; //ack con position
                        Message *ack = generateMessage(kindAck);
                        bubble("All ACK sn Arrived!");
                        float delay = (float)(intuniform(100, 1000))/(float)100;
                        EV << "Slave"<<id<<" have delay: "<<delay<<"\n";
                        scheduleAt(delay, ack);
                    }
                }
            }
        }else if(msg->getDestination() == id){
            //todo implement recezione messaggio diretto

        }else if(msg->getDestination() == 0){

            if(isClusterHead){
                numSent++;
                send(msg, "gate$o", 0); //gate out verso il master
            }
        }else {
            // We need to forward the message.
            forwardMessage(msg);
        }
}

Message *Slave::generateMessage(int kindMsg)
{
    int src = id;
    int dest;
    char msgname[24];

    if(kindMsg == 2) //kind==2 --> ACK POS
    {
        dest = 0;
        sprintf(msgname, "ack-slave-%d-to-master-%d", src, dest);

    }else if(kindMsg == 3) //kind==3 --> NET DET SUB-NODES
    {
        dest = 2000000; //broadcast to sub-nodes
        sprintf(msgname, "NetDetsn-S%d-to-sn", id);
    }else if(kindMsg == 5) //kind==5 --> ack sub-nodes
    {
        dest = 3000000; //return to cluster head
        sprintf(msgname, "acksn-%d-to-ch", src);
    }

    Message *msg = new Message(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    msg->setKindMsg(kindMsg);
    if(isClusterHead)
        msg->setPos(position);
    return msg;
}

void Slave::broadcastInCluster(Message *msg)
{
    int n = numSN;//gateSize("gate")-3; //i 3 gate sottratti sono quelli diretti al master e ai due cluster head vicini
    int k = 1;

    for(int i=0; i<n; i++)
    {
        Message *copy = msg->dup();
        if(copy->getKindMsg() == 3) //NET DET SUB-NODES kind
        {
            int idsn = (2*id) + numCS - k;
            copy->setNetDetId(idsn);
            k--;
        }
        EV << "Broadcasting message " << copy <<" in Cluster"<< id << " on gate[" << i+3 << "]\n";
        numSent++;
        send(copy, "gate$o", i+3);
    }
    delete msg;
}


void Slave::forwardMessage(Message *msg)
{
        // Increment hop count.
        msg->setHopCount(msg->getHopCount()+1);

        // Same routing as before: random gate.
        int n = gateSize("gate");
        int k = intuniform(0, n-1);

        EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
        send(msg, "gate$o", k);
}

void Slave::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

}; // namespace
