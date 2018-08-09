
#include <stdio.h>
#include <bits/stdc++.h>

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
typedef vector<bool> vb;
typedef vector<char> vc;

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1e6 + 5;

struct Edge {
	int u, v, w;
	bool operator<(const Edge& other) {
		return w < other.w;
	}
	bool operator==(const Edge& other) {
		return w == other.w && u == other.u && v == other.v;
	}
};

vector<Edge> elist;
vi parent;
vi ranks;
int nset;

void make_set(int N) {
	ranks.assign(N, 0);
	parent.resize(N);
	nset = N;
	for (int i = 0; i < N; ++i)
		parent[i] = i;
}

int find_set(int u) {
	if (parent[u] == u)
		return u;
	return parent[u] = find_set(parent[u]);
}

void union_set(int u, int v) {
	int pu = find_set(u);
	int pv = find_set(v);
	if (pu == pv)
		return;
	--nset;
	if (ranks[pu] < ranks[pv])
		swap(pu, pv);
	parent[pv] = pu;
	if (ranks[pu] == ranks[pv])
		ranks[pu]++;
}

int kruskal(vector<Edge>& mst) {
	int totalw = 0;
	for(int i = 0; nset > 1; ++i) {
		Edge e = elist[i];
		if (find_set(e.u) != find_set(e.v)) {
			union_set(e.u, e.v);
			mst.push_back(e);
			totalw += e.w;
		}
	}
	return totalw;
}

int kruskal2(Edge eno) {
	int totalw = 0;
	for(int i = 0; i<elist.size() && nset > 1; ++i) {
		Edge e = elist[i];
		if (e == eno)
			continue;
		if (find_set(e.u) != find_set(e.v)) {
			union_set(e.u, e.v);
			totalw += e.w;
		}
	}
	if (nset>1)
		totalw = INF;
	return totalw;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T,N,M, u, v, w;
	cin>>T;
	while(T--) {
		cin>>N>>M;
		make_set(N);
		elist.resize(M);
		for (int i = 0; i < M; ++i) {
			cin >> u >> v >> w;
			--u, --v;
			elist[i] = {u, v, w};
		}
		sort(elist.begin(), elist.end());
		vector<Edge> mst;
		int bestw = kruskal(mst);
		int next_bestw = INF;
		for (int i = 0; i < mst.size(); ++i) {
			make_set(N);
			int currw = kruskal2(mst[i]);
			next_bestw = min(next_bestw, currw);
		}
		cout<<bestw<<' '<<next_bestw<<'\n';
	}

  return 0;
}
