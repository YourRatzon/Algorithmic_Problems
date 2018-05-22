#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;


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


const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;

vi node_weights;
vector<vi> adj_list;
vector<bool> visited;
vector<double> results1, results2, results;
vi parent;
vi num_children;

void DFS1(int u) {
	visited[u] = true;
	vi my_children;
	for (int i = 0; i < adj_list[u].size(); ++i) {
		int v = adj_list[u][i];
		if (!visited[v]) {
			my_children.push_back(v);
			DFS1(v);
		}
		else {
			parent[u] = v;
		}
	}
	num_children[u] = my_children.size();
	results1[u] = node_weights[u];
	double sum = 0;
	if (!my_children.empty()) {
		for (int v : my_children)
			sum += results1[v];
		results1[u] += (sum / my_children.size());
	}
}

bool is_leaf(int u) { return adj_list[u].size() == 1; }

void DFS2(int u) {
	visited[u] = true;
	int my_parent = parent[u];
	results2[u] = node_weights[u];
	double sum = 0;
	if (is_leaf(my_parent))
		results2[u] += node_weights[my_parent];
	else {
		sum = results2[my_parent]-node_weights[my_parent];
		for (int i = 0; i < adj_list[my_parent].size(); ++i) {
			int v = adj_list[my_parent][i];
			if (v != u && parent[my_parent] != v)
				sum += results1[v];
		}
		results2[u] += node_weights[my_parent];
		results2[u] += sum / (adj_list[my_parent].size() - 1);
	}
	
	for (int i = 0; i < adj_list[u].size(); ++i) {
		int v = adj_list[u][i];
		if (!visited[v])
			DFS2(v);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N;
	cin >> N;
	node_weights.resize(N + 1);
	adj_list.assign(N + 1, vi());
	for (int i = 1; i <= N; ++i)
		cin >> node_weights[i];
	int u, v;
	for (int i = 0; i < N - 1; ++i) {
		cin >> u >> v;
		adj_list[u].push_back(v);
		adj_list[v].push_back(u);
	}
	parent.resize(N + 1);
	num_children.resize(N + 1, 0);
	results1.assign(N + 1, 0);
	results2.assign(N + 1, 0);
	results.assign(N + 1, 0);
	visited.assign(N + 1, false);
	int root_idx = 0;
	for (int i = 1; i <= N; ++i) {
		if (is_leaf(i)) {
			root_idx = i;
			DFS1(i);
			break;
		}
	}
	visited.assign(N + 1, false);
	visited[root_idx] = true;
	DFS2(adj_list[root_idx][0]);

	double min_res = INF_LL;
	int best_q;
	for (int i = 1; i <= N; ++i) {
		if (i == root_idx)
			results[i] = results1[i];
		else {
			results[i] = (results2[i] + results1[i] * num_children[i]) /	
						 (num_children[i]+1);
		}
		if (results[i] < min_res) {
			min_res = results[i];
			best_q = i;
		}
	}

	cout << best_q << '\n';
	return 0;
}
