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
    //delete the network adj matrix
    for (int i = 0; i < rowNet; i++)
  {
    delete [] network[i];
  }
  delete [] network;
  network = 0;
}


void Master::initialize()
{
    // Initialize variables
        id = 0;
        initSlavePos();
        //initNetwork();
        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
        int kindPower = 0; //power message
        int kindNetDet = 1; //request netdet message

        rowNet = 25;
        colNet = 25;
        network = createNetwork(network, rowNet, colNet);
        printNetwork();

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
                int row = msg->getSource();
                this->network[row][id] = 1;
                //this->network = sumMatrix(network, msg->getNet());

                for(int i=0; i<4; i++)
                {
                    network[row][msg->getGateCHConfig()[i]] = 1;
                    network[msg->getGateCHConfig()[i]][row] = 1;
                    if(i == 2)
                    {
                        network[msg->getGateCHConfig()[i]][msg->getGateCHConfig()[i+1]] = 1;
                        network[msg->getGateCHConfig()[i+1]][msg->getGateCHConfig()[i]] = 1;
                    }
                }

                row--;
                for(int i=0; i<3; i++)
                    this->slavePos[row][i] = msg->getPos()[i];

                delete msg;
                numReceived++;
                bubble("ACK ARRIVED!");
                printSlavePos();
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

        }
        EV << "Broadcasting message " << copy << " on gate[" << i << "]\n";
        network[id][k] = 1;
        k++;
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
/*
void Master::initNetwork()
{
    for(int i=0; i<25; i++){
        for(int j=0; j<25; j++){
            network[i][j] = 0;
        }
    }
}

void Master::printNetwork()
{
    EV <<"network: \n";
    for(int i=0; i<25; i++){
        for(int j=0; j<25; j++){
            EV <<" ["<<network[i][j]<<"] ";
        }
        EV<<"\n";
    }
}
*/
void Master::initSlavePos()
{
    for(int i=0; i<8; i++){
        for(int j=0; j<3; j++){
            slavePos[i][j] = 0;
        }
    }
}

void Master::printSlavePos() const
{
    EV <<"slavePos: \n";
    for(int i=0; i<8; i++){
        for(int j=0; j<3; j++){
            EV <<" ["<<slavePos[i][j]<<"] ";
        }
        EV<<"\n";
    }
}
/*
int ** Master::sumMatrix(a[][25], b[][25])
{
    int sum[25][25];

    for(int i=0; i<25; i++){
        for(int j=0; j<25; j++){
            sum[i][j] = a[i][j] + b[i][j];
        }
    }

    return sum;
}
*/

int** Master::createNetwork(int **&net, int row, int col)
{
  //int** net = 0;
  net = new int*[row];

  for (int i = 0; i < row; i++)
  {
        net[i] = new int[col];

        for (int j = 0; j < col; j++)
        {
              net[i][j] = 0;
        }
  }

  return net;
}

void Master::printNetwork() const
{
    EV <<"Master network: \n";
    for (int i = 0; i < rowNet; i++)
    {
        for (int j = 0; j < colNet; j++)
        {
            EV <<" ["<<network[i][j]<<"] ";
        }
        EV<<"\n";
    }
}


}; // namespace
