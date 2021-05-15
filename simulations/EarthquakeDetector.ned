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

        //START TOPOLOGY: 4CH-20SN
//        S1: Slave {
//            @display("p=642.56,345.37598");
//        }
//        S2: Slave {
//            @display("p=642.56,640.552");
//        }
//        S3: Slave {
//            @display("p=345.37598,640.552");
//        }
//        S4: Slave {
//            @display("p=345.37598,345.37598");
//        }
//        S5: Slave {
//            @display("p=642.56,54.216");
//        }
//        S6: Slave {
//            @display("p=748.98395,54.216");
//        }
//        S7: Slave {
//            @display("p=829.30396,146.584");
//        }
//        S8: Slave {
//            @display("p=935.72797,251");
//        }
//
//        S9: Slave {
//            @display("p=935.72797,345.37598");
//        }
//        S10: Slave {
//            @display("p=935.72797,640.552");
//        }
//        S11: Slave {
//            @display("p=935.72797,740.95197");
//        }
//        S12: Slave {
//            @display("p=829.30396,831.31195");
//        }
//        S13: Slave {
//            @display("p=734.928,937.73596");
//        }
//        S14: Slave {
//            @display("p=642.56,937.73596");
//        }
//        S15: Slave {
//            @display("p=345.37598,937.73596");
//        }
//        S16: Slave {
//            @display("p=248.99199,937.73596");
//        }
//        S17: Slave {
//            @display("p=146.584,831.31195");
//        }
//        S18: Slave {
//            @display("p=58.232,740.95197");
//        }
//
//        S19: Slave {
//            @display("p=58.232,640.552");
//        }
//        S20: Slave {
//            @display("p=58.232,345.37598");
//        }
//        S21: Slave {
//            @display("p=58.232,251");
//        }
//        S22: Slave {
//            @display("p=146.584,146.584");
//        }
//        S23: Slave {
//            @display("p=248.99199,54.216");
//        }
//        S24: Slave {
//            @display("p=345.37598,54.216");
//        }
        //END TOPOLOGY: 4CH-20SN




        //START TOPOLOGY: 6CH-18SN
        S1: Slave {
            @display("p=499.99197,313.248");
        }
        S2: Slave {
            @display("p=642.56,393.568");
        }
        S3: Slave {
            @display("p=642.56,592.36");
        }
        S4: Slave {
            @display("p=499.99197,678.704");
        }
        S5: Slave {
            @display("p=345.37598,592.36");
        }
        S6: Slave {
            @display("p=345.37598,393.568");
        }
        S7: Slave {
            @display("p=375.496,100.399994");
        }
        S8: Slave {
            @display("p=499.99197,54.216");
        }

        S9: Slave {
            @display("p=614.448,100.399994");
        }
        S10: Slave {
            @display("p=750.992,170.68");
        }
        S11: Slave {
            @display("p=867.456,232.928");
        }
        S12: Slave {
            @display("p=867.456,393.568");
        }
        S13: Slave {
            @display("p=867.456,592.36");
        }
        S14: Slave {
            @display("p=867.456,740.95197");
        }
        S15: Slave {
            @display("p=750.992,821.272");
        }
        S16: Slave {
            @display("p=614.448,901.592");
        }
        S17: Slave {
            @display("p=499.99197,963.83997");
        }
        S18: Slave {
            @display("p=375.496,901.592");
        }

        S19: Slave {
            @display("p=228.91199,821.272");
        }
        S20: Slave {
            @display("p=120.479996,726.896");
        }
        S21: Slave {
            @display("p=120.479996,592.36");
        }
        S22: Slave {
            @display("p=120.479996,375.496");
        }
        S23: Slave {
            @display("p=106.423996,232.928");
        }
        S24: Slave {
            @display("p=244.976,170.68");
        }
        //END TOPOLOGY: 6CH-18SN




        //START TOPOLOGY: 8CH-16SN
