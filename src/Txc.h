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

#ifndef __EARTHQUAKEDETECTOR_TCX_H
#define __EARTHQUAKEDETECTOR_TCX_H

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "tictoc_m.h"

using namespace omnetpp;

namespace earthquakedetector {

/**
 * Implements the Txc simple module. See the NED file for more information.
 */
class Txc : public cSimpleModule
{
    private:
        long numSent;
        long numReceived;
    protected:
        virtual TicTocMsg *generateMessage();
        virtual void forwardMessage(TicTocMsg *msg);
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
        virtual void refreshDisplay() const override;
};

}; // namespace

#endif
