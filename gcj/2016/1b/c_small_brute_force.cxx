

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
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = ll(1e18);
const int MAX_N = 1e7;

vector<pair<string, string>> topics;

bool is_set(int num, int bit) {
	return (num &  (1 << bit));
}

int main() {
	ios_base::sync_with_stdio(false);
	//cin.tie(0);
	start_timer();

	ifstream fin("c.in");
	ofstream fout("c.out");
	int T,N;
	fin >> T;
	string A, B;
	for (int t = 0; t < T; ++t) {
		fin >> N;
		topics.resize(N);
		for (int i = 0; i < N; ++i) {
			fin >> A >> B;
			topics[i] = { A, B };
		}


		int max_fake = 0;
		for (int i = 1; i < int(pow(2, N)); ++i) {
			int curr_fake = 0;
			bool success = true;
			set<string> first_real, second_real;

			for (int bit = 0; bit < N; ++bit) {
				if (!is_set(i, bit)) {
					first_real.insert(topics[bit].first);
					second_real.insert(topics[bit].second);
				}
			}
			for (int bit = 0; bit < N; ++bit) {
				if (is_set(i, bit)) {
					if (first_real.count(topics[bit].first) == 0 ||
						second_real.count(topics[bit].second) == 0) {
						success = false;
						break;
					}
					curr_fake++;
				}
			}
			if (success)
				max_fake = max(max_fake, curr_fake);
		}
		fout << "Case #" << t+1<<": " << max_fake << '\n';
	}

	print_timer();
	return 0;
}