//        S1: Slave {
//            @display("p=624.275,200");
//        }
//        S2: Slave {
//            @display("p=800,374.275");
//        }
//        S3: Slave {
//            @display("p=800,624.275");
//        }
//        S4: Slave {
//            @display("p=624.275,800");
//        }
//        S5: Slave {
//            @display("p=374.275,800");
//        }
//        S6: Slave {
//            @display("p=200,624.275");
//        }
//        S7: Slave {
//            @display("p=200,374.275");
//        }
//        S8: Slave {
//            @display("p=374.275,200");
//        }
//
//        S9: Slave {
//            @display("p=560.232,58.232");
//        }
//        S10: Slave {
//            @display("p=783.12,124.495995");
//        }
//        S11: Slave {
//            @display("p=861.43195,255.01599");
//        }
//        S12: Slave {
//            @display("p=927.696,421.68");
//        }
//        S13: Slave {
//            @display("p=927.696,562.24");
//        }
//        S14: Slave {
//            @display("p=861.43195,769.06396");
//        }
//        S15: Slave {
//            @display("p=765.048,847.376");
//        }
//        S16: Slave {
//            @display("p=560.232,925.688");
//        }
//        S17: Slave {
//            @display("p=435.736,925.688");
//        }
//        S18: Slave {
//            @display("p=230.92,877.496");
//        }
//
//        S19: Slave {
//            @display("p=100.399994,769.06396");
//        }
//        S20: Slave {
//            @display("p=58.232,578.30396");
//        }
//        S21: Slave {
//            @display("p=58.232,407.624");
//        }
//        S22: Slave {
//            @display("p=136.54399,234.93599");
//        }
//        S23: Slave {
//            @display("p=230.92,124.495995");
//        }
//        S24: Slave {
//            @display("p=421.68,58.232");
//        }
        //END TOPOLOGY: 8CH-16SN



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

        //START TOPOLOGY: 4CH 20SN
////        //Near Cluster Head:
//        S1.gate++ <--> C <--> S2.gate++;
//        S2.gate++ <--> C <--> S3.gate++;
//        S3.gate++ <--> C <--> S4.gate++;
//        S4.gate++ <--> C <--> S1.gate++;
//
////        //Cluster 1:
//        S1.gate++ <--> C <--> S5.gate++;
//        S1.gate++ <--> C <--> S6.gate++;
//        S1.gate++ <--> C <--> S7.gate++;
//        S1.gate++ <--> C <--> S8.gate++;
//        S1.gate++ <--> C <--> S9.gate++;
//        S5.gate++ <--> C <--> S6.gate++;
//        S6.gate++ <--> C <--> S7.gate++;
//        S7.gate++ <--> C <--> S8.gate++;
//        S8.gate++ <--> C <--> S9.gate++;
//        S9.gate++ <--> C <--> S5.gate++;    
//
////		//Cluster 2:
//		S2.gate++ <--> C <--> S10.gate++;
//        S2.gate++ <--> C <--> S11.gate++;
//        S2.gate++ <--> C <--> S12.gate++;
//        S2.gate++ <--> C <--> S13.gate++;
//        S2.gate++ <--> C <--> S14.gate++;
//        S10.gate++ <--> C <--> S11.gate++;
//        S11.gate++ <--> C <--> S12.gate++;
//        S12.gate++ <--> C <--> S13.gate++;
//        S13.gate++ <--> C <--> S14.gate++;
//        S14.gate++ <--> C <--> S10.gate++;   
//
////      //Cluster 3:
//		S3.gate++ <--> C <--> S15.gate++;
//        S3.gate++ <--> C <--> S16.gate++;
//        S3.gate++ <--> C <--> S17.gate++;
//        S3.gate++ <--> C <--> S18.gate++;
//        S3.gate++ <--> C <--> S19.gate++;
//        S15.gate++ <--> C <--> S16.gate++;
//        S16.gate++ <--> C <--> S17.gate++;
//        S17.gate++ <--> C <--> S18.gate++;
//        S18.gate++ <--> C <--> S19.gate++;
//        S19.gate++ <--> C <--> S15.gate++;   
//
////        //Cluster 4:
//		S4.gate++ <--> C <--> S20.gate++;
//        S4.gate++ <--> C <--> S21.gate++;
//        S4.gate++ <--> C <--> S22.gate++;
//        S4.gate++ <--> C <--> S23.gate++;
//        S4.gate++ <--> C <--> S24.gate++;
//        S20.gate++ <--> C <--> S21.gate++;
//        S21.gate++ <--> C <--> S22.gate++;
//        S22.gate++ <--> C <--> S23.gate++;
//        S23.gate++ <--> C <--> S24.gate++;
//        S24.gate++ <--> C <--> S20.gate++;   
        //END TOPOLOGY: 4CH-20SN




        //START TOPOLOGY: 6CH 18SN
        S1.gate++ <--> C <--> S2.gate++;
        S2.gate++ <--> C <--> S3.gate++;
        S3.gate++ <--> C <--> S4.gate++;
        S4.gate++ <--> C <--> S5.gate++;
        S5.gate++ <--> C <--> S6.gate++;
        S6.gate++ <--> C <--> S1.gate++;

        //Cluster 1:
        S1.gate++ <--> C <--> S7.gate++;
        S1.gate++ <--> C <--> S8.gate++;
        S1.gate++ <--> C <--> S9.gate++;
        S7.gate++ <--> C <--> S8.gate++;
        S8.gate++ <--> C <--> S9.gate++;
        S9.gate++ <--> C <--> S7.gate++;

        //Cluster 2:
        S2.gate++ <--> C <--> S10.gate++;
        S2.gate++ <--> C <--> S11.gate++;
        S2.gate++ <--> C <--> S12.gate++;
        S10.gate++ <--> C <--> S11.gate++;
        S11.gate++ <--> C <--> S12.gate++;
        S12.gate++ <--> C <--> S10.gate++;

        //Cluster 3:
        S3.gate++ <--> C <--> S13.gate++;
        S3.gate++ <--> C <--> S14.gate++;
        S3.gate++ <--> C <--> S15.gate++;
        S13.gate++ <--> C <--> S14.gate++;
        S14.gate++ <--> C <--> S15.gate++;
        S15.gate++ <--> C <--> S13.gate++;

        //Cluster 4:
        S4.gate++ <--> C <--> S16.gate++;
        S4.gate++ <--> C <--> S17.gate++;
        S4.gate++ <--> C <--> S18.gate++;
        S16.gate++ <--> C <--> S17.gate++;
        S17.gate++ <--> C <--> S18.gate++;
        S18.gate++ <--> C <--> S16.gate++;

        //Cluster 5:
        S5.gate++ <--> C <--> S19.gate++;
        S5.gate++ <--> C <--> S20.gate++;
        S5.gate++ <--> C <--> S21.gate++;
        S19.gate++ <--> C <--> S20.gate++;
        S20.gate++ <--> C <--> S21.gate++;
        S21.gate++ <--> C <--> S19.gate++;

        //Cluster 6:
        S6.gate++ <--> C <--> S22.gate++;
        S6.gate++ <--> C <--> S23.gate++;
        S6.gate++ <--> C <--> S24.gate++;
        S22.gate++ <--> C <--> S23.gate++;
        S23.gate++ <--> C <--> S24.gate++;
        S24.gate++ <--> C <--> S22.gate++;
        //END TOPOLOGY: 6CH 18SN




        //START TOPOLOGY: 8CH-16SN
