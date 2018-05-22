//#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

/*
ID: jamerz1
PROG: hidden
LANG: C++11
*/

using namespace std;

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
#define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

double EPS_ = 1e-16;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS_);
}

#define F first
#define S second

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef pair<int, int> ii;
typedef pair<double, double> dd;

typedef pair<ll, ll> llll;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<llll> vllll;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<bool> vb;
typedef vector<char> vc;
typedef vector<double> vd;

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;

vector<vi> adjlist;
vii edges;
vi dist;
int N, M;

void BFS(int s, int t) {
	dist.assign(N, INF);
	dist[s] = 0;
	queue<int> q;
	q.push(s);

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < adjlist[u].size(); ++i) {
			int v = adjlist[u][i];
			if ((u == s && v == t )|| (u == t && v == s))
				continue;

			if (dist[v] == INF) {
				dist[v] = dist[u] + 1;
				if (v == t)
					return;
				q.push(v);
			}
		}
	}
}

int main()  {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	
	cin >> N >> M;
	adjlist.assign(N, vi());
	edges.resize(M);
	int u, v;
	for (int i = 0; i < M; ++i) {
		cin >> u >> v;
		adjlist[u].push_back(v);
		adjlist[v].push_back(u);
		edges[i] = { u, v };
	}
	int min_cycle = INF;
	for (int i = 0; i < edges.size(); ++i) {
		u = edges[i].first;
		v = edges[i].second;
		BFS(u, v);
		if (dist[v] != INF)
			min_cycle = min(min_cycle, dist[v] + 1);
	}
	if (min_cycle < INF)
		cout << min_cycle << '\n';
	else
		cout << "impossible" << '\n';
	return 0;
}