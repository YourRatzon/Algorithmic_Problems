#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ll, ll> llll;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<llll> vllll;
typedef vector<int> vi;
typedef vector<ull> vull;

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration (msec): " << __duration * 1000 << '\n';
}
// END TIMER

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
//char _;

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-9;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const int MAX_N = 105;

vll tree_colors;
vector<vll> prices;
// color-tree-beauty
ll DP[MAX_N][MAX_N][MAX_N];
ll trees, colors, beauty;

void set_base_case() {

	for (int c = 1; c <= colors; ++c) {
		for (int t = 0; t < trees; ++t) {
			for (int k = 0; k <= beauty + 1; ++k)
				DP[c][t][k] = INF_LL;
		}
	}

	for (int c = 1; c <= colors; ++c) {
		if (tree_colors[0] != 0) {
			if (tree_colors[0] != c)
				DP[c][0][1] = INF_LL;
			else
				DP[c][0][1] = 0;
		}
		else {
			DP[c][0][1] = prices[0][c];
		}
	}


}
void solve() {
	set_base_case();
	for (int t = 1; t < trees; ++t) {
		for (int c = 1; c <= colors; ++c) {
			for (int k = 1; k <= beauty; ++k) {
				if (tree_colors[t] != 0 && tree_colors[t] != c) {
					DP[c][t][k] = INF_LL;
				}
				else {
					ll new_color_min_price = INF_LL;
					for (int last_c = 1; last_c <= colors; ++last_c) {
						if (last_c == c)
							continue;
						new_color_min_price = 
						  min(new_color_min_price, DP[last_c][t - 1][k - 1]);
					}
					DP[c][t][k] = min(new_color_min_price, DP[c][t - 1][k]);
					if (tree_colors[t] == 0 && DP[c][t][k]!=INF_LL)
						DP[c][t][k] += prices[t][c];
				}
			}
		}
	}
	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> trees >> colors >> beauty;
	tree_colors.resize(trees);
	for (int i = 0; i < trees; ++i) {
		cin >> tree_colors[i];
	}
	prices.assign(trees, vll(colors+1));
	ll x;
	for (int i = 0; i < trees; ++i) {
		for (int j = 1; j <= colors; ++j) {
			cin >> prices[i][j];
		}
	}
	solve();

	ll min_res = INF_LL;
	if (tree_colors[trees - 1] != 0)
		min_res = DP[tree_colors[trees - 1]][trees - 1][beauty];
	else {
		for (int c = 1; c <= colors; ++c) {
			min_res = min(min_res, DP[c][trees - 1][beauty]);
		}
	}
	cout << (min_res == INF_LL ? -1 : min_res) << '\n';
	return 0;
}

