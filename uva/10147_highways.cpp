
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



vector<int> parent;
vector<int> set_rank;
int nsets;

void make_set(int N) {
	nsets = N;
	set_rank.assign(N, 0);
	parent.resize(N);
	for (int i = 0; i < N; ++i)
		parent[i] = i;

}

int find_set(int u) {
		if (parent[u] == u)
			return u;
		return parent[u] = find_set(parent[u]);
}

void union_sets(int u, int v) {
	int pu = find_set(u);
	int pv = find_set(v);
	if (pu == pv)
		return;

	if (set_rank[pu] < set_rank[pv])
		swap(pu, pv);
	parent[pv] = pu;
	if (set_rank[pv]==set_rank[pu])
		set_rank[pu]++;

	nsets--;
}

struct Edge {
	Edge(int _u, int _v, double _w) : u(_u), v(_v), w(_w) {}
	int u, v;
	double w;
	bool operator<(Edge const& other) {
		return w < other.w;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T, N, M, x, y, u, v;
	cin>>T;
	while(T--) {
		cin >> N;
		make_set(N);
		vii verts(N);
		for (int i = 0; i < N; ++i) {
			cin >> x>> y;
			verts[i] = {x,y};
		}
		cin >> M;
		for (int i = 0; i < M; ++i) {
			cin >> u >> v;
			--u, --v;
			union_sets(u, v);
		}

		vector<Edge> edges;
		double w;
		for (int i = 0; i < N; ++i) {
			for (int j = i+1; j < N; ++j) {
				w = pow(verts[i].first-verts[j].first, 2) +
					  pow(verts[i].second-verts[j].second, 2);
				edges.push_back(Edge(i,j,w));
			}
		}
		sort(edges.begin(), edges.end());
		vii res;
		for (int i = 0; nsets > 1; ++i) {
			Edge e = edges[i];
			if (find_set(e.u) != find_set(e.v)) {
				res.push_back({e.u+1,e.v+1});
				union_sets(e.u, e.v);
			}
		}

		if (res.empty()) {
			cout<<"No new highways need\n";
		}
		else {
			for (ii p : res)
				cout<<p.first<<' '<<p.second<<'\n';
		}
		if (T)
			cout<<'\n';
	}
  return 0;
}
