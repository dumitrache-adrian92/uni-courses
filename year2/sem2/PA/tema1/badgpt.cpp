#include <bits/stdc++.h>

using namespace std;

#define INPUT_FILE "badgpt.in"
#define OUTPUT_FILE "badgpt.out"

const int mod = 1000000007;

#define KMAX 2

// returns the mod sum of a and b
uint64_t mod_sum(uint64_t a, uint64_t b) {
	return (a % mod + b % mod) % mod;
}

// returns the mod multiplication of a and b
uint64_t mod_mul(uint64_t a, uint64_t b) {
	return ((a % mod) * (b % mod)) % mod;
}

// converts a numerical character to uint64_t format
uint64_t char_to_int(char c) {
    return c - '0';
}

// multiplies two matrixes and avoids overflow
void multiply_matrix(uint64_t A[KMAX][KMAX], uint64_t B[KMAX][KMAX],
                            uint64_t C[KMAX][KMAX]) {
    uint64_t tmp[KMAX][KMAX];

    for (int i = 0; i < KMAX; ++i) {
        for (int j = 0; j < KMAX; ++j) {
            uint64_t sum = 0;

            for (int k = 0; k < KMAX; ++k)
                sum = mod_sum(sum, mod_mul(A[i][k], B[k][j]));

            tmp[i][j] = sum % mod;
        }
    }

    memcpy(C, tmp, sizeof(tmp));
}

// R = C ^ n using logarithmic exponentiation
void power_matrix(uint64_t C[KMAX][KMAX], uint64_t p, uint64_t R[KMAX][KMAX]) {
    // since R could be C, we'll use a temp matrix
    uint64_t tmp[KMAX][KMAX];

    // identity matrix
    for (int i = 0; i < KMAX; ++i) {
        for (int j = 0; j < KMAX; ++j) {
            tmp[i][j] = (i == j) ? 1 : 0;
        }
    }

    while (p != 1) {
        /* if the power is even do ((C^2)^2)^2... until we reach p */
        if  (p % 2 == 0) {
            multiply_matrix(C, C, C);
            p /= 2;
        } else {
            /* otherwise keep C in tmp so we get an even power and can do
               logarithmic exponentiation */
            multiply_matrix(tmp, C, tmp);
            --p;
        }
    }

    /* build the final matrix (which is the same matrix if the power was
       initially even) or the calculated matrix multiplied by the original
       matrix*/
    multiply_matrix(C, tmp, R);
}

// calculates the nth fibonacci term using matrix exponentiation
uint64_t n_fibonacci(uint64_t n) {
    uint64_t C[KMAX][KMAX] = { {0, 1},
                               {1, 1}};

    // replace C with C^n
    power_matrix(C, n, C);

    // return the element that represents the nth element in the sequence
    return C[1][0] % mod;
}

uint64_t count_original_texts(string s) {
    uint64_t result = 1;

    for (uint32_t i = 0; i < s.size(); i++)
        /* if we found a letter that implies ambiguity, amplify the
           result with number of possibilities of these consecutive letters */
        if ((s[i] == 'u' || s[i] == 'n')) {
            uint32_t j = i + 1;
            uint64_t count = 0;

            // compute how many times the letter repeats
            while (s[j] >= '0' && s[j] <= '9' && j < s.size()) {
                count = count * 1ULL * 10 + char_to_int(s[j]);
                j++;
            }

            // multiply the result by the corresponding Fibonacci number
            result = mod_mul(result, n_fibonacci(count + 1));
        }

    return result;
}

int main(void) {
    // input and output streams
    ifstream input;
    ofstream output;

    input.open(INPUT_FILE, ifstream::in);
    output.open(OUTPUT_FILE, ofstream::out | ofstream::trunc);

    // input string
    string s;

    input >> s;

    // calculate and output the result
    output << count_original_texts(s);

    input.close();
    output.close();

    return 0;
}
