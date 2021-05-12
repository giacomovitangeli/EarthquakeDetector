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

#include "State.h"

namespace earthquakedetector {

State::State() {
    batteryState = intuniform(50, 75);
    for(int i=0; i<3; i++)
        position[i] = (float)intuniform(1, 1000)/10;
}

State::~State() {

}

void State::setBatteryState(int b){
    batteryState = b;
    if(batteryState > 100)
        batteryState = 100;
}

float State::getBatteryState(){
    return batteryState;
}

void State::decBatteryState(int b){
    batteryState -= b;
    if(batteryState < 0)
        batteryState = 0;
}

void State::incBatteryState(int b){
    batteryState += b;
    if(batteryState > 100)
        batteryState = 100;
}

void State::setPosition(float pos[]){
    for(int i=0; i<3; i++)
        position[i] = pos[i];
}

float* State::getPosition(){
    return position;
}

void State::printPosition(){
    EV<<"Position: \n";
    for(int i=0; i<3; i++)
        EV <<" ["<<position[i]<<"] ";



}

} /* namespace earthquakedetector */
