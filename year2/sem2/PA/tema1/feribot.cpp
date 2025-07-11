#include <bits/stdc++.h>

using namespace std;

#define INPUT_FILE "feribot.in"
#define OUTPUT_FILE "feribot.out"
#define uint64_t unsigned long long

// calculates the sum of all elements in v, because std::accumulate overflows
uint64_t vector_sum(vector<uint64_t> v, uint64_t N) {
    uint64_t max = 0;

    for (uint64_t i = 0; i < N; i++) {
        max += v[i];
    }

    return max;
}

/* checks if there's anyway to split the vector into K or less subvectors so
   that the subvector whose sum of all elements is the greatest out of all
   subvectors is still less than cost */
bool can_split(vector<uint64_t> costs, uint64_t N, uint64_t K, uint64_t cost) {
    uint64_t sum;
    uint64_t subvectors;

    sum = 0;         // sum of the current subvector
    subvectors = 0;  // total number of subvectors

    // loop through the vector to build subvectors
    for (uint64_t i = 0; i < N; i++) {
        // if a cost goes over the current cap, there's no possible solution
        if (costs[i] > cost)
            return false;

        /* check if we can add the cost of the current element to the
           sequence without going over the cap,
           otherwise start a new subvector */
        if (sum + costs[i] > cost) {
            subvectors++;
            sum = costs[i];

            // it's impossible if we've already gone over the subvector limits
            if (subvectors > K)
                return false;
        } else {
            sum += costs[i];
        }
    }
    subvectors++;  // count the last sequence

    // if we haven't gone over the cap, this is our solution
    return subvectors <= K;
}

/* returns the minimum cost which allows us to split the vector in K or less
   subvectors so that the subvector whose sum of all elements is the greatest
   out of all subvectors is still less than the minimum cost found */
uint64_t find_minimum_cost(vector<uint64_t> costs, uint64_t N, uint64_t K) {
    uint64_t cost_to_check;
    uint64_t solution;

    /* lower and upper bound of the possible
       minimum costs (maximum element and sum of all elements) */
    uint64_t min = *max_element(costs.begin(), costs.end());
    uint64_t max = vector_sum(costs, N);

    // perform a binary search between all the possible costs ([min, max])
    while (min <= max) {
        // grab an element from the current interval
        cost_to_check = (max + min) / 2;

        /* if it leads to a solution, memorize it and narrow down the interval
           trying to find an even lower cost,
           otherwise, search only the higher costs*/
        if (can_split(costs, N, K, cost_to_check)) {
            max = cost_to_check - 1;
            solution = cost_to_check;
        } else {
            min = cost_to_check + 1;
        }
    }

    return solution;
}

int main(void) {
    // input and output streams
    ifstream input;
    ofstream output;

    input.open(INPUT_FILE, ifstream::in);
    output.open(OUTPUT_FILE, ofstream::out | ofstream::trunc);

    // number of cars and number of ferries
    uint64_t N, K;
    // cost of each car
    // note: costs can go up to a trillion so we're using uint64_t
    vector<uint64_t> costs;

    // reading from file
    input >> N;
    input >> K;

    uint64_t temp;  // temporary value for reading
    for (uint64_t i = 0; i < N; i++) {
        input >> temp;
        costs.push_back(temp);
    }

    // calculate and output the result
    output << find_minimum_cost(costs, N, K);

    input.close();
    output.close();

    return 0;
}
