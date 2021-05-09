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
    //delete the network adj matrix
    for (int i = 0; i < rowNet; i++)
  {
    delete [] network[i];
  }
  delete [] network;
  network = 0;
}


void Slave::initialize()
{
    // Initialize variables

        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
        batteryState = intuniform(0, 75);
        numCH = 8;
        numCHnear = 1;
        numSN = 2;
        numACKsn = 0;
        numACKch = 0;

        EV << "gateCHconfig "<< id <<" have gateCHConfig: [" << gateCHConfig[0] <<", "<< gateCHConfig[1] <<", "<< gateCHConfig[2] <<", "<<gateCHConfig[3]<<"] "<<"\n";
        EV << "gateSNconfig "<< id <<" have gateSNConfig: [" << gateSNConfig[0] <<", "<< gateSNConfig[1] <<"] "<<"\n";

        //initNetwork();
        //todo init
        rowNet=0;
        colNet=0;


        //todo inizializzare variabile network come puntatore di puntatore e convertire
        //le matrici stack in dinamiche
        //network = createNetwork(h, w);//stampa e riparti da qui

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
                this->numCHnear = 2;
                this->rowNet = numCHnear+numSN+2; //+2 sono il master e il CH a cui appartiene la matrice
                this->colNet = numCHnear+numSN+2;
                network = createNetwork(network, rowNet, colNet);
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


                //inoltro la req netdet ai sottonodi
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

                }else if(!isClusterHead){//is sub-node
                    this->id = msg->getNetDetId();
                    this->idClusterHead = (int)((id-numCH)/2);
                    this->rowNet = numSN+2; //+2 sono il master e il CH a cui appartiene il sub-node
                    this->colNet = numSN+2;
                    network = createNetwork(network, rowNet, colNet);
                    EV << "Handling broadcast in cluster"<<id<<"\n";
                    bubble("Request NetDet Arrived!");
                    numReceived++;
                    fillNetwork();
                    printNetwork();
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
                    //this->network = sumMatrix(network, msg->getNetwork());
                    //this->network[msg->getSource()][id] = 1;
                    delete msg;
                    bubble("ACK sn Arrived!");

                    if(numACKsn == numSN){

                        bubble("ALL ACK sn Arrived!");

                        //todo inviare getID ai CH vicini in broadcast
                        int kindReqCHnear = 6; //req CH near
                        Message *reqCHnear = generateMessage(kindReqCHnear);
                        float delay = (float)(intuniform(50, 1000))/(float)100;
                        scheduleAt(delay, reqCHnear);//fixme check delay time
                    }
                }
            }
        }else if(msg->getDestination() == 4000000){ //dest == 4000000 --> broadcast to CH near

            if(msg->getKindMsg() == 6)
            {
                if(id == msg->getSource())// is CH
                {
                    broadcastToNearCH(msg);

                }else{//is CH near
                    EV << "Handling broadcast To cluster near"<<id<<"\n";
                    bubble("RequestID to CH near Arrived!");
                    numReceived++;

                    int gate = 0;

                    if((id!=1) && (msg->getSource()!=1))
                    {
                        if(id<msg->getSource())
                            gate = 2;
                        if(id>msg->getSource())
                            gate = 1;
                    }else if((id==1) || (msg->getSource()==1))
                    {
                        if((id==2) || (msg->getSource()==2))
                            gate = 1;
                        if((id==numCH) || (msg->getSource()==numCH))
                            gate = 2;
                    }


                    delete msg;

                    int kindAckCHnear = 7; //ack CHnear
                    Message *ackCHnear = generateMessage(kindAckCHnear);
                    numSent++;
                    send(ackCHnear, "gate$o", gate);

                    //todo schedulare in time random
                    //float delay = (float)(intuniform(0, 1000))/(float)1000;
                    //scheduleAt(delay, ackCHnear);
                }
            }

        }else if(msg->getDestination() == 5000000){ //dest == 5000000 --> return from CH near
            if(msg->getKindMsg() == 7)
            {
                EV << "Handling broadcast To cluster near"<<id<<"\n";
                bubble("ACK from CH near Arrived!");
                numReceived++;
                gateCHConfig[numACKch] = msg->getSource();
                numACKch++;

                delete msg;

                if(numCHnear == numACKch)
                {
                    bubble("ALL ACK from CH near Arrived!");
                    //riempire matrice di adiacenza di CH

                    fillNetwork();
                    printNetwork();

                    //risposta al master, inviata dopo ACK CH vicini
                    int kindAck = 2; //ack con position e gateConfig
                    Message *ack = generateMessage(kindAck);
                    float delay = (float)(intuniform(100, 1000))/(float)50;
                    EV << "Slave"<<id<<" have delay: "<<delay<<"\n";
                    scheduleAt(delay, ack);

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
        dest = 3000000; //return from sub-nodes to cluster head
        sprintf(msgname, "acksn-%d-to-ch", src);
    }else if(kindMsg == 6) //kind==6 --> req CHnear
    {
        dest = 4000000; //broadcast to CHnear
        sprintf(msgname, "reqCHnear-%d-to-ch", src);
    }else if(kindMsg == 7) //kind==7 --> ack CHnear
    {
        dest = 5000000; //return from CHnear
        sprintf(msgname, "ackCHnear-%d-to-ch", src);
    }

    Message *msg = new Message(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    msg->setKindMsg(kindMsg);
    //msg->setNet(network);
    if(isClusterHead)
        msg->setPos(position);
        msg->setGateCHConfig(gateCHConfig);
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
            int idsn = (2*id) + numCH - k;
            gateCHConfig[i+2] = idsn;
            EV << "gateCHconfig "<< id <<" have gateCHConfig: [" << gateCHConfig[0] <<", "<< gateCHConfig[1] <<", "<< gateCHConfig[2] <<", "<<gateCHConfig[3]<<"] "<<"\n";
            copy->setNetDetId(idsn);
            k--;
        }
        EV << "Broadcasting message " << copy <<" in Cluster"<< id << " on gate[" << i+3 << "]\n";
        numSent++;
        send(copy, "gate$o", i+3);
    }
    delete msg;
}

