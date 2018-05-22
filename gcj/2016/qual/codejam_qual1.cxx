

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

void update(ll curr, vector<bool>& seen, int& num_seen) {
	while (curr) {
		if (!seen[curr % 10]) {
			seen[curr % 10] = true;
			num_seen++;
		}
		curr /= 10;
	}
}

int main() {
	/*ios_base::sync_with_stdio(false);
	cin.tie(0);*/
	//start_timer();


	int T;
	ll N;
	ifstream fin("a.in");
	fin >> T;
	vector<bool> seen;
	ofstream fout("a.out");
	int num_seen = 0;
	for (int t = 0; t < T; ++t) {
		fin >> N;
		if (N == 0) {
			fout << "Case #" << t + 1 << ": INSOMNIA\n";
			continue;
		}

		seen.assign(10, false);
		num_seen = 0;
		ll mult = 1;
		ll curr;
		while (mult < 1e4 && num_seen < 10) {
			curr = mult*N;
			++mult;
			update(curr, seen, num_seen);
		}
		fout << "Case #" << t+1 << ": " << curr << '\n';
	}
	//print_timer();
	return 0;
}