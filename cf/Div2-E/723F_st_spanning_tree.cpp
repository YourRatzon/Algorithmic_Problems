//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

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

double EPS = 1e-9;
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

vii edge_list;
vi parent;
vii span_tree;
vi node_rank;
int num_sets = 0;
void make_set(int i) {
	parent[i] = i;
	node_rank[i] = 0;
	num_sets++;
}

int find_set(int u) {
	if (parent[u] == u)
		return u;
	else
		return parent[u] = find_set(parent[u]);
}

bool set_union(int u, int v) {
	u = find_set(u);
	v = find_set(v);
	if (u == v)
		return false;
	num_sets--;
	if (node_rank[v] < node_rank[u])
		swap(v, u);
	//now: rank[u] <= rank[v]
	parent[u] = v;
	if (node_rank[u] == node_rank[v])
		node_rank[v]++;
	return true;
}

void success() {
	cout << "Yes\n";
	for (ii e : span_tree)
		cout << e.first << ' ' << e.second << '\n';
	exit(0);
}

struct dsu_comp {
	bool operator() (const ii& lhs, const ii &rhs) const {
		return lhs.first < rhs.first;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N, M;
	cin >> N >> M;
	int u, v;
	for (int i = 0; i < M; ++i) {
		cin >> u >> v;
		edge_list.push_back({ u, v });
	}
	int s, t, ds, dt;
	cin >> s >> t >> ds >> dt;

	parent.resize(N + 1);
	node_rank.resize(N + 1);
	for (int i = 1; i <= N; ++i)
		make_set(i);
	vii s_edges, t_edges;
	for (int i = 0; i < M; ++i) {
		u = edge_list[i].first;
		v = edge_list[i].second;
		if (u == s || v == s) {
			s_edges.push_back({ u, v });
			continue;
		}
		if (u == t || v == t) {
			t_edges.push_back({ u, v });
			continue;
		}
		if (set_union(u, v))
			span_tree.push_back({ u, v });
	}

	set<ii, dsu_comp> s_neighs, t_neighs;
	bool s_to_t = false;
	for (ii e : s_edges) {
		if (e.first != s)
			swap(e.first, e.second);
		if (e.second != t)
			s_neighs.insert({ find_set(e.second), e.second });
		else
			s_to_t = true;
	}
	for (ii e : t_edges) {
		if (e.first != t)
			swap(e.first, e.second);
		if (e.second != s)
			t_neighs.insert({ find_set(e.second), e.second });
		else
			s_to_t = true;
	}

	for (ii neigh : s_neighs) {
		if (t_neighs.count(neigh) == 0 && ds > 0) {
			if (set_union(s, neigh.first)) {
				--ds;
				span_tree.push_back({ s, neigh.second });
			}
		}
	}
	for (ii neigh : t_neighs) {
		if (s_neighs.count(neigh) == 0 && dt > 0) {
			if (set_union(t, neigh.first)) {
				--dt;
				span_tree.push_back({ t, neigh.second });
			}
		}
	}

	if (ds > 0) {
		int s_leader = find_set(s);
		for (ii neigh : s_neighs) {
			if (find_set(neigh.first) != s_leader) {
				if (set_union(s, neigh.first)) {
					--ds;
					span_tree.push_back({ s, neigh.second });
					if (num_sets == 1)
						success();
					if (ds <= 0)
						break;
				}
			}
		}
	}

	if (dt > 0) {
		int t_leader = find_set(t);
		for (ii neigh : t_neighs) {
			if (find_set(neigh.first) != t_leader) {
				if (set_union(t, neigh.first)) {
					--dt;
					span_tree.push_back({ t, neigh.second });
					if (num_sets == 1)
						success();
					if (dt <= 0)
						break;
				}
			}
		}
	}
	
	if (s_to_t && dt > 0 && ds > 0) {
		set_union(s, t);
		span_tree.push_back({ s, t});
		if (num_sets == 1)
			success();
	}
	cout << "No\n";
	return 0;
}
