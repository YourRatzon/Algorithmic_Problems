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
# define M_PI		3.14159265358979323846
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


# define M_PI		3.14159265358979323846
const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 2 * 1e5 + 1;

vll vert_weights;
vector<vii> adj_list;
vll num_reach;
vll depths;
vi st;

void DFS(int u, ll curr_depth, int stack_idx) {
	st[stack_idx] = u;
	depths[stack_idx] = curr_depth;
	for (size_t i = 0; i< adj_list[u].size(); ++i) {
		ll v = adj_list[u][i].first;
		ll w = adj_list[u][i].second;

		ll min_depth = curr_depth + w - vert_weights[v];
		auto low = lower_bound(depths.begin(), depths.begin() + stack_idx+1, 
							   min_depth);
		num_reach[st[stack_idx]]++;
		int low_idx = (low - depths.begin());
		if (low_idx - 1 >= 0)
			num_reach[st[low_idx-1]]--;
		DFS(v, curr_depth + w, stack_idx+1);
		num_reach[st[stack_idx]] += num_reach[st[stack_idx + 1]];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ll n;
	cin >> n;
	vert_weights.resize(n + 1);
	adj_list.assign(n + 1, vii());
	num_reach.assign(n + 1, 0);
	st.assign(n + 1, 0);
	depths.assign(n + 1, 0);
	for (int i = 1; i <= n; ++i)
		cin >> vert_weights[i];

	ll p, w;
	for (int i = 2; i <= n; ++i) {
		cin >> p >> w;
		adj_list[p].push_back({ i, w });
	}
	DFS(1,0,0);
	for (int i = 1; i <= n; ++i)
		cout << num_reach[i] << ' ';
	cout << '\n';

	return 0;
}