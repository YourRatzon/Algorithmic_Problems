
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

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1e6 + 5;

vector<vector<char>> grid;
vi xmoves = {-1,0,1,0};
vi ymoves = {0,-1,0,1};
int R,C;

bool legal_move(int x,int y) {
	return x>=0&&x<R&&y>=0&& y<C;
}

bool find_sheep(int x, int y) {
	for (int i = 0; i < xmoves.size(); ++i) {
		int newx = x+xmoves[i];
		int newy = y+ymoves[i];
		if (legal_move(newx, newy) && grid[newx][newy] == 'S')
				return true;
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin>>R>>C;
	grid.assign(R, vector<char>(C));
	vii wolves;
	for (int i = 0; i<R; ++i) {
		for (int j = 0; j < C; ++j) {
			cin>>grid[i][j];
			if (grid[i][j] == 'W')
				wolves.push_back({i,j});
			else if (grid[i][j] == '.')
				grid[i][j] = 'D';
		}
	}

	for (int i = 0; i < wolves.size(); ++i) {
		ii wolf = wolves[i];
		bool found_sheep = find_sheep(wolf.first, wolf.second);
		if (found_sheep) {
				cout <<"No\n";
				return 0;
		}
	}

	cout <<"Yes\n";
	for (int i = 0; i<R; ++i) {
		for (int j = 0; j < C; ++j) {
			cout<<grid[i][j];
		}
		cout<<'\n';
	}

  return 0;
}
