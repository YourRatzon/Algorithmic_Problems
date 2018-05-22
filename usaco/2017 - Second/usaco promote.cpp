//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
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
const int MAX_N = 1e6 + 5;

using namespace __gnu_pbds;
typedef tree<
	int,
	null_type,
	less<int>,
	rb_tree_tag,
	tree_order_statistics_node_update>
	ordered_set;

vector<vi> adjlist;
vi res;
vi P;
ordered_set X;
void solve(int u) {
	X.insert(P[u]);
	int bigger = X.size() - X.order_of_key(P[u]) - 1;
	res[u] = -bigger;
	for (int i = 0; i < adjlist[u].size(); ++i) {
		int v = adjlist[u][i];
		solve(v);
	}
	bigger = X.size() - X.order_of_key(P[u]) - 1;
	res[u] += bigger;

}
int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	ifstream fin("promote.in");
	ofstream fout("promote.out");
	int N;
	fin >> N;
	P.assign(N + 2, 0);
	res.assign(N + 2, 0);
	adjlist.assign(N + 2, vi());
	for (int i = 1; i <= N; ++i)
		fin >> P[i];
	int u = 0;
	for (int v = 2; v <= N; ++v) {
		fin >> u;
		adjlist[u].push_back(v);
	}
	solve(1);
	for (int i = 1; i <= N; ++i)
		fout << res[i] << '\n';
	return 0;
}