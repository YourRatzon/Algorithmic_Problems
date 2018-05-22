#include <bits/stdc++.h>

/*
ID: jamerz1
PROG: cbarn
LANG: C++11
*/

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << __duration << '\n';
}
// END TIMER

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-9;
bool eq(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = ll(1e18);

vi cows;
vi next_non_zero;
int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//start_timer();

	ifstream fin("cbarn.in");
	ofstream fout("cbarn.out");

	int N;
	fin >> N;
	cows.resize(N);
	next_non_zero.assign(N,-1);
	bool seen_non_one = false;
	for (int i = 0; i < N; ++i) {
		fin >> cows[i];
		if (cows[i] != 1)
			seen_non_one = true;
	}
	if (!seen_non_one)  {
		fout << 0 << '\n';
		return 0;
	}
	int next_idx = 0;
	int idx = 0;
	while (idx < N && cows[idx] == 0) {
		idx++;
	}
	while (next_non_zero[idx] == -1) {
		next_idx = (idx + 1) % N;
		while (cows[next_idx] == 0) {
			next_idx++;
			next_idx %= N;
		}
		next_non_zero[idx] = next_idx;
		idx = next_idx;
	}

	ll min_res = INF_LL;
	ll curr_res = 0;
	vi save_cows = cows;
	for (int i = 0; i < N; ++i) {
		cows = save_cows;
		curr_res = 0;
		// dont start here if next room is non zero
		if (cows[i]==0||cows[(i+1)%N]!=0)
			continue;
		int next = next_non_zero[i]-1;
		bool fail = false;
		for (int j = i, count = 0; count < N; j--,count++) {
			if (j < 0)
				j += N;
			while (next > j && cows[next] != 0) {
				next--;
				if (next < 0)
					next += N;
			}
			while (cows[j]&& next != j) {
				ll diff = next - j;
				if (diff < 0)
					diff += N;
				curr_res += diff*diff;
				next--;
				if (next < 0)
					next += N;
				cows[j]--;
			}
			if (cows[j] != 0)  {// fail!
				if (cows[j] > 1) {
					break;
				}
			}
		}
		for (int j = 0; j < N; ++j) {
			if (cows[j] > 1) {
				fail = true;
				break;
			}
		}
		if (!fail)
			min_res = min(min_res, curr_res);
	}
	if (min_res == INF_LL)
		min_res = 0;
	fout << min_res << '\n';
	fout.close();
	//print_timer();
	return 0;
}