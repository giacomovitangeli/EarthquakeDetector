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
        channel C extends ned.DelayChannel {
            delay = 100ms;
        }
       
        
    
    submodules:
        M: Master{@display("p=500,500");}
  
  		S1: Slave{@display("p=624.275,200");}
  		S2: Slave{@display("p=800,374.275");}
  		S3: Slave{@display("p=800,624.275");}
  		S4: Slave{@display("p=624.275,800");}
  		S5: Slave{@display("p=374.275,800");}
  		S6: Slave{@display("p=200,624.275");}
  		S7: Slave{@display("p=200,374.275");}
  		S8: Slave{@display("p=374.275,200");}
  		
        
        //slave[6]: Slave;
    	//slave[21]: Slave;	//slave[0] is the master
    	//ERROR when add master
    	//master: Master;
    	
    	//slave[0]:<default("WirelessHost")> like INetworkNode{@display("p=500,500");} NOT WORK
    	
        
    connections:      
		M.gate++ <--> C <--> S1.gate++;
		M.gate++ <--> C <--> S2.gate++;
		M.gate++ <--> C <--> S3.gate++;
		M.gate++ <--> C <--> S4.gate++;
		M.gate++ <--> C <--> S5.gate++;
		M.gate++ <--> C <--> S6.gate++;
		M.gate++ <--> C <--> S7.gate++;
		M.gate++ <--> C <--> S8.gate++;
		
		S1.gate++ <--> C <--> S2.gate++;
		S2.gate++ <--> C <--> S3.gate++;
		S3.gate++ <--> C <--> S4.gate++;
		S4.gate++ <--> C <--> S5.gate++;
		S5.gate++ <--> C <--> S6.gate++;
		S6.gate++ <--> C <--> S7.gate++;
		S7.gate++ <--> C <--> S8.gate++;
		S8.gate++ <--> C <--> S1.gate++;
				
        
        
//    	slave[0].gate++ <--> C <--> slave[1].gate++;
//        slave[0].gate++ <--> C <--> slave[2].gate++;
//        slave[0].gate++ <--> C <--> slave[3].gate++;
//        slave[0].gate++ <--> C <--> slave[4].gate++;
//        slave[0].gate++ <--> C <--> slave[5].gate++;
//        
//        slave[1].gate++ <--> C <--> slave[6].gate++;
//        slave[1].gate++ <--> C <--> slave[7].gate++;
//        slave[1].gate++ <--> C <--> slave[8].gate++;
//        
//        slave[2].gate++ <--> C <--> slave[9].gate++;
//        slave[2].gate++ <--> C <--> slave[10].gate++;
//        slave[2].gate++ <--> C <--> slave[11].gate++;
// 
// 		slave[3].gate++ <--> C <--> slave[12].gate++;
//        slave[3].gate++ <--> C <--> slave[13].gate++;
//        slave[3].gate++ <--> C <--> slave[14].gate++;
//        
// 		slave[4].gate++ <--> C <--> slave[15].gate++;
//        slave[4].gate++ <--> C <--> slave[16].gate++;
//        slave[4].gate++ <--> C <--> slave[17].gate++;        
//    
//    
//    	slave[5].gate++ <--> C <--> slave[18].gate++;
//        slave[5].gate++ <--> C <--> slave[19].gate++;
//        slave[5].gate++ <--> C <--> slave[20].gate++;
//        
//        slave[0].gate++ <--> C <--> slave[6].gate++;
//        slave[0].gate++ <--> C <--> slave[7].gate++;
//        slave[0].gate++ <--> C <--> slave[8].gate++;
//        slave[0].gate++ <--> C <--> slave[9].gate++;
//        slave[0].gate++ <--> C <--> slave[10].gate++;
//        slave[0].gate++ <--> C <--> slave[11].gate++;
//        slave[0].gate++ <--> C <--> slave[12].gate++;
//        slave[0].gate++ <--> C <--> slave[13].gate++;
//        slave[0].gate++ <--> C <--> slave[14].gate++;
//        slave[0].gate++ <--> C <--> slave[15].gate++;
//        slave[0].gate++ <--> C <--> slave[16].gate++;
//        slave[0].gate++ <--> C <--> slave[17].gate++;
//        slave[0].gate++ <--> C <--> slave[18].gate++;
//        slave[0].gate++ <--> C <--> slave[19].gate++;
//        slave[0].gate++ <--> C <--> slave[20].gate++;
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
	    
   