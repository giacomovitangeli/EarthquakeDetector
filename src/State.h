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

#ifndef STATE_H_
#define STATE_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

namespace earthquakedetector {

class State : public cSimpleModule{
private:
    int batteryState;
    float position[3]{0};  //[posX, posY, posZ]

public:
    State();
    virtual ~State();
    void setBatteryState(int b);
    float getBatteryState();
    void decBatteryState(int b);
    void incBatteryState(int b);
    void setPosition(float pos[]);
    float* getPosition();
    void printPosition();

};

} /* namespace earthquakedetector */

#endif /* STATE_H_ */
