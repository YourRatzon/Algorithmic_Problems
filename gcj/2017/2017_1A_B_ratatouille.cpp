
#define _USE_MATH_DEFINES

/*
ID: jamerz1
PROG: cardgame
LANG: C++11
*/


#include <bits/stdc++.h>

#define fi first
#define se second

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll,ll> llll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ull> vull;
typedef vector<ll> vll;
typedef vector<llll> vllll;

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

// TIMER
std::clock_t start;
double duration;
void start_timer() { start = std::clock(); }
void print_timer() {
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << '\n';
}
// END TIMER

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-10;
bool eq(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);

int main() {
//	ios_base::sync_with_stdio(false);
//	cin.tie(0);
	ifstream fin("B.in");
	ofstream fout("B.out");
	int T, N, P, tmp;
	vi R(N);
	fin>>T;
	for (int t = 0;t < T; ++t) {
		fin>>N>>P;
		vector<multiset<int>> grid(N,multiset<int>());
		for (int i = 0; i < N; ++i)
			fin>>R[i];
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < P; ++j) {
				fin>>tmp;
				grid[i].insert(tmp);
			}
		}

		set<int> kit_sizes;
		double r0 = R[0];
		for (int q : grid[0]) {
			double norm_q = 10 * q / r0;
			int max_x = int(floor(norm_q/9));
			int min_x = int(ceil(norm_q/11));
			for (int x = min_x; x<=max_x; ++x)
				kit_sizes.insert(x);
		}
		int res = 0;
		for (int x : kit_sizes) {
			vector<multiset<int>> cand_lists(N);
			int min_size = INF;
			for (int i = 0; i < N; ++i) {
				multiset<int> cands;
				for (int q : grid[i]) {
					double min_q = R[i] * x * 0.9;
					double max_q = R[i] * x * 1.1;
					if (q >= min_q && q <= max_q)
						cands.insert(q);
				}
				min_size = min(min_size, int(cands.size()));
				if (min_size == 0)
					break;
				cand_lists[i] = cands;
			}
			if (min_size > 0) {
				res += min_size;
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < min_size; ++j) {
						int to_erase = *cand_lists[i].begin();
						cand_lists[i].erase(cand_lists[i].begin());
						grid[i].erase(grid[i].find(to_erase));
					}

				}
			}
		}
		fout<<"Case #"<<t+1<<": "<<res<<'\n';
	}


	return 0;
}




