
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;
	cin >> N;
	vi trees(N);
	vi heights(N);
	for (int i = 0; i < N; ++i) {
		cin>>trees[i]>>heights[i];
	}
	if (N <= 2) {
		cout<<N<<'\n';
		return 0;
	}
	vector<vi> DP(N,vi(3,0)); // 0 - no fell, 1 - left, 2 - right
	DP[N-1][2] = 1;
	if (trees[N-1] - heights[N-1] > trees[N-2])
		DP[N-1][1] = 1;

	for (int i = N-2; i > 0; --i) {
		DP[i][0] = max(DP[i+1][0],max(DP[i+1][1],DP[i+1][2]));
		if (trees[i] - heights[i] > trees[i-1])
			DP[i][1] = 1 + DP[i][0];
		if (trees[i] + heights[i] < trees[i+1] - heights[i+1])
			DP[i][2] = 1 + DP[i][0];
		else if (trees[i] + heights[i] < trees[i+1])
			DP[i][2] = 1 + max(DP[i+1][0], DP[i+1][2]);
	}
	int res = 1 + max(DP[1][0],max(DP[1][1],DP[1][2]));
	cout<<res<<'\n';
  return 0;
}
