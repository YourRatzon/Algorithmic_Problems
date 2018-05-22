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

vector<vii> adj_list;
vi id_to_weight;
vector<vll> res_flow;
int source, sink;

int get_num_verts(int N) {
	int res = 0;
	for (int i = 1; i <= N; ++i) {
		res += i*(i+1) / 2;
	}
	return res;
}

bool legal(int r, int c, const vector<vi>& last_level) {
	return (r >= 0 && r < last_level.size() &&
	    	c >= 0 && c < last_level[r].size());
}

void add_edges(int u, const vii& to_try, const vector<vi>& last_level) {
	for (int i = 0; i < to_try.size(); ++i) {
		int try_r = to_try[i].first;
		int try_c = to_try[i].second;
		if (legal(try_r, try_c, last_level)) {
			int v = last_level[try_r][try_c];
			adj_list[u].push_back({ v, INF });
		}
	}

}

void build_graph(int N, int& curr_id) {
	int x;
	cin >> x;
	id_to_weight[curr_id] = x;
	vector<vi> last_level(1, vi(1, curr_id ));
	curr_id++;

	for (int i = 2; i <= N; ++i) {
		vector<vi> curr_level(i, vi(i));
		for (int j = i; j > 0; --j) {
			for (int c = 0; c < j; ++c) {
				int r = i - j;
				cin >> x;
				id_to_weight[curr_id] = x;
				curr_level[r][c] = curr_id;
				vii to_try = { { r, c }, { r - 1, c }, { r, c - 1 } };
				add_edges(curr_id, to_try, last_level);
				curr_id++;
			}
		}
		last_level = curr_level;
	}
}

void build_netflow(int num_verts) {
	adj_list.push_back(vii());
	adj_list.push_back(vii());
	for (int i = 0; i < num_verts; ++i) {
		int w = id_to_weight[i];
		if (w > 0)
			adj_list[source].push_back({ i, w });
		else if (w < 0)
			adj_list[i].push_back({ sink, -w });
	}

	res_flow.assign(adj_list.size() + 1, vll(adj_list.size() + 1, 0));
	for (int i = 0; i < adj_list.size(); ++i) {
		for (int j = 0; j < adj_list[i].size(); ++j) {
			int u = i;
			int v = adj_list[i][j].first;
			int w = adj_list[i][j].second;
			res_flow[u][v] = w;
		}
	}
}

ll augment_path(int v, ll min_edge, const vi& path) {
	if (v == source)
		return min_edge;
	else if (path[v] != -1) {
		ll flow = augment_path(path[v], min(min_edge, res_flow[path[v]][v]), path);
		res_flow[path[v]][v] -= flow;
		res_flow[v][path[v]] += flow;
		return flow;
	}
	else
		return 0;
}

ll get_max_flow() {
	ll max_flow = 0;
	while (true) {
		ll curr_flow = 0;
		vi dist(adj_list.size(), INF);
		dist[source] = 0;
		queue < int > q;
		q.push(source);
		vi path(adj_list.size(), -1);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			if (u == sink)
				break;
			for (int v = 0; v < adj_list.size(); ++v) {
				if (res_flow[u][v] > 0 && dist[v] == INF) {
					dist[v] = dist[u] + 1;
					q.push(v);
					path[v] = u;
				}
			}
		}
		curr_flow = augment_path(sink, INF, path);
		if (curr_flow == 0)
			break;
		max_flow += curr_flow;
	}
	return max_flow;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N;
	cin >> N;
	int curr_id = 0;
	int num_verts = get_num_verts(N);
	adj_list.assign(num_verts, vii());
	id_to_weight.resize(num_verts);

	build_graph(N, curr_id);
	source = curr_id;
	sink = curr_id + 1;
	build_netflow(num_verts);

	ll sum_of_positive_weights = 0;
	for (int i = 0; i < num_verts;++i) {
		if (id_to_weight[i]>0)
			sum_of_positive_weights += id_to_weight[i];
	}

	ll max_flow = get_max_flow();

	cout << sum_of_positive_weights - max_flow << '\n';

	return 0;
}
