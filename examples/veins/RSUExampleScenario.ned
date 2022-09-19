import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.ERURSU; //added
import org.car2x.veins.nodes.HospitalRSU; //added
import org.car2x.veins.nodes.Scenario;
import org.car2x.veins.modules.application.traci.TraCIDemoRSU11p; //added
network RSUExampleScenario extends Scenario
{
    parameters:
        int numRsu = default(0);
        @display("bgb=1009,457");
    submodules:
        //start
        ERU: ERURSU {
            @display("p=275,261;i=device/server2;is=l");
        }
        Hospital: HospitalRSU{
            @display("p=575,261;i=misc/city_vl;is=l");
        }
        //end
        rsu[1]: RSU {
            @display("i=device/antennatower;p=422.9275,106.365");
        }
    connections allowunconnected:
        //start       
        rsu[0].RSUOutgate++ --> ERU.ERURSUIngate++;
        ERU.ERURSUOutgate++ --> Hospital.HospitalRSUIngate++;
}
