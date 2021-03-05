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

package earthquakedetector.simulations;

import earthquakedetector.Txc;

//
// Two instances (tic and toc) of Txc connected.
//
network EarthquakeDetector
{
    parameters:
        //int numSlaves;  // number of slaves
        @display("bgi=background/terrain,s;bgb=600,600");
    //submodules:
        //master: Txc;
        //slave[numSlaves]: Txc {}
     types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }

     submodules:
	    tic[6]: Txc;
     connections:
        tic[0].gate++ <--> Channel <--> tic[1].gate++;
        tic[1].gate++ <--> Channel <--> tic[2].gate++;
        tic[1].gate++ <--> Channel <--> tic[4].gate++;
        tic[3].gate++ <--> Channel <--> tic[4].gate++;
        tic[4].gate++ <--> Channel <--> tic[5].gate++;
        
}
