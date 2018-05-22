//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

//#define F first
//#define S second

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

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

double EPS = 1e-16;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

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


# define M_PI		3.14159265358979323846
const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1000 + 5;

ll memo[MAX_N][MAX_N][2];

vii hol, gue;
vll hh_dist, gg_dist;
vector<vll> hg_dist, gh_dist;
int H, G;

ll solve(int i, int j, int k) {
	if (memo[i][j][k] != -1)
		return memo[i][j][k];
	if (i > H || j > G || (i==H && j < G))
		return memo[i][j][k] = INF;

	if (memo[i + 1][j][0] == -1)
		solve(i + 1, j, 0);
	if (memo[i][j + 1][1] == -1)
		solve(i, j + 1, 1);
	if (k == 0) {
		ll next_H_dist = hh_dist[i];
		ll next_G_dist = hg_dist[i][j + 1];
		memo[i][j][k] = min(memo[i + 1][j][0] + next_H_dist,
							memo[i][j+1][1] + next_G_dist);
	}
	else {
		ll next_G_dist = gg_dist[j];
		ll next_H_dist = gh_dist[j][i + 1];
		memo[i][j][k] = min(memo[i][j + 1][1] + next_G_dist,
						    memo[i + 1][j][0] + next_H_dist);
	}
}

ll get_dist(int i, int j, const vii& A, const vii& B) {
	ll width = (A[i].first - B[j].first);
	ll height = (A[i].second - B[j].second);
	return width*width + height*height;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	
	ifstream fin("checklist.in");
	ofstream fout("checklist.out");

	int x,y;
	fin >> H >> G;
	hol.resize(H+3), gue.resize(G+3);
	for (int i = 1; i <= H; ++i) {
		fin >> x >> y;
		hol[i] = { x, y };
	}
	for (int i = 1; i <= G; ++i) {
		fin >> x >> y;
		gue[i] = { x, y };
	}
	for (int i = 0; i <= H + 4; ++i) {
		for (int j = 0; j <= G + 4; ++j) {
			memo[i][j][0] = -1;
			memo[i][j][1] = -1;
		}
	}
	memo[H][G][1] = INF;
	for (int i = 0; i < G; ++i) {
		memo[H][i][0] = INF;
		memo[H][i][1] = INF;
		memo[H + 1][i][0] = INF;
		memo[H + 1][i][1] = INF;
	}
	memo[H + 1][G][0] = INF;
	memo[H + 1][G][1] = INF;
	for (int i = 0; i < H; ++i) {
		memo[i][G + 1][0] = INF;
		memo[i][G + 1][1] = INF;
	}
	memo[H][G + 1][0] = INF;
	memo[H][G + 1][1] = INF;
	
	memo[H][G][0] = 0;

	hh_dist.assign(H + 4, INF);
	gg_dist.assign(G + 4, INF);
	hg_dist.assign(H + 4, vll(G + 4, INF));
	gh_dist.assign(G + 4, vll(H + 4, INF));

	for (int i = 1; i < H; ++i) {
		hh_dist[i] = get_dist(i, i + 1, hol, hol);
	}
	for (int i = 1; i < G; ++i) {
		gg_dist[i] = get_dist(i, i + 1, gue, gue);
	}
	for (int i = 1; i < H; ++i) {
		for (int j = 1; j <= G; ++j) {
			hg_dist[i][j] = gh_dist[j][i] = get_dist(i, j, hol, gue);
		}
	}
	gh_dist[G][H] = get_dist(G, H, gue, hol);
	solve(1, 0, 0);
	fout << memo[1][0][0] << '\n';
	return 0;
}