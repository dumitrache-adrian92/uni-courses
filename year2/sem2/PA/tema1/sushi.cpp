#include <bits/stdc++.h>

using namespace std;

/* calculates the total score that a plate
   of sushi is worth based on the preferences in g */
vector <int> compute_sushi_score(vector <vector <int> > g, int friend_n,
															int sushi_n) {
	vector <int> sushi_score(sushi_n);
	for (int i = 0; i < sushi_n; i++) {
		sushi_score[i] = 0;
		for (int j = 0; j < friend_n; j++)
			sushi_score[i] += g[j][i];
	}

	return sushi_score;
}

int task1(int friend_n, int sushi_n, int budget, vector <int>& sushi_price,
												 vector <vector <int> >& g) {
	vector <int> sushi_score(sushi_n);

	// convert the input into something more similar to the knapsack problem
	sushi_score = compute_sushi_score(g, friend_n, sushi_n);
	budget = friend_n * budget;

	/* dp[i][j] = the maximum score we can get with the first i sushi plates
	   and with a budget of j */
	vector<vector <int> > dp(sushi_n + 1, vector <int> (budget + 1, 0));

	// apply the recurrence until we get our result
	for (int i = 1; i <= sushi_n; i++)
		for (int j = 0; j <= budget; j++) {
			dp[i][j] = dp[i - 1][j];

			if (j - sushi_price[i - 1] >= 0) {
                int sol_aux;

				sol_aux = dp[i - 1][j - sushi_price[i - 1]] + sushi_score[i - 1];

                dp[i][j] = max(dp[i][j], sol_aux);
            }
		}

	return dp[sushi_n][budget];
}

// returns a vector that's equal to p concatenated to itself
vector<int> double_sushi(vector<int> p, int m) {
	vector<int> p2(2 * m);

	for (int i = 0; i < 2 * m; i++)
		p2[i] = p[i % m];

	return p2;
}

/* returns a matrix where each line i is the
   corresponding line in g concatenated to itself */
vector<vector <int>> double_grades(vector <vector <int>> g, int n, int m) {
	vector <vector <int>> g2(n, vector <int> (2 * m));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < 2 * m; j++)
			g2[i][j] = g[i][j % m];

	return g2;
}

int task2(int n, int m, int x, vector <int> &p, vector <vector <int>> g) {
	vector<int> p2(2 * m);
	vector <vector <int>> g2(n, vector <int> (2 * m));

	// double the plates of sushi we have and solve it like the previous task
	p2 = double_sushi(p, m);
	g2 = double_grades(g, n, m);

	return task1(n, 2 * m, x, p2, g2);
}

int task3(int friend_n, int sushi_n, int budget, vector <int> &p,
												vector <vector <int> > &g) {
	vector <int> sushi_price(2 * sushi_n);
	vector < vector <int> > g2(friend_n, vector <int> (2 * sushi_n));
	int i, j, k;

	// double the plates of sushi we have
	sushi_price = double_sushi(p, sushi_n);
	g2 = double_grades(g, friend_n, sushi_n);
	sushi_n *= 2;

	vector <int> sushi_score(sushi_n);

	// convert the input into something more similar to the knapsack problem
	sushi_score = compute_sushi_score(g2, friend_n, sushi_n);
	budget = friend_n * budget;

	if (friend_n > sushi_n)
		friend_n = sushi_n;

	/* dp[i][j][k] = the maximum score we can get with the first i sushi plates
	   with a budget of j and k maximum plates */
	vector< vector < vector <int> > > dp(sushi_n + 1,
									vector< vector <int> > (budget + 1,
									vector <int> (friend_n + 1, 0)));

	for (i = 1; i <= sushi_n; i++)
		for (j = 1; j <= budget; j++)
			for (k = 1; k <= friend_n && k <= i; k++) {
				dp[i][j][k] = dp[i - 1][j][k];

				if (j - sushi_price[i - 1] >= 0) {
					int sol_aux;

					sol_aux = dp[i - 1][j - sushi_price[i - 1]][k - 1] +
								sushi_score[i - 1];

					dp[i][j][k] = max(dp[i][j][k], sol_aux);
				}
			}

	return dp[sushi_n][budget][friend_n];
}

int main() {
	ifstream input;
    ofstream output;

    input.open("sushi.in", ifstream::in);
    output.open("sushi.out", ofstream::out | ofstream::trunc);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector < vector <int> > grades;

	input >> task;
	input >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		input >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			input >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	output << ans << endl;

	input.close();
	output.close();

	return 0;
}
