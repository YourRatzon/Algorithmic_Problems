//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

//#define F first
//#define S second

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
# define M_PI		3.14159265358979323846
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


# define M_PI		3.14159265358979323846
const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1000 + 5;

struct pt {
	pt() : x(0), y(0), id(0) {}
	pt(int _x, int _y, int _id) : x(_x), y(_y), id(_id) {}
	int x, y, id;
};

unordered_map < int, vi> x_pts;
unordered_map < int, vi> y_pts;
vector<pt> pts_x, pts_y;
bool comp_x(const pt& a, const pt& b)
{
	return a.x < b.x;
}
bool comp_y(const pt& a, const pt& b)
{
	return a.y< b.y;
}
vector<pt> pts;
queue<pt> q;
vll dist;
int solve1(ifstream& fin, ofstream& fout) {
	int N, xl, yl, xb, yb;
	fin >> N >> xl >> yl >> xb >> yb;
	const int BARN_ID = N + 1;
	int x, y;
	pts.resize(N + 2);
	pts[0] = { xl, yl, 0 };
	for (int i = 1; i <= N; ++i) {
		fin >> x >> y;
		pts[i] = { x, y, i };
		x_pts[x].push_back(i);
		y_pts[y].push_back(i);
	}
	pts[N + 1] = { xb, yb, N + 1 };
	x_pts[xb].push_back(N + 1);
	y_pts[yb].push_back(N + 1);

	dist.assign(N + 2, INF_LL);
	dist[0] = 0; // 0 is barn
	q.push(pts[0]);
	while (!q.empty()) {
		pt u = q.front();
		q.pop();
		for (int vid : x_pts[u.x]) {
			if (dist[vid] == INF_LL) {
				dist[vid] = dist[u.id] + 1;
				if (vid == BARN_ID) {
					fout << dist[u.id] << '\n';
					return 0;
				}
				q.push(pts[vid]);
			}
		}
		for (int vid : y_pts[u.y]) {
			if (dist[vid] == INF_LL) {
				dist[vid] = dist[u.id] + 1;
				if (vid == BARN_ID) {
					fout << dist[u.id] << '\n';
					return 0;
				}
				q.push(pts[vid]);
			}
		}
	}
}
int solve2(ifstream& fin, ofstream& fout) {
	int N, xl, yl, xb, yb;
	fin >> N >> xl >> yl >> xb >> yb;
	const int BARN_ID = N + 1;
	int x, y;
	pts.resize(N + 2), pts_x.resize(N + 2), pts_y.resize(N + 2);
	pts[0] = { xl, yl, 0 };
	for (int i = 1; i <= N; ++i) {
		fin >> x >> y;
		pts[i] = { x, y, i };
		pts_x[i] = pts[i];
		pts_y[i] = pts[i];
	}
	pts[N + 1] = { xb, yb, N + 1 };
	pts_x[N + 1] = pts[N + 1];
	pts_y[N + 1] = pts[N + 1];

	sort(pts_x.begin(), pts_x.end(), comp_x);
	sort(pts_y.begin(), pts_y.end(), comp_y);

	vll dist(N + 2, INF_LL);
	dist[0] = 0; // 0 is barn
	queue<pt> q;
	q.push(pts[0]);
	while (!q.empty()) {
		pt u = q.front();
		q.pop();
		for (auto it = lower_bound(pts_x.begin(), pts_x.end(), u, comp_x);
			it != pts_x.end(); ++it) {
			pt v = *it;
			if (v.x != u.x)
				break;

			if (dist[v.id] == INF_LL) {
				dist[v.id] = dist[u.id] + 1;
				if (v.id == BARN_ID) {
					fout << dist[u.id] << '\n';
					return 0;
				}
				q.push(v);
			}
		}
		for (auto it = lower_bound(pts_y.begin(), pts_y.end(), u, comp_y);
			it != pts_y.end(); ++it) {
			pt v = *it;
			if (v.y != u.y)
				break;

			if (dist[v.id] == INF_LL) {
				dist[v.id] = dist[u.id] + 1;
				if (v.id == BARN_ID) {
					fout << dist[u.id] << '\n';
					return 0;
				}
				q.push(v);
			}
		}
	}


	return 0;
}
int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("lasers.in");
	ofstream fout("lasers.out");

	srand(time(NULL));
	int seed = rand() % 2;
	if (seed)
		solve1(fin,fout);
	else
		solve2(fin,fout);
	return 0;
}