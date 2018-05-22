//#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

/*
ID: jamerz1
PROG: hidden
LANG: C++11
*/

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

double EPS_ = 1e-16;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS_);
}

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
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
typedef vector<double> vd;

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;

const int MAXN = 102;

vector<vb> grid;
vector<vi> maxH;
vector<vector<vi>> DP;
vi h_size;
int N, M, K;

void set_maxH(int i, int j) {
	int h = 0;
	int r = i, c = j;
	while (c-h >=0 && c+h < M && r < N) {
		bool good = true;
		int row_count = 0;
		for (int j = c - h; j <= c + h; ++j) {
			if (!grid[r][j]) {
				good = false;
				break;
			}
			else
				++row_count;
		}
		if (!good)
			break;
		else {
			++h;
			++r;
		}
	}
	maxH[i][j] = h;
}
int main()  {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);

	start_timer();
	ifstream fin("c.in");
	ofstream fout("c.out");
	int T;
	fin >> T;
	for (int t = 0; t < T; ++t) {
		fin >> N>>M>>K;
		grid.assign(N, vb(M, false));
		maxH.assign(N, vi(M, 0));
		DP.assign(N, vector<vi>(M, vi(K + 1, 0)));
		char c;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				fin >> c;
				if (c == '#')
					grid[i][j] = true;
			}
		}

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				set_maxH(i, j);
			}
		}

		h_size.assign(N+1, 0);
		for (int i = 1; i <= N; ++i) {
			h_size[i] = h_size[i - 1] + (2*i-1);
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				DP[i][j][1] = h_size[maxH[i][j]];
			}
		}

		for (int i = N - 1; i >= 0; --i) {
			for (int j = 0; j < M; ++j) {
				for (int k = 2; k <= K; ++k) {
					int H = maxH[i][j];
					for (int h = 1; h <= H; ++h) {
						if (i + h >= N)
							break;
						for (int c = j - (h - 1); c <= j + (h - 1); ++c) {
							if (c < 0)
								continue;
							if (c >= M)
								break;
							if (DP[i + h][c][k - 1] > 0) {
								DP[i][j][k] = max(DP[i][j][k],
									DP[i + h][c][k - 1] + h_size[h]);
							}
						}
					}
				}
			}
		}

		int res = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				res = max(res, DP[i][j][K]);
			}
		}
		fout << "Case #" << t + 1 << ": " << fixed << setprecision(15) << res << '\n';
	}
	print_timer();
	return 0;
}