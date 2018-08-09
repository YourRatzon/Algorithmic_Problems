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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int S, x1, x2;
	cin >> S >> x1 >> x2;
	int t1, t2;
	cin >> t1 >> t2;
	int p, d;
	cin >> p >> d;

	int distTI;
	if (d == 1 && x1 < x2) {
		if (p <= x1)
			distTI = x1 - p;
		else
			distTI = (S - p) + S + x1;
	}
	else if (d == -1 && x1 > x2) {
		if (p >= x1)
			distTI = p - x1;
		else
			distTI = p + S + (S - x1);
	}
	else if (d == 1 && x1 > x2)
		distTI = (S - p) + (S - x1);
	else // d==-1 && x1<x2
		distTI = p + x1;

	int Istart = 2 * S;
	int D = abs(x2 - x1);
	int end = 2 * S + D;
	int Tstart = Istart - distTI;

	double Vi = 1 / double(t2);
	double Vt = 1 / double(t1);
	double slowT = D / Vi;
	double meetT = (Istart - Tstart) / (Vt - Vi);
	double res;
	if (meetT >= 0 && meetT < slowT)
		res = meetT + (end - (Istart + Vi*meetT)) / Vt;
	else
		res = slowT;
	cout << int(round(res)) << '\n';
	return 0;
}