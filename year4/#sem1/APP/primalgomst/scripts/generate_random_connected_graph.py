"""A script for generating random connected graphs of size n"""

import argparse
import random

def generate_random_connected_graph(n,
                                    min_weight,
                                    max_weight,
                                    sparseness_factor,
                                    message=""):
    """Generates a random connected graph of size n"""
    print(message)
    graph = [[0 for _ in range(n)] for _ in range(n)]
    # Generate a random spanning tree
    for i in range(1, n):
        # Choose a random parent for the current node from the nodes already in the tree
        parent = random.randint(0, i - 1)
        # Choose a random weight for the edge between the current node and its parent
        weight = random.randint(min_weight, max_weight)

        # Add the edge to the graph
        graph[parent][i] = weight
        graph[i][parent] = weight

    # Add the remaining edges
    for i in range(n):
        for j in range(i + 1, n):
            if graph[i][j] == 0 and random.random() < sparseness_factor:
                weight = random.randint(min_weight, max_weight)
                graph[i][j] = weight
                graph[j][i] = weight

    return graph


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                description="A script for generating random connected graphs of size n")

    parser.add_argument("n",
                        type=int,
                        help="Number of nodes in the graph")

    parser.add_argument("--max-weight",
                        type=int,
                        default=500,
                        help="Maximum weight of an edge, 500 by default")

    parser.add_argument("--min-weight",
                        type=int,
                        default=1,
                        help="Minimum weight of an edge, 1 by default")

    parser.add_argument("--sparseness-factor",
                        type=float,
                        default=0.1,
                        help="Sparseness factor of the graph, \
or the probability of an edge existing between two nodes, 0.1 by default")

    args = parser.parse_args()

    g = generate_random_connected_graph(args.n,
                                    args.min_weight,
                                    args.max_weight,
                                    args.sparseness_factor)
