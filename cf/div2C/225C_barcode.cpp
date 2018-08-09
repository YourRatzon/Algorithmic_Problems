
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

	int N,M,X,Y;
	cin>>N>>M>>X>>Y;
	vector<vc> grid(N,vc(M));
	vi wcol(M,0), bcol(M,0);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin>>grid[i][j];
			if (grid[i][j] == '.')
				bcol[j]++;
			else
				wcol[j]++;
		}
	}

	vector<vi> wseg(M,vi(M,0));
	vector<vi> bseg(M,vi(M,0));
	for (int i = 0; i < M; ++i) {
		wseg[i][i] = wcol[i];
		bseg[i][i] = bcol[i];
	}

	for (int i = 0; i < M; ++i) {
		for (int j = i+1; j < M; ++j) {
			wseg[i][j] = wseg[i][j-1] + wcol[j];
			bseg[i][j] = bseg[i][j-1] + bcol[j];
		}
	}

	vector<vi> DP(M,vi(2,INF));

	for (int i = 0; i < M; ++i) {
		if (i+1 >= X && i+1 <= Y) {
			DP[i][0] = wseg[0][i];
			DP[i][1] = bseg[0][i];
		}
		for (int j = 0; j < i; ++j) {
			int seg_len = i - j;
			if (seg_len >= X && seg_len <= Y) {
				DP[i][0] = min(DP[i][0], DP[j][1] + wseg[j+1][i]);
				DP[i][1] = min(DP[i][1], DP[j][0] + bseg[j+1][i]);
			}
		}
	}

	cout << min(DP[M-1][0],DP[M-1][1])<<'\n';

  return 0;
}
