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

#ifndef ICALLBACK_H_
#define ICALLBACK_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

namespace earthquakedetector {

class ICallback : UdpSocket{
public:
    ICallback();
    virtual ~ICallback();
    void socketDataArrived(UdpSocket *socket, Packet *packet);
    void socketErrorArrived(UdpSocket *socket, Indication *indication);
};

} /* namespace earthquakedetector */

#endif /* ICALLBACK_H_ */
