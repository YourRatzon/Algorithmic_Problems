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


const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1000 + 5;


int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	
	ifstream fin("a.in");
	ofstream fout("a.out");

	int T;
	fin >> T;
	double p, _x, _y;
	for (int t = 1; t <= T; ++t) {
		fin >> p >> _x >> _y;
		fout << "Case #" << t << ": ";
		double X = -1 + _x / 50.0;
		double Y = -1 + _y / 50.0;
		if (eq_(p, 0)) {
			fout << "white\n";
			continue;
		}
		if (eq_(X, 0) && eq_(Y, 0)) {
			fout << "black\n";
			continue;
		}
		double angle = atan2(Y, X) * 180 / M_PI;
		double X2, Y2;
		if (X == 0) {
			X2 = 0;
			Y2 = (Y > 0 ? 1 : -1);
		}
		else if (Y == 0) {
			X2 = (X > 0 ? 1 : -1);
			Y2 = 0;

		}
		else {
			double xDy = X / Y;
			Y2 = -sqrt(1 / (1 + xDy*xDy));
			X2 = Y2*xDy;
		}
		angle = 90 - angle;
		if (angle < 0)
			angle += 360;
		if (angle <= p/100.0 * 360 &&
			fabs(X) <= fabs(X2) && fabs(Y) <= fabs(Y2)) {
			fout << "black\n";
		}
		else
			fout << "white\n";
	}
	return 0;
}