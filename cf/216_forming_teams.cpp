
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

int N,M;
vector<vi> adjlist;
vb visited;

bool is_odd_cycle(int u, int startu, int path_len) {
	visited[u] = true;
	for (int i = 0; i < adjlist[u].size(); ++i) {
		int v = adjlist[u][i];
		if (!visited[v]) {
			return is_odd_cycle(v, startu, path_len+1);
		}
		else if (path_len > 2 && v == startu) {
				return ((path_len % 2) == 1);
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin>>N>>M;
	adjlist.assign(N+1, vi());
	visited.assign(N+1, false);
	int u,v;
	for (int i = 0; i < M; ++i) {
		cin>>u>>v;
		adjlist[u].push_back(v);
		adjlist[v].push_back(u);
	}

	int res = 0;
	for (int u = 1; u <= N; ++u) {
		if (!visited[u])
			res += int(is_odd_cycle(u, u, 1));
	}

	if ((N-res)%2 == 1)
		res++;
	cout<<res<<'\n';
  return 0;
}
