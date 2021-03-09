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
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.INetworkNode;
import inet.physicallayer.contract.packetlevel.IRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;
//
// Two instances (tic and toc) of Txc connected.
//
network EarthquakeDetector
{
    parameters:
        @display("bgb=650,500;bgg=100,1,grey95");
        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);

        @figure[rcvdPkText](type=indicatorText; pos=380,20; anchor=w; font=,18; textFormat="S1 packets received: %g"; initialValue=0);
        @statistic[packetReceived](source=hostS1.app[0].packetReceived; record=figure(count); targetFigure=rcvdPkText);
        
        
        //int numSlaves;  // number of slaves
        //@display("bgi=background/terrain,s;bgb=600,600");
    //submodules:
        //master: Txc;
        //slave[numSlaves]: Txc {}
     //types:
        //channel Channel extends ned.DelayChannel {
            //delay = 100ms;
        //}

     submodules:
         visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
            @display("p=580,125");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=580,200");
        }
        radioMedium: <default("UnitDiskRadioMedium")> like IRadioMedium {
            @display("p=580,275");
        }
        hostM: <default("WirelessHost")> like INetworkNode {
            @display("p=250,250");
        }
        hostS1: <default("WirelessHost")> like INetworkNode {
            @display("p=375,150");
        }
        hostS2: <default("WirelessHost")> like INetworkNode {
            @display("p=375,350");
        }
        hostS3: <default("WirelessHost")> like INetworkNode {
            @display("p=125,350");
        }
        hostS4: <default("WirelessHost")> like INetworkNode {
            @display("p=125,150");
        }
        hostS5: <default("WirelessHost")> like INetworkNode {
            @display("p=250,50");
        }
        
        //obstacles
        physicalEnvironment: PhysicalEnvironment {
            @display("p=580,425");
        }
	    //tic[6]: Txc;
        
     //connections:
        //tic[0].gate++ <--> Channel <--> tic[1].gate++;
        //tic[1].gate++ <--> Channel <--> tic[2].gate++;
        //tic[1].gate++ <--> Channel <--> tic[4].gate++;
        //tic[3].gate++ <--> Channel <--> tic[4].gate++;
        //tic[4].gate++ <--> Channel <--> tic[5].gate++;
    
}