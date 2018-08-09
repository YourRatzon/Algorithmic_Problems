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

vi sched;
vector<vi> memo;
int n;

void set_last_day(int yest) {
	if (sched[n-1] == 0)
		memo[yest][n-1] = 1;

	else if (sched[n-1] != 0 && yest == 0) // rested yesterday
		memo[yest][n-1] = 0;
	else if (sched[n-1] != 0 && yest == 1) {// contest yesteday
		if (sched[n-1] == 1) // gym closed
			memo[yest][n-1] = 1;
		else
			memo[yest][n-1] = 0;
	}
	else if (sched[n-1] != 0 && yest == 2) { // gym yesterday
		if (sched[n-1] == 2) // no contest
			memo[yest][n-1] = 1;
		else
			memo[yest][n-1] = 0;
	}
}

void solve(int yest, int today) {
	if (memo[yest][today] != -1)
		return;

	if (today == n-1) {
		set_last_day(yest);
		return;
	}

	solve(0,today+1);
	memo[yest][today] = 1 + memo[0][today+1]; // if all closed (sched[today]==0)

	if (sched[today] == 1 && yest != 1) { // gym closed, contest open, yest no contest
		solve(1,today+1);
		memo[yest][today] = min(memo[1][today+1], memo[yest][today]);
	}
	else if (sched[today] == 2 && yest != 2) { //gym open, contest closed, yet no gym
		solve(2,today+1);
		memo[yest][today] = min(memo[2][today+1], memo[yest][today]);
	}
	else if (sched[today] == 3) { // all open
		if (yest != 1) {
			solve(1,today+1);
			memo[yest][today] = min(memo[1][today+1], memo[yest][today]);
		}
		if (yest != 2) {
			solve(2,today+1);
			memo[yest][today] = min(memo[2][today+1], memo[yest][today]);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	sched.resize(n);
	for (int i = 0; i < n; ++i) {
			cin>>sched[i];
	}
	memo.assign(3,vi(n, -1));
	solve(0, 0);
	cout<<memo[0][0]<<'\n';
  return 0;
}
