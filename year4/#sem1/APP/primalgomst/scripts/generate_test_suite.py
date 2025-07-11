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
    tests = [
        (f"{TESTS_PATH}/small_graph.txt", (25, 1, 100, 0.3, "Generating small graph...")),
        (f"{TESTS_PATH}/medium_graph.txt", (300, 1, 100, 0.3, "Generating medium graph...")),
        (f"{TESTS_PATH}/large_graph.txt", (750, 1, 100, 0.3, "Generating large graph...")),
        (f"{TESTS_PATH}/huge_graph.txt", (10000, 1, 100, 0.3, "Generating huge graph...")),
        (f"{TESTS_PATH}/sparse_graph.txt", (10000, 1, 100, 0.05, "Generating sparse graph...")),
        (f"{TESTS_PATH}/dense_graph.txt", (10000, 1, 100, 0.85 , "Generating dense graph...")),
        (f"{TESTS_PATH}/small_weights_graph.txt", (10000, 1, 10, 0.3 , "Generating graph with small weights...")),
        (f"{TESTS_PATH}/large_weights_graph.txt", (10000, 100, 1000, 0.3, "Generating graph with large weights..."))
    ]

    with ThreadPoolExecutor(max_workers=len(tests)) as executor:
        executor.map(lambda x: serialize_graph(generate_random_connected_graph(*x[1]), x[0]), tests)
