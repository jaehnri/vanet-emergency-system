import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.Scenario;
import org.car2x.veins.modules.application.traci.TraCIDemoRSU11p; //added
network RSUExampleScenario extends Scenario
{
    parameters:
        @display("bgb=1009,457");
    submodules:
        rsu[1]: RSU {
            @display("i=device/antennatower;p=422.9275,106.365");
        }
}
