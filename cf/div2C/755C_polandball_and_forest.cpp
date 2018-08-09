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

vi p;
vi set_rank;
int find_set(int u) {
	if (p[u] == u)
		return u;
	else
		return p[u] = find_set(p[u]);
}
void set_union(int u, int v) {
	u = find_set(u);
	v = find_set(v);
	if (u != v) {
		if (set_rank[u] < set_rank[v])
			swap(u, v);
		p[v] = u;
		if (set_rank[u] == set_rank[v])
			++set_rank[u];
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	p.resize(n+1);
	set_rank.assign(n + 1, 0);
	for (int i = 1; i <= n; ++i)
		p[i] = i;

	int v;
	for (int u = 1; u <= n; ++u) {
		cin >> v;
		set_union(u, v);
	}
	
	set<int> seen;
	for (int i = 1; i <= n; ++i) {
		seen.insert(find_set(i));
	}
	cout << seen.size() << '\n';

	return 0;
}