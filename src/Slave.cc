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
        batteryState = intuniform(0, 50);

        /*
        //FIXME trovare l'id degli slaves per assegnare le posizioni in fase di init
        switch(id){
        case '3':
            position[0] = 624.275;
            position[1] = 200;

        case '4':
            position[0] = 800;
            position[1] = 374.275;

        case '5':
            position[0] = 800;
            position[1] = 624.275;

        case '6':
            position[0] = 624.275;
            position[1] = 800;

        case '7':
            position[0] = 374.275;
            position[1] = 800;

        case '8':
            position[0] = 200;
            position[1] = 624.275;

        case '9':
            position[0] = 200;
            position[1] = 374.275;

        case '10':
            position[0] = 374.275;
            position[1] = 200;

        }*/
        /*
         * S1: Slave{@display("p=624.275,200");}
        S2: Slave{@display("p=800,374.275");}
        S3: Slave{@display("p=800,624.275");}
        S4: Slave{@display("p=624.275,800");}
        S5: Slave{@display("p=374.275,800");}
        S6: Slave{@display("p=200,624.275");}
        S7: Slave{@display("p=200,374.275");}
        S8: Slave{@display("p=374.275,200");}
         * */

/*
        // Module 0 sends the first message
        if (getIndex() == 0) {
            // Boot the process scheduling the initial message as a self-message.
            Message *msg = generateMessage();
            numSent++;
            scheduleAt(0.0, msg);
        }*/
}

void Slave::handleMessage(cMessage *cmsg)
{
    Message *msg = check_and_cast<Message *>(cmsg);

        if(msg->getDestination() == 1000000) //dest == 1000000 -> broadcast
        {
            if(msg->getKindMsg() == 0)
            {
                //kind == 0 -> power
                batteryState += 25;
                if(batteryState > 100)
                    batteryState = 100;

                delete msg;
                bubble("Power Arrived! +25%");
                EV << "Battery state: " << batteryState << "%"<<"\n";

            }
            else if(msg->getKindMsg() == 1)
            {
                //kind == 1 -> net detection
                id = msg->getNetDetId();
                delete msg;
                if(id == 1){
                    position[0] = 624.275;
                    position[1] = 200;
                    position[2] = 3;
                }else if(id == 2){
                    position[0] = 800;
                    position[1] = 374.275;
                    position[2] = 3;

                }else if(id == 3){
                    position[0] = 800;
                    position[1] = 624.275;
                    position[2] = 3;

                }else if(id == 4){
                    position[0] = 624.275;
                    position[1] = 800;
                    position[2] = 3;

                }else if(id == 5){
                    position[0] = 374.275;
                    position[1] = 800;
                    position[2] = 3;

                }else if(id == 6){
                    position[0] = 200;
                    position[1] = 624.275;
                    position[2] = 3;

                }else if(id == 7){
                    position[0] = 200;
                    position[1] = 374.275;
                    position[2] = 3;

                }else if(id == 8){
                    position[0] = 374.275;
                    position[1] = 200;
                    position[2] = 3;

                }else{
                    position[0] = 0;
                    position[1] = 0;
                    position[2] = 0;
                }

                bubble("Request NetDet Arrived!");
                EV << "Slave "<< id <<" is in position: [" << position[0] <<", "<< position[1] <<", "<< position[2] <<"] "<<"\n";

                //todo invia ack al master con posizione
                int kindAck = 2; //ack con position
                Message *ack = generateMessage(kindAck);
                scheduleAt(0.0, msg);
                //todo 2 inviare ack in tempi random
                //per evitare deadlock
            }
        }
        else {
            // We need to forward the message.
            forwardMessage(msg);
        }
}

Message *Slave::generateMessage(int kindMsg)
{
    int src = id;
    int dest;
    char msgname[24];

    //kind==2 --> ACK POS
    if(kindMsg == 2)
    {
        dest = 0;
        sprintf(msgname, "ack-slave-%d-to-master-%d", src, dest);

    }
    Message *msg = new Message(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    msg->setKindMsg(kindMsg);
    msg->setPos(position);
    return msg;
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
