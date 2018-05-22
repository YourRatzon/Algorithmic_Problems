#include <bits/stdc++.h>

/*
ID: jamerz1
PROG: cbarn
LANG: C++11
*/

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << __duration << '\n';
}
// END TIMER

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-9;
bool eq(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = ll(1e18);

int X, Y, M, K;
vii DP;
int get_best(int k) {
	ii save = DP[k];
	int new_X=save.first, new_Y = save.second;
	int total_best = abs(DP[k].first + DP[k].second - M);

	if (save.first < X) {
		new_X = min(save.first +save.second, X);
		if (new_X > save.first) {
			new_Y = save.second - (new_X - save.first);
		}

		if (abs(new_X +new_Y- M) < total_best) {
			total_best = abs(new_X+new_Y - M);
			DP[k].first = new_X;
			DP[k].second = new_Y;
		}
	}
	new_X = save.first, new_Y = save.second;
	if (save.second < Y) {
		new_Y = min(save.second +save.first, Y);

		if (new_Y> save.second) {
			new_X = save.first - (new_Y - save.second);
		}
		if (abs(new_Y +new_X- M) < total_best) {
			total_best = abs(new_Y +new_X- M);
			DP[k].second = new_Y;
			DP[k].first = new_X;

		}
	}
	if (abs(save.first - M) < total_best){
		total_best = abs(save.first - M);
		DP[k].second = 0;
		DP[k].first = save.first;
	}
	if (abs(save.second - M) < total_best){
		total_best = abs(save.second - M);
		DP[k].first = 0;
		DP[k].second = save.second;
	}
	if (abs(save.first + Y - M)<total_best) {
		total_best = abs(save.first + Y - M);
		DP[k].second = Y;
		DP[k].first = save.first;
	}
	if (abs(save.second + X - M)<total_best) {
		total_best = abs(save.second + X - M);
		DP[k].first = X;
		DP[k].second = save.second;
	}
	return total_best;
}
int solve(int x, int y, int m, int k) {
	if (k == 1) {
		int res = M;
		DP[1] = { 0, 0 };
		if (abs(M - x) < res) {
			DP[1] = { x, 0 };
			res = abs(m-x);
		}
		if (abs(M - y) < res) {
			DP[1] = { 0, y };
			res =abs(m- y);
		}
		return res;
	}

	if (DP[k - 1].first == -1) {
		solve(x, y, m, k - 1);
	}
	DP[k] = DP[k - 1];
	int total_best = get_best(k);
	return total_best;
}
int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//start_timer();

	ifstream fin("pails.in");
	ofstream fout("pails.out");

	fin >> X >> Y >> K>>M;
	DP.assign(K + 1, { -1, -1});
	int res = solve(X, Y, M, K);
	fout << res << '\n';
	fin.close();
	fout.close();
	//print_timer();
	return 0;
}