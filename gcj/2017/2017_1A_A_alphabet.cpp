
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
	ifstream fin("a.in");
	ofstream fout("A.out");
	int T, R,C;
	fin>>T;
	vector<vector<char>> grid;
	for (int t = 0; t < T; ++t) {
		fin>>R>>C;
		grid.assign(R,vector<char>(C));
		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
				fin>>grid[r][c];
			}
		}

	for (int r = 0; r < R; ++r) {
		int c = 0;
		while (c < C && grid[r][c] == '?')
			++c;
		if (c==C)
			continue;
		char name = grid[r][c];
		for (int j = 0; j < c; ++j)
			grid[r][j] = name;

		while (c<C) {
			if (grid[r][c] == '?')
				grid[r][c] = name;
			else
				name = grid[r][c];
			++c;
		}

	}
	for (int c = 0; c < C; ++c) {
		int r = 0;
		while (r < R && grid[r][c] == '?')
			++r;
		char name = grid[r][c];
		for (int i = 0; i < r; ++i)
			grid[i][c] = name;
		while (r<R) {
			if (grid[r][c] == '?')
				grid[r][c] = name;
			else
				name = grid[r][c];
			++r;
		}
	}
	fout<<"Case #"<<t+1<<":\n";
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c)
			fout<<grid[r][c];
		fout<<'\n';
	}
	}
	return 0;
}




