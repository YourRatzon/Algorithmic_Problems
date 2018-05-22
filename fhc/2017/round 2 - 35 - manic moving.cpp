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


const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1000 + 5;

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	
	ifstream fin("c.in");
	ofstream fout("c.out");
	
	int T;
	fin >> T;
	for (int t = 1; t <= T; ++t) {
		cout << "Case #" << t << ": ";

		fout << "Case #" << t << ": ";
		int N, M, K;
		fin >> N >> M >> K;
		vector<vll> adjmatrix(N+1, vll(N+1, INF));
		for (int i = 0; i <= N; ++i)
			adjmatrix[i][i] = 0;

		ll u, v, w;
		for (int i = 0; i < M; ++i) {
			fin >> u >> v >> w;
			adjmatrix[u][v] = min(adjmatrix[u][v], w);
			adjmatrix[v][u] = adjmatrix[u][v];
		}
		for (int k = 1; k <= N; ++k) {
			for (int i = 1; i <= N; ++i) {
				for (int j = i + 1; j <= N; ++j) {
					adjmatrix[i][j] =
						min(adjmatrix[i][j],
						adjmatrix[i][k] + adjmatrix[k][j]);
					adjmatrix[j][i] = adjmatrix[i][j];
				}
			}
		}
		vii trips(K);
		for (int i = 0; i < K; ++i) {
			fin >> u >> v;
			trips[i] = { u, v };
		}

		if (K == 1) {
			u = trips[0].first;
			v = trips[0].second;
			ll res = adjmatrix[1][u] + adjmatrix[u][v];
			if (res < INF)
				fout << res << '\n';
			else
				fout << -1 << '\n';
			continue;
		}

		vector<vii> adjlist(K*4+5, vii());
		int curr_idx = 1;
		int prev_v = 1;
		vi idx_to_u(1,1);
		for (int i = 0; i < K; ++i) {
			u = trips[i].first;
			v = trips[i].second;
			idx_to_u.push_back(u);
			idx_to_u.push_back(v);
			adjlist[curr_idx-1].push_back({ curr_idx, adjmatrix[prev_v][u] });
			adjlist[curr_idx].push_back({ curr_idx + 1, adjmatrix[u][v] });
			curr_idx += 2;
			prev_v = v;
		}
		int sink_idx = curr_idx-1;
		int sink_v = v;
		int u1 = trips[0].first;
		int u2 = trips[1].first;
		adjlist[1].push_back({ curr_idx, adjmatrix[u1][u2] });
		prev_v = u2;
		curr_idx++;
		idx_to_u.push_back(u2);
		for (int i = 1; i < K; ++i) {
			int v1 = trips[i-1].second;
			idx_to_u.push_back(v1);
			adjlist[curr_idx-1].push_back({ curr_idx, adjmatrix[prev_v][v1] });
			
			if (i < K - 1){
				int	u2 = trips[i + 1].first;
				idx_to_u.push_back(u2);
				adjlist[curr_idx].push_back({ curr_idx + 1, adjmatrix[v1][u2] });
				prev_v = u2;
			}
			else {
				adjlist[curr_idx].push_back({ sink_idx,adjmatrix[v1][sink_v] });
			}
			curr_idx += 2;
		}
		for (int i = 3; i < sink_idx-1; i += 2) {
			int u = idx_to_u[i];
			int v = idx_to_u[sink_idx + i];
			adjlist[i].push_back({ sink_idx + i, adjmatrix[u][v] });
			u = idx_to_u[sink_idx + i - 1];
			v = idx_to_u[i + 1];
			adjlist[sink_idx+i-1].push_back({ i+1, adjmatrix[u][v] });
		}
		
		int V = adjlist.size();
		vll dist(V, INF);
		dist[0] = 0;
		priority_queue < llll, vllll, greater<llll>> pq;
		pq.push({ 0, 0 });
		int it = 1;
		while (!pq.empty()) {
			llll pp = pq.top();
			pq.pop();
			ll d = pp.first;
			ll u = pp.second;
			if (d>dist[u]){
				continue;
			}
			for (int i = 0; i < adjlist[u].size(); ++i) {
				ll v = adjlist[u][i].first;
				ll w = adjlist[u][i].second;
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					pq.push({ dist[v], v });
				}
			}
		}
		ll res;
		if (dist[sink_idx] < INF)
			res = dist[sink_idx];
		else
			res = -1;
		cout << res << '\n';
		fout << res << '\n';
	}
	return 0;
}