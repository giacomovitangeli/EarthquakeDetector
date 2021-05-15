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
        latencySignal = registerSignal("latency");

    // Initialize variables
        id = 0;
        initSlavePos();
        //initNetwork();
        numSent = 0;
        numReceived = 0;
        numLost = 0;
        WATCH(numSent);
        WATCH(numReceived);


        numCH = 8;
        rowNet = 25;
        colNet = 25;
        network = createNetwork(network, rowNet, colNet);
        printNetwork();

        int kindPower = 0; //power message
        int kindNetDet = 1; //request netdet message

        //POWER to the slaves
        Message *power = generateMessage(kindPower);
        scheduleAt(0.0, power);

        //NET DETECTION
        Message *requestNetDet = generateMessage(kindNetDet);
        scheduleAt(0.002, requestNetDet);

}

void Master::handleMessage(cMessage *cmsg)
{
    Message *msg = check_and_cast<Message *>(cmsg);

        if(msg->getDestination() == this->id)
        {
            if(msg->getKind() == 2)//ack netdet
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

                //emit(latencySignal, simTime() - tempLinkLayerFrame->getCreationTime());
                emit(latencySignal, simTime());

                int idSrc = msg->getSource();
                int batterySrc = msg->getBatterySrc();//batteria richiesta dallo slave
                delete msg;

                numReceived++;
                bubble("ACK ARRIVED!");
                printSlavePos();
                printNetwork();
                //EV << "Battery state: " << batterySrc << "%"<<"\n";

                int kindPower = 0; //power message
                Message *power = generateMessage(kindPower);
                numSent++;
                power->setBatterySrc(batterySrc);//batteria inviata allo slave, override default value
                int gate = idSrc-1;//-1 because gate array start from 0, slaveID enum start from 1
                sendDelayed(power, 0.0,"gate$o", gate);

                if(numCH == numReceived)
                {
                    bubble("ALL ACK ARRIVED!");
                    //END SIMULATION

                    //reboot
                    //int kindNetDet = 1;
                    //Message *requestNetDet = generateMessage(kindNetDet);
                    //broadcastMessage(requestNetDet);
                }

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


    // Create message object and set source and destination field.
    Message *msg = new Message(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    msg->setKind(kindMsg);
    int b = 25;//default value
    msg->setBatterySrc(b);
    msg->setIsLost(msg->packetLoss());

    return msg;
}



void Master::broadcastMessage(Message *msg)
{
    int n = numCH; //number of cluster head
    int k = 1;
    if(msg->getKind() == 0)// pwr msg
        n = gateSize("gate");

    for (int i=0; i<n; i++)
    {
        Message *copy = msg->dup();
        if(copy->getKind() == 1) //net detection kind
        {
            copy->setNetDetId(k);

        }
        EV << "Broadcasting message " << copy << " on gate[" << i << "]\n";
        network[id][k] = 1;
        k++;
        numSent++;

        float retransmitDelay = 0;

        if(copy->getIsLost() && copy->getKind() == 1)
            retransmitDelay = retransmitMsg(msg, retransmitDelay);

        if(copy->getKind() == 1)
            emit(latencySignal, simTime());

        sendDelayed(copy, retransmitDelay, "gate$o", i);
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

float Master::retransmitMsg(Message *msg, float delay)
{
    float retransmitDelay = delay;
    numLost++;
    numSent++;
    //state->decBatteryState(sendEnergy);
    //int b = state->getBatteryState();
    //emit(energySignal, b);
    EV<<"Packet Loss \n";
    bubble("Packet Loss");

    msg->setIsLost(msg->packetLoss());
    retransmitDelay += (float)(intuniform(10, 100))/(float)100000;

    if(msg->getIsLost())
        retransmitDelay = retransmitMsg(msg, retransmitDelay);

    return retransmitDelay;
}

}; // namespace
