//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

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

double EPS = 1e-9;
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

struct Op {
	int l, r;
	ll d;
};
vll nums;
vll op_counts;
vector<ll> num_stree;
vector<ll> op_stree;
vector<Op> ops;

void build_stree(vll& stree, vll& A, int u, int tl, int tr) {
	if (tl == tr) { // leaf
		stree[u] = A[tl];
	}
	else {
		int tm = (tr + tl) / 2;
		build_stree(stree,A,2 * u, tl, tm);
		build_stree(stree,A,2 * u + 1, tm+1, tr);
	}
}

void update(vll& stree, ll to_add, int u, int tl, int tr, int l, int r) {
	if (l > r)
		return;
	if (tl == l&&tr == r)
		stree[u] += to_add;
	else {
		int tm = (tr + tl) / 2;
		update(stree, to_add, 2 * u, tl, tm, l, min(tm, r));
		update(stree, to_add, 2 * u+1, tm+1, tr,max(tm+1, l), r);
	}
}

ll get(vll& stree, int u, int pos, int tl, int tr) {
	if (tl == tr)
		return stree[u];
	int tm = (tl + tr) / 2;
	if (pos <= tm)
		return stree[u] + get(stree, u * 2, pos, tl, tm);
	else
		return stree[u] + get(stree, u * 2 + 1, pos, tm + 1, tr);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N, M, K;
	int start = 1;
	cin >> N >> M >> K;
	nums.resize(N+1);
	num_stree.resize(4 * (N+1));
	for (int i = 1; i <= N; ++i)
		cin >> nums[i];
	build_stree(num_stree, nums, start, 1, N);
	int L, R;
	ll D;
	ops.resize(M+1);
	op_counts.assign(M + 1, 0);
	op_stree.resize(4 * (M+1));
	for (int i = 1; i <= M; ++i) {
		cin >> L >> R >> D;
		ops[i] = { L, R, D };
	}
	build_stree(op_stree, op_counts, start, 1, M);
	ll to_add = 1;
	for (int i = 0; i < K; ++i) {
		cin >> L >> R;
		update(op_stree, to_add, start, 1, M, L, R);
	}

	for (int i = 1; i <= M; ++i) {
		ll op_count = get(op_stree, 1, i, 1, M);
		update(num_stree, op_count*ops[i].d, start, 1, N, ops[i].l, ops[i].r);
	}
	for (int i = 1; i <= N; ++i) {
		cout << get(num_stree, 1, i, 1, N) << '\n';
	}
	return 0;
}
