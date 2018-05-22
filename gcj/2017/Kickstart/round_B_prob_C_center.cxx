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
const int MAXN = 1e5 + 2;

const double EPS = 1e-12;

struct P {
	P() : x(0), y(0) {}
	P(long double x, long double y) : x(x), y(y) {}
	long double x, y;
};

vector<P> points, wpoints;
vd weights;



ld get_res(ld Mx, ld My) {
	ld res = 0;
	for (int i = 0; i < points.size(); ++i) {
		res += max(fabs(Mx - points[i].x),
			       fabs(My - points[i].y)) * weights[i];
	}
	return res;
}

ld get_resx(ld Mx) {
	ld Ly = -1000, Ry = 1000;
	while (abs(Ry - Ly) > EPS) {
		ld Mly = Ly + (Ry - Ly) / 3;
		ld Mry = Ry - (Ry - Ly) / 3;
		if (get_res(Mx, Mly) > get_res(Mx, Mry))
			Ly = Mly;
		else
			Ry = Mry;
	}
	ld My = (Ry + Ly) / 2;
	return get_res(Mx, My);
}
int main()  {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("b.in");
	ofstream fout("b.out");
	int T;
	fin >> T;
	for (int t = 0; t < T; ++t) {
		int N;
		fin >> N;
		points.resize(N), wpoints.resize(N);
		weights.resize(N);
		long double x, y, w;
		long double W = 0.0;
		for (int i = 0; i < N; ++i) {
			fin >> x >> y >> w;
			points[i] = P(x, y);
			x *= w, y *= w;
			wpoints[i] = P(x, y);
			weights[i] = w;
			W += w;
		}
		ld min_res = INF_LL;
		ld Lx = -1000, Rx = 1000;
		while (abs(Rx - Lx) > EPS) {
			ld Mlx = Lx + (Rx - Lx) / 3;
			ld Mrx = Rx - (Rx - Lx) / 3;
			if (get_resx(Mlx) > get_resx(Mrx))
				Lx = Mlx;
			else
				Rx = Mrx;
		}

		ld Mx = (Lx + Rx) / 2;
		ld res = get_resx(Mx);
		fout << "Case #" << t + 1 << ": " << fixed << setprecision(15) << res << '\n';
	}
	return 0;
}