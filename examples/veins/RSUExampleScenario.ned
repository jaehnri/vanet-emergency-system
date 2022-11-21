import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.ERURSU; //added
import org.car2x.veins.nodes.Scenario;
import org.car2x.veins.modules.application.traci.TraCIDemoRSU11p; //added
network RSUExampleScenario extends Scenario
{
    parameters:
        int numRsu = default(0);
        @display("bgb=1600,1500");
    submodules:
        //start
        ERU: ERURSU {
            @display("p=275,261;i=device/server2;is=l");
        }
        Hospital[2]: RSU{
            @display("p=575,261;i=misc/city_vl;is=l");
        }
        //end
        rsu[1]: RSU {
            @display("i=device/antennatower;p=422.9275,106.365");
        }
    connections allowunconnected:
        ERU.rsuConnection <--> rsu[0].eruConnection;
        
        ERU.firstHospitalConnection <--> Hospital[0].eruConnection;
        ERU.secondHospitalConnection <--> Hospital[1].eruConnection;
}
