import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.TLRSU; //added
import org.car2x.veins.nodes.Scenario;
import org.car2x.veins.modules.application.traci.RSUAppl; //added
import org.car2x.veins.modules.mobility.traci.TraCIVehicleInserter; //added
network RSUExampleScenario extends Scenario
{
    parameters:
        @display("bgb=1600,1500");
    submodules:
        //start
        eru: RSU {
            rsuCount = 1;
            hospitalCount = 2;
            @display("p=275,261;i=device/server2;is=l");
        }
        Hospital[2]: RSU {
            eruCount = 1;
            @display("p=575,261;i=misc/city_vl;is=l");
        }
        //end
        rsu[3]: RSU {
            @display("i=device/antennatower;p=422.9275,106.365");
        }

        tls[32]: TLRSU {
            @display("i=veins/node/trafficlight;p=325.42624,127.89125");
        }
        
        //randomCars: TraCIVehicleInserter {
        //}
    connections allowunconnected:
        eru.rsuGates[0] <--> rsu[2].eruGates[0];
        
        rsu[0].rsuGates[0] <--> rsu[1].rsuGates[0];
        rsu[1].rsuGates[1] <--> rsu[2].rsuGates[0];

		eru.hospitalGates[0] <--> Hospital[0].eruGates[0];
		eru.hospitalGates[1] <--> Hospital[1].eruGates[0];
}
