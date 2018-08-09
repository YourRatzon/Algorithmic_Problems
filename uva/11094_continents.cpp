
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

vector<vc> grid;
vector<vb> visited;
int R,C,x,y;
vi rmoves = {-1,0,0,1};
vi cmoves = {0,-1,1,0};
char land;

bool legal(int r, int c) {
	return r>=0 && r < R && c>= 0 && c < C;
}

int DFS(int r, int c) {
	visited[r][c] = true;
	int res = 1;
	for (int i = 0; i < rmoves.size(); ++i) {
		int newr = r+rmoves[i];
		int newc = c+cmoves[i];
		if (newc < 0)
			newc += C;
		newc %= C;

		if (legal(newr,newc) && !visited[newr][newc] && grid[newr][newc] == grid[x][y])
			res += DFS(newr,newc);
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	while(cin>>R>>C) {
		grid.assign(R,vc(C));
		visited.assign(R,vb(C,false));
		for (int r = 0; r < R; ++r)
			for (int c = 0; c < C; ++c)
				cin>>grid[r][c];
		cin>>x>>y;

		DFS(x,y);
		int res = 0;
		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
					if (!visited[r][c] && grid[r][c] == grid[x][y]) {
						res = max(res,DFS(r,c));
					}
			}
		}
		cout<<res<<'\n';
	}

  return 0;
}
