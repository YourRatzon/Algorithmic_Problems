//#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

/*
ID: jamerz1
PROG: picture
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

double EPS = 1e-16;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
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


const int MAXX = 7000 ;
const int MAXY = 7000 ;

const int MAXN = 21000;
const int NORM = 10000+2;

bitset<MAXY> grid[MAXX];
bitset<MAXY> visited[MAXX];
struct rect {
	rect() : x1(0), y1(0), x2(0), y2(0) {}
	rect(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
	int x1, y1, x2, y2;
};
bool rectsort(rect lhs, rect rhs){
	return lhs.x1 < rhs.x1;
}

bool legal(int i, int j){
	return i >= 0 && i < MAXX&&j >= 0 && j < MAXY;
}
int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//start_timer();
	ifstream fin("picture.in");
	ofstream fout("picture.out");
	int R;
	int x1, y1, x2, y2;
	fin >> R;
	int rratio = MAXN / MAXX;
	int cratio = MAXN / MAXY;
	vector<rect> rects(R);
	for (int i = 0; i < R; ++i) {
		fin >> x1 >> y1 >> x2 >> y2;
		x1 += NORM, y1 += NORM, x2 += NORM, y2 += NORM;
		rects[i] = rect(x1, y1, x2, y2);
	}

	ll res = 0;
	for (int r = 1; r <= rratio; ++r) {
		for (int c = 1; c <= cratio; ++c) {
			for (int i = 0; i < MAXX; ++i) {
				visited[i].reset();
				grid[i].set();
			}

			int xmin = MAXX*(r - 1);
			int xmax = MAXX*r;
			int ymin = MAXY*(c - 1);
			int ymax = MAXY*c;

			int d = 0;
			for (int i = 0; i < rects.size(); ++i) {
				for (int x = max(xmin, rects[i].x1);
					x < min(xmax, rects[i].x2); ++x) {
					for (int y = max(ymin, rects[i].y1);
						y < min(ymax, rects[i].y2); ++y) {
						grid[x - MAXX*(r - 1)][y - MAXY*(c - 1)] = false;
						++d;
					}
				}
			}
			for (int i = 0; i < rects.size(); ++i) {
				for (int x = max(xmin, rects[i].x1);
					x < min(xmax, rects[i].x2); ++x) {
					for (int y = max(ymin, rects[i].y1);
						y < min(ymax, rects[i].y2); ++y) {

						int nx = x - MAXX*(r - 1);
						int ny = y - MAXY*(c - 1);
						if (grid[nx][ny] || visited[nx][ny])
							continue;

						visited[nx][ny] = true;

						if (legal(nx - 1, ny))
							res += grid[nx - 1][ny];
						if (legal(nx + 1, ny))
							res += grid[nx + 1][ny];
						if (legal(nx, ny - 1))
							res += grid[nx][ny - 1];
						if (legal(nx, ny + 1))
							res += grid[nx][ny + 1];
					}
				}
			}
		}
	}
	fout << res << '\n';
	//print_timer();
	return 0;
}