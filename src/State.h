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

namespace earthquakedetector {

class State {
private:
    float batteryState;
    float* position;  //[posX, posY, posZ]

public:
    State();
    virtual ~State();
    void setBatteryState(float b);
    float getBatteryState();
    void setPosition(float* pos);
    float* getPosition();

};

} /* namespace earthquakedetector */

#endif /* STATE_H_ */
