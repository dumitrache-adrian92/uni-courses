#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

// returns the mod sum of a and b
uint64_t mod_sum(uint64_t a, uint64_t b) {
	return (a % mod + b % mod) % mod;
}

// returns the mod sum of a, b and c
uint64_t mod_sum(uint64_t a, uint64_t b, uint64_t c) {
	return (a % mod + b % mod + c % mod) % mod;
}

int type1(int x, int y) {
	int i, j;
	/* dp_ends_with_0[i][j] = the number of type 1 signals that end in 0 which
	   can be formed with i 0s and j 1s */
    vector< vector <int> > dp_ends_with_0(x + 1, vector <int>(y + 1, 0));
	/* dp_ends_with_1[i][j] = the number of type 1 signals that end in 1 which
	   can be formed with i 0s and j 1s */
	vector< vector <int> > dp_ends_with_1(x + 1, vector <int>(y + 1, 0));

	// base cases
	// more than one 1 => we can't form any signals, as the 1s will repeat
	// if we have one 1, we have one signal (1)
	dp_ends_with_1[0][1] = 1;

	// if we have x 0s, we have one signal (000...) for x >= 1
	for (i = 1; i <= x; i++)
		dp_ends_with_0[i][0] = 1;

	// use the recurrence to compute the result
	for (i = 1; i <= x; i++)
		for (j = 1; j <= y; j++) {
			// we can add 0 to any signal that has i-1 0s and j 1s
			dp_ends_with_0[i][j] = mod_sum(dp_ends_with_0[i - 1][j],
											dp_ends_with_1[i - 1][j]);
			/* we can add 1 to any signal that has i 0s and j-1 1s, as long as
			   they don't end in 1 (that would result in consecutive 1s) */
			dp_ends_with_1[i][j] = dp_ends_with_0[i][j - 1] % mod;
		}

    return mod_sum(dp_ends_with_0[x][y], dp_ends_with_1[x][y]);
}

int type2(int x, int y) {
    int i, j;
    vector< vector <int> > dp_ends_with_0(x + 1, vector <int>(y + 1, 0));
	vector< vector <int> > dp_ends_with_1(x + 1, vector <int>(y + 1, 0));
	vector< vector <int> > dp_ends_with_11(x + 1, vector <int>(y + 1, 0));

	// base cases
	// we can't form signals that end in 11 if we have anything but two 1s
	// if we have two 1s, we have one signal that ends in 11 (11)
	dp_ends_with_11[0][2] = 1;

	// more than one 1 => we can't form any signals, as the 1s will repeat
	// if we have one 1, we have one signal (1)
	dp_ends_with_1[0][1] = 1;

	// if we have x 0s, we have one signal (000...) for x >= 1
	for (i = 1; i <= x; i++)
		dp_ends_with_0[i][0] = 1;

	for (i = 1; i <= x; i++)
		for (j = 1; j <= y; j++) {
			// we can add 0 to any signal that has i-1 0s and j 1s
			dp_ends_with_0[i][j] = mod_sum(dp_ends_with_0[i - 1][j],
										   dp_ends_with_1[i - 1][j],
										   dp_ends_with_11[i - 1][j]);

			/* we can add 1 to any signal that has i 0s and j-1 1s, as long as
			   they don't end in 1 (those should be counted separately) */
			dp_ends_with_1[i][j] = dp_ends_with_0[i][j - 1] % mod;

			/* we can also add 1 to signals that end in a 1, but we should keep
			   track of them separately so we don't count signals with more
			   than two consecutive ones */
			dp_ends_with_11[i][j] = dp_ends_with_1[i][j - 1] % mod;
		}

    return mod_sum(dp_ends_with_0[x][y],
				   dp_ends_with_1[x][y],
			       dp_ends_with_11[x][y]);
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
