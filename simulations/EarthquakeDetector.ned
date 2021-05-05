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
import earthquakedetector.Node;
import earthquakedetector.Master;
import earthquakedetector.Slave;
//import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
//import inet.node.inet.INetworkNode;
//import inet.physicallayer.contract.packetlevel.IRadioMedium;
//import inet.visualizer.contract.IIntegratedVisualizer;
//import inet.environment.common.PhysicalEnvironment;





network EarthquakeDetector
{
    parameters:
        @display("bgb=1000,1000;bgg=100,1,grey95");
        //@figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);

    types:
        channel C extends ned.DelayChannel
        {
            delay = 1ms;
        }



    submodules:
        M: Master {
            @display("p=500,500");
        }

        S1: Slave {
            @display("p=624.275,200");
        }
        S2: Slave {
            @display("p=800,374.275");
        }
        S3: Slave {
            @display("p=800,624.275");
        }
        S4: Slave {
            @display("p=624.275,800");
        }
        S5: Slave {
            @display("p=374.275,800");
        }
        S6: Slave {
            @display("p=200,624.275");
        }
        S7: Slave {
            @display("p=200,374.275");
        }
        S8: Slave {
            @display("p=374.275,200");
        }

        S9: Slave {
            @display("p=560.232,58.232");
        }
        S10: Slave {
            @display("p=783.12,124.495995");
        }
        S11: Slave {
            @display("p=861.43195,255.01599");
        }
        S12: Slave {
            @display("p=927.696,421.68");
        }
        S13: Slave {
            @display("p=927.696,562.24");
        }
        S14: Slave {
            @display("p=861.43195,769.06396");
        }
        S15: Slave {
            @display("p=765.048,847.376");
        }
        S16: Slave {
            @display("p=560.232,925.688");
        }
        S17: Slave {
            @display("p=435.736,925.688");
        }
        S18: Slave {
            @display("p=230.92,877.496");
        }

        S19: Slave {
            @display("p=100.399994,769.06396");
        }
        S20: Slave {
            @display("p=58.232,578.30396");
        }
        S21: Slave {
            @display("p=58.232,407.624");
        }
        S22: Slave {
            @display("p=136.54399,234.93599");
        }
        S23: Slave {
            @display("p=230.92,124.495995");
        }
        S24: Slave {
            @display("p=421.68,58.232");
        }



        //slave[6]: Slave;
    	//slave[21]: Slave;	//slave[0] is the master
    	//ERROR when add master
    	//master: Master;

    	//slave[0]:<default("WirelessHost")> like INetworkNode{@display("p=500,500");} NOT WORK


    connections:
        //Master to all:
        M.gate++ <--> C <--> S1.gate++;
        M.gate++ <--> C <--> S2.gate++;
        M.gate++ <--> C <--> S3.gate++;
        M.gate++ <--> C <--> S4.gate++;
        M.gate++ <--> C <--> S5.gate++;
        M.gate++ <--> C <--> S6.gate++;
        M.gate++ <--> C <--> S7.gate++;
        M.gate++ <--> C <--> S8.gate++;

        M.gate++ <--> C <--> S9.gate++;
        M.gate++ <--> C <--> S10.gate++;
        M.gate++ <--> C <--> S11.gate++;
        M.gate++ <--> C <--> S12.gate++;
        M.gate++ <--> C <--> S13.gate++;
        M.gate++ <--> C <--> S14.gate++;
        M.gate++ <--> C <--> S15.gate++;
        M.gate++ <--> C <--> S16.gate++;
        M.gate++ <--> C <--> S17.gate++;
        M.gate++ <--> C <--> S18.gate++;
        M.gate++ <--> C <--> S19.gate++;
        M.gate++ <--> C <--> S20.gate++;
        M.gate++ <--> C <--> S21.gate++;
        M.gate++ <--> C <--> S22.gate++;
        M.gate++ <--> C <--> S23.gate++;
        M.gate++ <--> C <--> S24.gate++;

        //Near Cluster Head:
        S1.gate++ <--> C <--> S2.gate++;
        S2.gate++ <--> C <--> S3.gate++;
        S3.gate++ <--> C <--> S4.gate++;
        S4.gate++ <--> C <--> S5.gate++;
        S5.gate++ <--> C <--> S6.gate++;
        S6.gate++ <--> C <--> S7.gate++;
        S7.gate++ <--> C <--> S8.gate++;
        S8.gate++ <--> C <--> S1.gate++;

        //Cluster 1:
        S1.gate++ <--> C <--> S9.gate++;
        S1.gate++ <--> C <--> S10.gate++;
        S9.gate++ <--> C <--> S10.gate++;

		//Cluster 2:
        S2.gate++ <--> C <--> S11.gate++;
        S2.gate++ <--> C <--> S12.gate++;
        S11.gate++ <--> C <--> S12.gate++;

        //Cluster 3:
        S3.gate++ <--> C <--> S13.gate++;
        S3.gate++ <--> C <--> S14.gate++;
        S13.gate++ <--> C <--> S14.gate++;

        //Cluster 4:
        S4.gate++ <--> C <--> S15.gate++;
        S4.gate++ <--> C <--> S16.gate++;
        S15.gate++ <--> C <--> S16.gate++;

        //Cluster 5:
        S5.gate++ <--> C <--> S17.gate++;
        S5.gate++ <--> C <--> S18.gate++;
        S17.gate++ <--> C <--> S18.gate++;

		//Cluster 6:
        S6.gate++ <--> C <--> S19.gate++;
        S6.gate++ <--> C <--> S20.gate++;
        S19.gate++ <--> C <--> S20.gate++;

		//Cluster 7:
        S7.gate++ <--> C <--> S21.gate++;
        S7.gate++ <--> C <--> S22.gate++;
        S21.gate++ <--> C <--> S22.gate++;

        //Cluster 8:
        S8.gate++ <--> C <--> S23.gate++;
        S8.gate++ <--> C <--> S24.gate++;
        S23.gate++ <--> C <--> S24.gate++;



}
    //parameters:
        //@display("bgb=650,500;bgg=100,1,grey95");
        //@figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);

        //@figure[rcvdPkText](type=indicatorText; pos=380,20; anchor=w; font=,18; textFormat="S1 packets received: %g"; initialValue=0);
        //@statistic[packetReceived](source=hostS1.app[0].packetReceived; record=figure(count); targetFigure=rcvdPkText);


        //int numSlaves;  // number of slaves
        //@display("bgi=background/terrain,s;bgb=600,600");
//    submodules:
//        master: Txc;
//        slave[numSlaves]: Txc {};


//     submodules:
//         visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
//            @display("p=580,125");
//        }
//        configurator: Ipv4NetworkConfigurator {
//            @display("p=580,200");
//        }
//        radioMedium: <default("ApskScalarRadioMedium")> like IRadioMedium {
//            @display("p=580,275");
//        }
//        hostM: <default("WirelessHost")> like INetworkNode {
//            @display("p=250,250");
//        }
//        hostS1: <default("WirelessHost")> like INetworkNode {
//            @display("p=375,150");
//        }
//        hostS2: <default("WirelessHost")> like INetworkNode {
//            @display("p=375,350");
//        }
//        hostS3: <default("WirelessHost")> like INetworkNode {
//            @display("p=125,350");
//        }
//        hostS4: <default("WirelessHost")> like INetworkNode {
//            @display("p=125,150");
//        }
//        hostS5: <default("WirelessHost")> like INetworkNode {
//            @display("p=250,50");
//        }

        //obstacles
//        physicalEnvironment: PhysicalEnvironment {
//            @display("p=580,425");
//        }


