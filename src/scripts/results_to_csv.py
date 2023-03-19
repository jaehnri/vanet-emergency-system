import subprocess
import pandas as pd

def grep_results():
    return subprocess.run("grep -Hrn ambulanceArrivalTime ../../examples/veins/results/", shell=True, stdout=subprocess.PIPE).stdout.decode("utf-8") 

'''
 The expected result received from the step above is as such:
 '../../examples/veins/results/Simulate-false,false,false,100-#8.sca:5678:scalar RSUExampleScenario.node[134].appl ambulanceArrivalTime -1'
'''
def parse_results(raw_results):
    df = pd.DataFrame(columns = 
                      ( 
                       'name', 
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
        simulation_iteration = simulation_parameters.split('-')[1].split('.')[0]


        name = result[29:31]
        print(name)
        vehicle_count = simulation_parameters[31:34]
        print(vehicle_count)

        # false,false,false,100-#8.sca:5678:scalar
        #simulation_parameters = simulation_parameters.split('-')[1]

        # ['changeLane=false', 'false', 'false', '100'] 
        #simulation_parameters = simulation_parameters.split(',')

        #canChangeLane = simulation_parameters[0].split('=')[1]
        #canOpenTraffic = simulation_parameters[1]
        #canFindNearestHospital = simulation_parameters[2]
        #numberOfVehicles = simulation_parameters[3]

        df.loc[i] = [name, vehicle_count, ambulanceArrivalTime]
        i += 1
    
    df.to_csv('simulations_new.csv')

raw_results = grep_results()
parse_results(raw_results)