//        //Near Cluster Head:
//        S1.gate++ <--> C <--> S2.gate++;
//        S2.gate++ <--> C <--> S3.gate++;
//        S3.gate++ <--> C <--> S4.gate++;
//        S4.gate++ <--> C <--> S5.gate++;
//        S5.gate++ <--> C <--> S6.gate++;
//        S6.gate++ <--> C <--> S7.gate++;
//        S7.gate++ <--> C <--> S8.gate++;
//        S8.gate++ <--> C <--> S1.gate++;
//
//        //Cluster 1:
//        S1.gate++ <--> C <--> S9.gate++;
//        S1.gate++ <--> C <--> S10.gate++;
//        S9.gate++ <--> C <--> S10.gate++;
//
//		//Cluster 2:
//        S2.gate++ <--> C <--> S11.gate++;
//        S2.gate++ <--> C <--> S12.gate++;
//        S11.gate++ <--> C <--> S12.gate++;
//
//        //Cluster 3:
//        S3.gate++ <--> C <--> S13.gate++;
//        S3.gate++ <--> C <--> S14.gate++;
//        S13.gate++ <--> C <--> S14.gate++;
//
//        //Cluster 4:
//        S4.gate++ <--> C <--> S15.gate++;
//        S4.gate++ <--> C <--> S16.gate++;
//        S15.gate++ <--> C <--> S16.gate++;
//
//        //Cluster 5:
//        S5.gate++ <--> C <--> S17.gate++;
//        S5.gate++ <--> C <--> S18.gate++;
//        S17.gate++ <--> C <--> S18.gate++;
//
//		//Cluster 6:
//        S6.gate++ <--> C <--> S19.gate++;
//        S6.gate++ <--> C <--> S20.gate++;
//        S19.gate++ <--> C <--> S20.gate++;
//
//		//Cluster 7:
//        S7.gate++ <--> C <--> S21.gate++;
//        S7.gate++ <--> C <--> S22.gate++;
//        S21.gate++ <--> C <--> S22.gate++;
//
//        //Cluster 8:
//        S8.gate++ <--> C <--> S23.gate++;
//        S8.gate++ <--> C <--> S24.gate++;
//        S23.gate++ <--> C <--> S24.gate++;
        //END TOPOLOGY: 8CH-16SN


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