void Slave::broadcastToNearCH(Message *msg)
{
    int n = numCHnear; //2 CH near

    for(int i=0; i<n; i++)
    {
        Message *copy = msg->dup();
        /*if(copy->getKindMsg() == 6)
        {
            copy->setNetDetId(i);
        }*/
        EV << "Broadcasting message " << copy <<" to near CH from S"<< id << " on gate[" << i+1 << "]\n";
        numSent++;
        send(copy, "gate$o", i+1);
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
/*
void Slave::initNetwork()
{
    for(int i=0; i<25; i++){
        for(int j=0; j<25; j++){
            network[i][j] = 0;
        }
    }
}

void Slave::printNetwork()
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
/*
int ** Slave::sumMatrix(a[][25], b[][25])
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

int** Slave::createNetwork(int **&net, int row, int col)
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

void Slave::fillNetwork()
{
    if(isClusterHead)
    {
        //0->master
        //1->thisCH
        //2->gateCHConfig[0]-> CHnear1
        //3->gateCHConfig[1]-> CHnear2
        //4->gateCHConfig[2]-> sub-node1
        //5->gateCHConfig[3]-> sub-node2

        //master<->CH
        network[0][1] = 1;
        network[1][0] = 1;

        for(int i=2; i<rowNet; i++)
        {
            //thisCH<->CHnear/sub-node
            network[1][i] = 1;
            network[i][1] = 1;
            if(i == (numCHnear+2))
            {
                network[i][i+1] = 1;
                network[i+1][i] = 1;
            }
        }
    }else if(!isClusterHead)
    {
        //0->master
        //1->thisSN
        //2->gateSNConfig[0]-> CH
        //3->gateSNConfig[1]-> sub-node2

        network[0][2] = 1;//when master give power to slave sub-node

        for(int i=2; i<(numSN+2); i++)
        {
            //thisSN<->CH/other sub-node
            network[1][i] = 1;
            network[i][1] = 1;
        }

    }
}


void Slave::printNetwork() const
{
    EV <<"Slave "<< id <<" network: \n";
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
