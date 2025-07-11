"""Generates a time graph for the SM lab1 exercises"""

import subprocess
import matplotlib.pyplot as plt

# Create a list of n values
n = [2, 4, 8, 16]

# Run ./lab1 for each value of n and record the time taken
serial_times = []
crcw_times = []
crew_times = []
for i in n:
    # Run the program and record the time taken
    time = subprocess.run(["./lab1", str(i)], capture_output=True, text=True, check=True).stdout
    # Split by newline
    time = time.split("\n")
    # Get the time taken
    serial_times.append(float(time[0]))
    crcw_times.append(float(time[1]))
    crew_times.append(float(time[2]))

# Plot the graph
plt.plot(n, serial_times, label="Serial")
plt.plot(n, crcw_times, label="CRCW")
plt.plot(n, crew_times, label="CREW")
plt.xlabel("n")
plt.ylabel("Time taken (s)")
plt.title("Time taken vs n")
plt.legend()

# Save the graph
plt.savefig("graph.png")
plt.show()
