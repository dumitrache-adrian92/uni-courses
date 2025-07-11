"""Generates test files for the MST problem"""

import argparse
from generate_random_connected_graph import generate_random_connected_graph
from concurrent.futures import ThreadPoolExecutor

def serialize_graph(graph,
                    target_fillepath):
    """Serializes the graph into a string"""
    n = len(graph)
    with open(target_fillepath, mode="w", encoding='ascii') as file:
        file.truncate(0)

        file.write(f"{n}\n")
        for i in range(n):
            for j in range(n):
                file.write(f"{graph[i][j]} ")

            file.write("\n")



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="A script for generating MST test files")
    parser.add_argument("tests_path", type=str, help="Path to the tests directory")
    args = parser.parse_args()
    TESTS_PATH = args.tests_path
    sparseness_factor = 0.3
    min_weight = 1
    max_weight = 100

    tests = [(f"{TESTS_PATH}/graph_{i}", (i, min_weight, max_weight, sparseness_factor, f"Generating {i} graph"))
                    for i in range(50, 2501, 50)]

    with ThreadPoolExecutor(max_workers=len(tests)) as executor:
        executor.map(lambda x: serialize_graph(generate_random_connected_graph(*x[1]), x[0]), tests)
