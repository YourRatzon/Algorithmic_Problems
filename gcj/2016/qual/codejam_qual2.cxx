

#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << __duration << '\n';
}
// END TIMER

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
//char _;

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

int main() {
	/*ios_base::sync_with_stdio(false);
	cin.tie(0);*/
	//start_timer();
	

	ifstream fin("b.in");
	ofstream fout("b.out");
	int T;
	fin >> T;
	string S;
	for (int t = 0; t < T; ++t) {
		fin >> S;
		int res = 0;
		while (true) {
			int idx = 0;
			if (S[idx] == '+') {
				while (idx < S.size() && S[idx] == '+')
					++idx;
				if (idx == S.size())
					break;
				++res;
				--idx;
				while (idx >= 0) {
					S[idx] = '-';
					--idx;
				}
			}
			else {
				while (idx < S.size() && S[idx] == '-')
					++idx;
				--idx;
				++res;
				while (idx >= 0) {
					S[idx] = '+';
					--idx;
				}
			}
		}
		fout << "Case #" << t + 1 << ": " << res << '\n';
	}

	fin.close();
	fout.close();
	//print_timer();
	return 0;
}