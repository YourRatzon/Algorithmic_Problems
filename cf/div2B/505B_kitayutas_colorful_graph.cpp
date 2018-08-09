
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

vector<vector<vi>> adjlist;
vector<vb> visited;
bool can_reach(int u, int t, int c) {
	visited[c][u]=true;
	for (int i = 0; i < adjlist[c][u].size(); ++i) {
		int v = adjlist[c][u][i];
		if (v == t)
			return true;
		if (!visited[c][v]) {
			bool res = can_reach(v,t,c);
			if (res)
				return true;
		}
	}
	return false;
}
int N, M;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin>>N>>M;
	adjlist.assign(M+1, vector<vi>(N+1, vi()));
	int a,b,c;
	for (int i = 0; i < M; ++i) {
		cin>>a>>b>>c;
		adjlist[c][a].push_back(b);
		adjlist[c][b].push_back(a);
	}
	int Q;
	cin>>Q;
	int u,v;
	for (int q = 0; q<Q; ++q) {
		cin>>u>>v;
		int res = 0;
		visited.assign(M+1, vb(N+1, false));
		for (int i = 1; i <= M; ++i) {
			res += int(can_reach(u,v,i));
		}
		cout<<res<<'\n';
	}
  return 0;
}
