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
const ll MOD = int(1e9) + 7;

ll power_mod(ll a, ll exp, ll MOD) {
	if (exp == 0)
		return 1;
	ll res = 1;
	while (exp) {
		if (exp % 2 == 0) {
			a = (a*a) % MOD;
			exp /= 2;
		}
		else {
			res = (res*a) % MOD;
			exp -= 1;
		}
	}
	return res;
}

ll power_mod_rec(ll a, ll exp, ll MOD) {
	if (exp == 0)
		return 1;
	ll res;
	if (exp % 2 == 0)
		res = power_mod_rec((a*a) % MOD, exp / 2, MOD);
	else
		res = a * power_mod_rec(a, exp - 1, MOD);
	return res%MOD;
}

vector<bool> visited;
vector<bool> done;
vi edges;

int DFS(int u) {
	visited[u] = true;
	int v = edges[u];
	if (!visited[v])
		return DFS(v);
	else if (!done[v]) {
		int cycle_sz = 1;
		int start = u;
		vi curr_cycle = { u };
		u = v;
		while (u != start && !done[u]) {
			curr_cycle.push_back(u);
			cycle_sz++;
			u = edges[u];
		}
		if (u == start) {
			for (int u : curr_cycle)
				done[u] = true;
			return cycle_sz;
		}
		else
			return 0;
	}
	else
		return 0;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	
	int n;
	scanf("%d", &n);
	edges.resize(n + 1);
	visited.assign(n + 1, false);
	done.assign(n + 1, false);

	int v;
	for (int u = 1; u <= n; ++u) {
		scanf("%d", &v);
		edges[u] = v;
	}
	ll res = 1;
	for (int u = 1; u <= n; ++u) {
		if (!visited[u]) {
			int cycle_sz = DFS(u);
			if (cycle_sz > 0) {
				ll add_sets = power_mod_rec(2, cycle_sz, MOD) - 2;
				if (add_sets < 0)
					add_sets += MOD;
				res = (res*add_sets) % MOD;
			}
		}
	}
	ll non_cycle_nodes = 0;
	for (int i = 1; i <= n; ++i)
		if (!done[i])
			++non_cycle_nodes;
	ll add_sets = power_mod_rec(2, non_cycle_nodes, MOD);
	res = (res*add_sets) % MOD;

	cout << res << '\n';
	return 0;
}

