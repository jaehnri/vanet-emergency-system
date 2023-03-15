import subprocess
import pandas as pd

def grep_results():
    return subprocess.run(["grep", "-Hrn", "ambulanceArrivalTime", "../../examples/veins/results/"], stdout=subprocess.PIPE).stdout.decode("utf-8") 
    
'''
 The expected result received from the step above is as such:
 '../../examples/veins/results/Simulate-false,false,false,100-#8.sca:5678:scalar RSUExampleScenario.node[134].appl ambulanceArrivalTime -1'
'''
def parse_results(raw_results):
    df = pd.DataFrame(columns = 
                      ('iteration', 
                       'can_change_lane', 
                       'can_open_traffic', 
                       'can_find_nearest_hospital', 
                       'number_of_vehicles', 
                       'ambulance_arrival_time'))

    # Ignores last element as it is a lone line-break 
    raw_results = raw_results.split('\n')[:-1]

    i = 0
    for result in raw_results:
        split_line = result.split(' ')

        # ../../examples/veins/results/Simulate-false,false,false,100-#8.sca:5678:scalar
        simulation_parameters = split_line[0]
        ambulanceArrivalTime = split_line[-1]

        # 2.sca:211:scalar
        simulation_iteration = simulation_parameters.split('-')[2]
        simulation_iteration = simulation_iteration.split('.')[0]

        # false,false,false,100-#8.sca:5678:scalar
        simulation_parameters = simulation_parameters.split('-')[1]

        # ['true', 'false', 'false', '100'] 
        simulation_parameters = simulation_parameters.split(',')

        canChangeLane = simulation_parameters[0]
        canOpenTraffic = simulation_parameters[1]
        canFindNearestHospital = simulation_parameters[2]
        numberOfVehicles = simulation_parameters[3]

        df.loc[i] = [simulation_iteration, canChangeLane, canOpenTraffic, canFindNearestHospital, numberOfVehicles, ambulanceArrivalTime]
        i += 1
    
    df.to_csv('simulations.csv')

raw_results = grep_results()
parse_results(raw_results)