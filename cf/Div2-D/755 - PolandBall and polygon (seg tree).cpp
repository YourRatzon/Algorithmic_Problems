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
const int MAX_N = 1e6 + 5;

ll n, k;
ll t[4 * MAX_N];
void build(vll& a, ll v, ll tl, ll tr) {
	if (tl == tr)
		t[v] = a[tl];
	else {
		ll tm = (tl + tr) / 2;
		build(a, v * 2, tl, tm);
		build(a, v * 2 + 1, tm + 1, tr);
		t[v] = t[v * 2] + t[v * 2 + 1];
	}
}
ll sum(ll v, ll tl, ll tr, ll l, ll r) {
	if (l > r)
		return 0;
	if (l == tl&&r == tr)
		return t[v];
	ll tm = tl + (tr - tl) / 2;
	return sum(v * 2, tl, tm, l, min(r, tm)) +
		sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

void update(ll v, ll tl, ll tr, ll pos, ll new_val) {
	if (tl == tr)
		t[v] = new_val;
	else {
		ll tm = (tl + tr) / 2;
		if (pos <= tm)
			update(v * 2, tl, tm, pos, new_val);
		else
			update(v * 2 + 1, tm + 1, tr, pos, new_val);
		t[v] = t[v * 2] + t[v * 2 + 1];
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	k = min(k, n - k);
	vll A(n + 1, 0);
	build(A, 1, 0, n - 1);
	ll curr = 1;
	ll res = 1;
	for (int i = 0; i < n; ++i) {
		A[curr]++;
		update(1, 0, n - 1, curr, A[curr]);
		ll lines = 0;
		
		int L = curr + 1;
		int M = min(curr + k - 1, n - 1);
		int R = (curr + k - 1) % n;
			lines += sum(1, 0, n - 1, L,M);
		if (R<L)
			lines += sum(1, 0, n - 1, 0, R);

		res += lines + 1;
		curr = (curr + k) % n;
		A[curr]++;
		update(1, 0, n - 1, curr, A[curr]);
		cout << res << ' ';
	}
	cout << '\n';

	return 0;
}