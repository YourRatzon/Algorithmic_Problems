#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

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

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer(string str = "") {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << str << " Duration (msec): " << __duration * 1000 << '\n';
}
// END TIMER

//PI
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
//char _;

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-9;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;

ll n_choose_2(ll n) {
	if (n < 2)
		return 0;
	return n*(n - 1) / 2;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ll N, K;
	cin >> N >> K;
	vll votes(N);
	vll inc_start(N,1), inc_end(N,1), dec_start(N,1), dec_end(N,1);
	for (int i = 0; i < N; ++i) 
		cin >> votes[i];

	for (int i = 1; i < N; ++i) {
		if (votes[i] >= votes[i - 1])
			inc_end[i] = inc_end[i - 1] + 1;
		if (votes[i] <= votes[i - 1])
			dec_end[i] = dec_end[i - 1] + 1;
	}
	for (int i = N - 2; i >= 0; --i) {
		if (votes[i] <= votes[i + 1])
			inc_start[i] = inc_start[i + 1] + 1;
		if (votes[i] >= votes[i + 1])
			dec_start[i] = dec_start[i + 1] + 1;
	}
	// count inc/dec sequences in window of size K ending at i
	vll inc_DP(N,0), dec_DP(N,0);
	ll inc_range_len = 1, dec_range_len = 1;
	ll num_inc_ranges = 0, num_dec_ranges = 0;
	for (int i = 1; i < K; ++i) {
		if (votes[i] >= votes[i - 1]) {
			++inc_range_len;
		}
		else {
			num_inc_ranges += n_choose_2(inc_range_len);
			inc_range_len = 1;
		}
		if (votes[i] <= votes[i - 1]) {
			++dec_range_len;
		}
		else {
			num_dec_ranges += n_choose_2(dec_range_len);
			dec_range_len = 1;
		}
	}
	num_inc_ranges += n_choose_2(inc_range_len);
	num_dec_ranges += n_choose_2(dec_range_len);
	inc_DP[K - 1] = num_inc_ranges;
	dec_DP[K - 1] = num_dec_ranges;
	for (int i = K; i < N; ++i) {
		inc_DP[i] = inc_DP[i - 1];
		if (votes[i] >= votes[i - 1])
			inc_DP[i] += min(K-1,inc_end[i]-1);
		if (votes[i - K + 1] >= votes[i - K])
			inc_DP[i] -= min(K-1,inc_start[i - K]-1);
		dec_DP[i] = dec_DP[i - 1];
		if (votes[i] <= votes[i - 1])
			dec_DP[i] += min(K-1,dec_end[i]-1);
		if (votes[i - K + 1] <= votes[i - K])
			dec_DP[i] -= min(K-1,dec_start[i - K]-1);
	}
	for (int i = K - 1; i < N; ++i) {
		cout << inc_DP[i] - dec_DP[i] << '\n';
	}
	return 0;
}
