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
        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);

        int kind = 1; //power message
        Message *power = generateMessage(kind);
        broadcastMessage(power);


/*
        // Module 0 sends the first message
        if (getIndex() == 0) {
            // Boot the process scheduling the initial message as a self-message.
            Message *msg = generateMessage();
            numSent++;
            scheduleAt(0.0, msg);
        }*/
}

void Master::handleMessage(cMessage *msg)
{
   /* Message *ttmsg = check_and_cast<Message *>(msg);

        if (ttmsg->getDestination() == getIndex()) {
            // Message arrived
            int hopcount = ttmsg->getHopCount();
            EV << "Message " << ttmsg << " arrived after " << hopcount << " hops.\n";
            numReceived++;
            delete ttmsg;
            bubble("ARRIVED, starting new one!");

            // Generate another one.
            EV << "Generating another message: ";
            //Message *newmsg = generateMessage();
            EV << newmsg << endl;
            forwardMessage(newmsg);
            numSent++;
        }
        else {
            // We need to forward the message.
            forwardMessage(ttmsg);
        }*/
}

Message *Master::generateMessage(int kind)
{
    int src = id;
    int dest;
    char msgname[20];

    //kind==1 --> POWER
    //kind==2 --> ...
    if(kind == 1){
        dest = 1000000;
        //1000000 --> Broadcast Message
        sprintf(msgname, "power-master-to-all");
    }

// Produce source and destination addresses.
  /*
    int src = getIndex();  // our module index
    int n = getVectorSize();  // module vector size
    int dest = intuniform(0, n-2);
    if (dest >= src)
        dest++;
*/
    //char msgname[20];
    //sprintf(msgname, "msg-%d-to-%d", src, dest);

    // Create message object and set source and destination field.
    Message *msg = new Message(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}



void Master::broadcastMessage(Message *msg)
{
    int n = gateSize("gate");

    for (int i=0; i<n; i++)
    {
        Message *copy = msg->dup();
        EV << "Broadcasting message " << copy << " on gate[" << i << "]\n";
        send(copy, "gate$o", i);    //FIXME
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

}; // namespace
