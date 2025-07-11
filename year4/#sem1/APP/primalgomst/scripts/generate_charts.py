import matplotlib.pyplot as plt
import os
import pandas as pd
import subprocess
import time
import numpy as np

def generate_total_time_barplot(times):
    """Generates a chart of the total time of the MST problem"""
    fig, ax = plt.subplots()
    fig.set_size_inches(15, 9)
    ax.bar(times.keys(), times.values(), align='edge', width=0.2)
    ax.set_xticklabels(times.keys(), rotation=30)
    ax.set_title("Total time of serial Prim's algorithm for different graphs")
    ax.set_ylabel("Total time (s)")
    plt.savefig("../media/total_time_serial.png")

def generate_compared_total_time_barplot_side_by_side(times1, times2):
    """Generates a chart of the total time of the MST problem"""
    fig, ax = plt.subplots()
    fig.set_size_inches(15, 9)
    ax.bar(np.arange(len(times1)), times1.values(), align='edge', width=0.2, label="Serial")
    ax.bar(np.arange(len(times2)) + 0.25, times2.values(), align='edge', width=0.2, label="Pthreads")
    ax.set_xticks(np.arange(len(times1)))
    ax.set_xticklabels(times1.keys(), rotation=30)
    ax.set_title("Total time of serial vs pthreads")
    ax.set_ylabel("Total time (s)")
    ax.legend()
    plt.savefig("../media/total_time_serial_vs_pthreads.png")

def generate_compared_total_time_barplot_side_by_side_by_side(times1, times2, times3):
    """Generates a chart of the total time of the MST problem"""
    fig, ax = plt.subplots()
    fig.set_size_inches(15, 9)
    ax.bar(np.arange(len(times1)), times1.values(), align='edge', width=0.2, label="Serial")
    ax.bar(np.arange(len(times2)) + 0.25, times2.values(), align='edge', width=0.2, label="Pthreads")
    ax.bar(np.arange(len(times3)) + 0.5, times3.values(), align='edge', width=0.2, label="OpenMP")
    ax.set_xticks(np.arange(len(times1)))
    ax.set_xticklabels(times1.keys(), rotation=30)
    ax.set_title("Total time of serial vs pthreads vs openmp")
    ax.set_ylabel("Total time (s)")
    ax.legend()
    plt.savefig("../media/total_time_serial_vs_pthreads_vs_openmp.png")

def get_csv_file_in_folder(path):
    """Gets the csv file in the folder"""
    for f in os.scandir(path):
        if f.is_file() and f.name.endswith(".csv"):
            return f

def get_times_dict(folder_path):
    """Gets the total time for each test in the folder"""
    filter_tests = ["dense_graph", "huge_graph", "sparse_graph"]
    tests = [f.name for f in os.scandir(folder_path) if f.is_dir() and f.name in filter_tests]
    times = [get_total_time(get_csv_file_in_folder(f"{folder_path}/{test}")) for test in tests]
    serial_prim_totals = zip(tests, times)
    serial_prim_totals = dict(sorted(serial_prim_totals, key=lambda x: x[1]))

    return serial_prim_totals

def get_total_time(filepath):
    """Parses the total time from the file"""
    df = pd.read_csv(filepath, header=None, sep="\t")

    result = 0.0

    for x in df[1]:
        if x == "CPU Time":
            continue

        result += float(x)

    return result

def generate_prim_as_a_function_of_n(time_path, image_name):
    n_to_time = {}

    with open(time_path, "r") as f:
        n = 50
        for line in f:
            time = line.replace("\n", "").replace(",", ".")
            n_to_time[n] = float(time)
            n += 50

    n_to_time = sorted(n_to_time.items())
    n = [x[0] for x in n_to_time]
    times = [x[1] for x in n_to_time]

    fig, ax = plt.subplots()
    fig.set_size_inches(15, 9)
    ax.plot(n, times)
    ax.set_title("Prim's algorithm as a function of N")
    ax.set_xlabel("N")
    ax.set_ylabel("Time (s)")
    plt.savefig(f"../media/{image_name}")

def generate_prim_as_a_function_of_p(time_path, image_name):
    n_to_time = {}

    with open(time_path, "r") as f:
        n = 2
        for line in f:
            time = line.replace("\n", "").replace(",", ".")
            n_to_time[n] = float(time)
            n *= 2

    n_to_time = sorted(n_to_time.items())
    n = [x[0] for x in n_to_time]
    times = [x[1] for x in n_to_time]

    fig, ax = plt.subplots()
    fig.set_size_inches(15, 9)
    ax.plot(n, times)
    ax.set_title("Prim's algorithm as a function of P")
    ax.set_xlabel("P")
    ax.set_ylabel("Time (s)")
    plt.savefig(f"../media/{image_name}")


if __name__ == "__main__":
    SERIAL_RESULTS_PATH = "../../../Downloads/serial_prim"
    pthreads_results_dict = {
        "sparse_graph": 2.105,
        "huge_graph": 2.294,
        "dense_graph": 2.511,
    }
    openmp_results_dict = {
        "sparse_graph": 2.3,
        "huge_graph": 2.5,
        "dense_graph": 2.8,
    }
    # print(get_times_dict(SERIAL_RESULTS_PATH))``

    # generate_total_time_barplot(get_times_dict(SERIAL_RESULTS_PATH))
    # generate_compared_total_time_barplot_side_by_side(get_times_dict(SERIAL_RESULTS_PATH), pthreads_results_dict)
    generate_compared_total_time_barplot_side_by_side_by_side(get_times_dict(SERIAL_RESULTS_PATH), pthreads_results_dict, openmp_results_dict)

    # generate_prim_as_a_function_of_n("../tmp/serial_time.log", "serial_prim_as_a_function_of_n.png")
    # generate_prim_as_a_function_of_n("../tmp/pthreads_time.log", "pthreads_prim_as_a_function_of_n.png")
    # generate_prim_as_a_function_of_n("../tmp/openmp_time.log", "openmp_prim_as_a_function_of_n.png")


    # generate_prim_as_a_function_of_p("../tmp/p_pthreads_time.log", "pthreads_prim_as_a_function_of_p.png")
    # generate_prim_as_a_function_of_p("../tmp/p_openmp_time.log", "openmp_prim_as_a_function_of_p.png")

    # generate_prim_as_a_function_of_n("../tmp/mpi_time.log", "mpi_prim_as_a_function_of_n.png")
    # generate_prim_as_a_function_of_p("../tmp/hybrid_time.log", "hybrid_prim_as_a_function_of_p.png")