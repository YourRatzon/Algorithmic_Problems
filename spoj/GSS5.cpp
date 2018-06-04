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

struct Node {
	int all_sum, max_sum, max_pref, max_suff;
};
vi A;
vector<Node> stree;
Node combine(Node l, Node r) {
	Node node;
	node.all_sum = l.all_sum + r.all_sum;
	node.max_pref = max(l.max_pref, l.all_sum + r.max_pref);
	node.max_suff = max(r.max_suff, l.max_suff + r.all_sum);
	node.max_sum = max(max(l.max_sum, r.max_sum), l.max_suff+r.max_pref);
	return node;
}
void build_stree(int u, int tl, int tr) {
	if (tl == tr) { // leaf
		stree[u] = { A[tl], A[tl], A[tl], A[tl] };
	}
	else {
		int tm = (tr + tl) / 2;
		build_stree(2 * u, tl, tm);
		build_stree(2 * u + 1, tm+1, tr);
		stree[u] = combine(stree[u * 2], stree[u * 2 + 1]);
	}
}
Node query(int u, int tl, int tr, int l, int r) {
	if (l > r)
		return { 0, 0, 0, 0 };

	if (l == tl && tr == r)
		return stree[u];
	int tm = (tl + tr) / 2;
	if (r <= tm)
		return query(u * 2, tl, tm, l, r);
	else if (l > tm)
		return query(u * 2 + 1, tm + 1, tr, l, r);
	else {
		Node left = query(u * 2, tl, tm, l, tm);
		Node right = query(u * 2 + 1, tm + 1, tr, tm + 1, r);
		return combine(left, right);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T, N, M;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> N;
		A.resize(N);
		stree.resize(4 * N);
		for (int i = 0; i < N; ++i)
			cin >> A[i];
		build_stree(1, 0, N-1);
		cin >> M;
		int L1, R1, L2, R2;
		for (int i = 0; i < M; ++i) {
			cin >> L1 >> R1 >> L2 >> R2;
			--L1, --R1, --L2, --R2;
			if (R1 < L2) {
				Node left = query(1, 0, N - 1, L1, R1);
				Node mid = query(1, 0, N - 1, R1 + 1, L2 - 1);
				Node right = query(1, 0, N - 1, L2, R2);
				cout << left.max_suff + mid.all_sum + right.max_pref << '\n';
			}
			else {
				Node left1 = query(1, 0, N - 1, L1, L2-1);
				Node right1 = query(1, 0, N - 1, L2, R2);
				Node left2 = query(1, 0, N - 1, L1, R1);
				Node right2 = query(1, 0, N - 1, R1+1, R2);
				Node mid = query(1, 0, N - 1, L2, R1);
				int max_sum = max(mid.max_sum,
					max(left1.max_suff + right1.max_pref,
					left2.max_suff + right2.max_pref));

				cout << max_sum << '\n';
			}
		}
	}


	return 0;
}
