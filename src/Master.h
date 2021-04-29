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

#ifndef MASTER_H_
#define MASTER_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "Message.h"
using namespace omnetpp;


namespace earthquakedetector {

class Master : public cSimpleModule{
    public:
        Master();
        virtual ~Master();

    private:
        long numSent;
        long numReceived;
        int id;
        bool usability;
        float network[8][3];

    protected:
        virtual Message *generateMessage(int kindMsg);
        virtual void broadcastMessage(Message *msg);
        virtual void forwardMessage(Message *msg);
        virtual void initialize() override;
        virtual void handleMessage(cMessage *cmsg) override;
        virtual void refreshDisplay() const override;
        virtual void initNetwork();
        virtual void printNetwork();
};

} /* namespace earthquakedetector */

#endif /* MASTER_H_ */
