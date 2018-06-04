
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

vector<vi> adjlist;
vb visited;
vii end_times;
vi topo_sort;

void DFS(int u) {
	visited[u] = true;
	for (int i = 0; i < adjlist[u].size(); ++i) {
		int v = adjlist[u][i];
		if (!visited[v]) {
			DFS(v);
		}
	}
	topo_sort.push_back(u);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N,K,W;
	cin>>N>>K;
	adjlist.assign(N,vi());
	end_times.resize(N);
	visited.assign(N, false);

	for (int u = 0; u < K; ++u) {
		int v;
		cin>>W;
		for (int i = 0; i < W; ++i) {
			cin >> v;
			adjlist[u].push_back(v-1);
		}
	}

	for (int u = 0; u < N; ++u) {
		if (!visited[u]) {
			DFS(u);
		}
	}

	vi parent(N, 0);
	for (int i = 0; i < topo_sort.size()-1; ++i) {
		int u = topo_sort[i];
		int v = topo_sort[i+1];
		parent[u] = v+1;
	}
	for (int i = 0; i < N; ++i)
		cout<<parent[i]<<'\n';

  return 0;
}
