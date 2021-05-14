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

package earthquakedetector;

//
// Immediately sends out any message it receives. It can optionally generate
// a message at the beginning of the simulation, to bootstrap the process.
//
simple Slave
{
    parameters:
        @signal[energy](type="int");
        @statistic[batteryState](title="energy"; source="energy"; record=vector,stats; interpolationmode=none);
        
        @signal[knowledge](type="int");
        @statistic[knowledge](title="knowledge"; source="knowledge"; record=vector,stats; interpolationmode=none);
        
        @signal[interactivity](type="int");
        @statistic[interactivity](title="interactivity"; source="interactivity"; record=vector,stats; interpolationmode=none);
        
        @display("i=block/routing");
    gates:
        inout gate[];  // declare two way connections
}