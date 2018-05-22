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

//#define F first
//#define S second

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef pair<int, int> ii;
typedef pair<double, double> dd;

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

const int MAX_G = 4;
vector<vd> G, TB, S, M;

void print_res(ld g, ld s, ld m) {
	cout << fixed<<setprecision(11)<<g << ' ' << s << ' ' << m << '\n';
}

void setup() {
	G.assign(5, vd(5, 0.0));
	TB.assign(8, vd(8, 0.0));
	S.assign(8, vd(8, 0.0));
	M.assign(3, vd(3, 0.0));
	for (int i = 0; i < 3; ++i) {
		G[i][4] = 0;
		G[4][i] = 1.0;
	}
	for (int i = 0; i < 6; ++i) {
		TB[i][7] = 0;
		TB[7][i] = 1.0;
	}
	for (int i = 0; i < 5; ++i) {
		S[i][6] = 0;
		S[i][7] = 0;
		S[6][i] = 1.0;
		S[7][i] = 1.0;
	}
	S[5][7] = 0;
	S[7][5] = 1;
	for (int i = 0; i < 3; ++i) {
		M[i][2] = 0;
		M[2][i] = 1;
	}
}

int main()  {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);

	ld p;
	while (cin >> p && p != -1) {
		setup();
		if (p == 1.0) {
			print_res(1, 1, 1);
			continue;
		}
		if (p == 0.0) {
			print_res(0, 0, 0);
			continue;
		}

		ld q = 1.0 - p;
		ld pduece = p*p / (1.0 - 2*p*q);
		G[3][3] = pduece;
		for (int dsum = 5; dsum >= 0; --dsum) {
			for (int i = max(0, dsum - 3); i <= dsum-(max(0,dsum-3)); ++i) {
				int j = dsum - i;
				G[i][j] = p*G[i + 1][j] + q*G[i][j + 1];
			}
		}
		ld pg = G[0][0];
		ld qg = 1.0 - pg;
		TB[6][6] = pduece;
		for (int dsum = 11; dsum >= 0; --dsum) {
			for (int i = max(0, dsum - 6); i <= dsum - (max(0, dsum - 6)); ++i) {
				int j = dsum - i;
				TB[i][j] = p*TB[i + 1][j] + q*TB[i][j + 1];
			}
		}
		ld ptb = TB[0][0];
		S[6][6] = ptb;
		S[5][6] = pg*S[6][6] + qg*S[5][7];
		S[6][5] = pg*S[7][5] + qg*S[6][6];
		for (int dsum = 10; dsum >= 0; --dsum) {
			for (int i = max(0, dsum - 5); i <= dsum - (max(0, dsum - 5)); ++i) {
				int j = dsum - i;
				S[i][j] = pg*S[i + 1][j] + qg*S[i][j + 1];
			}
		}
		ld ps = S[0][0];
		ld qs = 1.0 - ps;
		for (int dsum = 2; dsum >= 0; --dsum) {
			for (int i = max(0, dsum - 1); i <= dsum - (max(0, dsum - 1)); ++i) {
				int j = dsum - i;
				M[i][j] = ps*M[i + 1][j] + qs*M[i][j + 1];
			}
		}
		ld pm = M[0][0];
		print_res(pg, ps, pm);
	}
	return 0;
}