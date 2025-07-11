no_processors = 3
commands = ["initial", "P1Rd", "P2Rd", "P3Rd", "P1Rd", "P1Wr", "P1Rd", "P2Wr", "P3Rd"]
# commands = ["initial", "P2Wr", "P1Rd", "P3Wr", "P1Wr"]
# commands = ["initial", "P3Rd", "P2Rd", "P1Wr", "P1Rd", "P2Rd"]
proc_states = []
mag_action = ""
data_source = ""
all_invalid = True
have_written = False
possessor = 0

graph = {'I' : {'Rd': ['S', 'BusRd'], 'Wr' : ['M', 'BusRdX']},
         'S' : {'Rd': ['S', '-'], 'Wr': ['M', 'BusRdX'], 'BusRd': ['S', 'Flush*'], 'BusRdX': ['I', 'Flush*']},
         'E' : {'Rd': ['E', '-'], 'Wr': ['M', '-'], 'BusRd': ['S', 'Flush'], 'BusRdX': ['I', 'Flush']},
         'M' : {'Rd': ['M', '-'], 'Wr': ['M', '-'], 'BusRd': ['S', 'Flush'], 'BusRdX': ['I', 'Flush']}
         }

def check_read(command):
    if command[2:] == "Rd":
        return "Rd", int(command[1])
    return "Wr", int(command[1])

if __name__ == '__main__':
    print(f"Processor_action P1 P2 P3 Mag_action Data_source")
    for command in commands:
        if command == "initial":
            proc_states = ["I" for _ in range(no_processors + 1)]
            mag_action = "-"
            data_source = "-"
            all_invalid = True
            
        else:
            act, proc = check_read(command)

            if act == "Rd":
                if proc_states[possessor] == 'I':
                    possessor = proc
                
                if all_invalid:
                    all_invalid = False
                    proc_states[proc] = 'E'
                    data_source = "Mem"
                    mag_action = "BusRd"
                
                elif not have_written:
                    
                    if proc_states[proc] == 'E' or proc_states[proc] == 'S':
                        mag_action = '-'
                        data_source = '-'
                    else:
                        proc_states[proc] = 'S'
                        was_exclusive = False
                        for i in range(1, no_processors + 1):
                            if proc_states[i] == 'E':
                                was_exclusive = True
                                proc_states[i] = 'S'
                                mag_action = "Flush"
                                data_source = f"Cache{possessor}"
                        
                        if not was_exclusive:
                            mag_action = "Flush*"
                            data_source = f"Cache{possessor}"
                            
                else:
                    next_state, action_for_others = graph[proc_states[proc]]['Rd']
                    data_source = "-"
                    data_s = "-"
                    mag_action = action_for_others
                    for i in range(1, no_processors + 1):
                        if i != proc:
                            if action_for_others in graph[proc_states[i]].keys():
                                if proc_states[i] != 'I':
                                    data_source = f"Cache{i}"
                                proc_states[i], data_s = graph[proc_states[i]][action_for_others]
                    
                    if data_source == "-":
                        data_source = data_s
                    proc_states[proc] = next_state
            # Write                
            else:
                next_state, action_for_others = graph[proc_states[proc]]['Wr']
                proc_states[proc] = next_state
                data_s = "-"
                data_source = "-"
                have_written = True
                
                # start with Wr case
                if all_invalid:
                    possessor = proc
                all_invalid = False
                mag_action = action_for_others
                for i in range(1, no_processors + 1):
                    if i != proc:
                        if action_for_others in graph[proc_states[i]].keys():
                            next_state, data_s = graph[proc_states[i]][action_for_others]
                            proc_states[i] = next_state
                            if data_source != 'Flush*':
                                data_source = data_s
                        
        
        print(f"{command} {proc_states[1:]} {mag_action} {data_source}")
