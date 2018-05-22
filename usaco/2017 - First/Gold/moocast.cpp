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
const int MAX_N = 2 * 1e5 + 1;


vii pts;
vector<vector<ll>> sq_dists;
ll get_dist_sq(int i, int j) {
	ll width = abs(pts[i].first - pts[j].first);
	ll height = abs(pts[i].second - pts[j].second);
	ll res = width*width + height*height;
	return res;
}

vector<bool> visited;
vector<vi> adjlist;
void DFS(int u, ll X, int N) {
	visited[u] = true;
	for (int i = 0; i < adjlist[u].size(); ++i) {
		int v = adjlist[u][i];
		if (!visited[v])
			DFS(v, X, N);
	}
}
bool possible(ll X, int N) {
	adjlist.assign(N, vi());
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			if (sq_dists[i][j] <= X) {
				adjlist[i].push_back(j);
				adjlist[j].push_back(i);
			}
		}
	}

	visited.assign(N, false);
	DFS(0, X, N);
	bool success = true;
	for (int j = 0; j < N; ++j) {
		if (!visited[j]) {
			success = false;
			break;
		}
	}
	if (success)
		return true;
	else
		return false;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	
	ifstream fin("moocast.in");
	ofstream fout("moocast.out");
	int N, x, y;
	fin >> N;
	pts.resize(N);
	sq_dists.resize(N, vector<ll>(N, 0));
	for (int i = 0; i < N; ++i) {
		fin >> x >> y;
		pts[i] = { x, y };
	}
	if (N == 1) {
		fout << 0 << '\n';
		return 0;
	}

	for (int i = 0; i < N; ++i) {
		for (int j = i+1; j < N; ++j) {
			sq_dists[i][j] = sq_dists[j][i] = get_dist_sq(i, j);
		}
	}

	ll low = 0, high = 2 * 25000 * 25000;
	ll min_X = INF_LL;
	while (low <= high) {
		ll X = low + (high - low) / 2;
		if (possible(X, N)) {
			min_X = X;
			high = X - 1;
		}
		else {
			low = X + 1;
		}

	}
	fout << min_X << '\n';
	return 0;
}