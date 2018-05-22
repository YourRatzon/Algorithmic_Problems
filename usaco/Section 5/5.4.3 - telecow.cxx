#include <bits/stdc++.h>

/*
ID: jamerz1
PROG: telecow
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


vector<vector<int>> adj_matrix;
int N, E, s, t;
int num_vert;
ll max_flow = 0;
vector<bool > visited;
vector<int> parent;
set<int> min_vertex_cut;
vii edge_list;


int augment(int v, int min_edge) {
	if (v == s) { // DONE!!
		return min_edge;
	}
	int parent_v = parent[v];
	min_edge = min(min_edge, adj_matrix[parent_v][v]);
	min_edge = augment(parent_v, min_edge);
	adj_matrix[parent_v][v] -= min_edge;
	adj_matrix[v][parent_v] += min_edge;
	return min_edge;
}


int find_max_flow();
void reset_flow_capacities();

void find_min_vertex_cut(int max_flow, set<int>& min_vertex_cut) {
	int last_flow = max_flow;
	for (int i = 1; i <= N; ++i) {
		if (i == s || i == t)
			continue;
		reset_flow_capacities();
		for (int vert : min_vertex_cut) {
			adj_matrix[vert][vert + N] = 0;
			adj_matrix[vert + N][vert] = 0;
		}
		adj_matrix[i][i + N] = 0;
		adj_matrix[i + N][i] = 0;

		int curr_flow = find_max_flow();
		if (curr_flow < last_flow) {
			min_vertex_cut.insert(i);
			last_flow = curr_flow;
		}
		if (min_vertex_cut.size() > max_flow) {
			min_vertex_cut.erase(std::prev(min_vertex_cut.end()));
		}
	}
}


int find_max_flow() {
	int max_flow = 0;
	int curr_flow = 0;
	while (true) {
		queue<int> q;
		q.push(s);
		visited.assign(num_vert + 1, false);
		parent.assign(num_vert + 1, -1);
		visited[s] = true;
		while (!q.empty()) {
			int u = q.front();
			if (u == t) // done!
				break;
			q.pop();
			for (int v = 1; v < adj_matrix[u].size(); ++v) {
				if (!visited[v] && adj_matrix[u][v] > 0) {
					visited[v] = true;
					parent[v] = u;
					if (v == t)
						break;
					q.push(v);
				}
			}
		}
		if (parent[t] == -1)
			return max_flow;
		curr_flow = augment(t, INF);
		if (curr_flow == 0)
			return max_flow;
		else
			max_flow += curr_flow;
	}
	return max_flow;
}

void reset_flow_capacities() {
	for (int i = 1; i <= N; ++i) {
		int cap;
		if (i == s || i == t)
			cap = INF;
		else
			cap = 1;
		adj_matrix[i][N + i] = cap;
		adj_matrix[N + i][i] = cap;
	}

	for (int i = 0; i < edge_list.size(); ++i) {
		int u = edge_list[i].first;
		int v = edge_list[i].second;
		if (u + N == v) {
			adj_matrix[u][v] = INF;
			adj_matrix[v][u] = INF;
		}
		else {
			adj_matrix[N + u][v] = INF;
			adj_matrix[v + N][u] = INF;
		}
	}
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//start_timer();

	ifstream fin("telecow.in");
	ofstream fout("telecow.out");

	fin >> N >> E >> s >> t;
	if (s > t) swap(s, t); // now s < t
	num_vert = 2 * N;
	adj_matrix.assign(num_vert + 1, vi(num_vert + 1, 0));
	int u, v;
	// for v != s,t, Vin = <input>, Vout=N+<input>
	// IN -> OUT
	// 1 -> N + 1
	// 3 -> N + 3;
	// N -> N + N;
	edge_list.resize(E);
	for (int i = 0; i < E; ++i) {
		fin >> u >> v;
		edge_list[i] = { u, v };
	}
	fin.close();
	reset_flow_capacities();

	if (N == 2) {
		fout << 0 << '\n';
		return 0;
	}
	int max_flow = find_max_flow();
	find_min_vertex_cut(max_flow, min_vertex_cut);

	fout << min_vertex_cut.size() << '\n';
	auto it = min_vertex_cut.begin();
	fout << *it;
	++it;
	for (; it != min_vertex_cut.end(); ++it) {
		fout << ' ' << *it;
	}
	fout << '\n';
	fout.close();


	//print_timer();
	return 0;
}