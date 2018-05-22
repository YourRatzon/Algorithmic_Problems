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
typedef vector<bool> vb;
typedef vector<char> vc;
typedef vector<double> vd;

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 2e5+2;

vi get_setbits(ull n) {
	vi res;
	for (int i = 0; i < 64; ++i) {
		if ((n & (1ull << i)) != 0)
			res.push_back(i);
	}
	return res;
}
vi get_powers(int p, int nmax) {
	if (p == 0)
		return { 0 };
	if (nmax == 0)
		return {};
	if (nmax == 1)
		return { p };

	vi tmp1 = get_powers(p - 1, nmax / 2);
	vi tmp2 = get_powers(p - 1, (nmax+1) / 2);

	tmp1.insert(tmp1.end(), tmp2.begin(), tmp2.end());
	return tmp1;
}
int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	ifstream fin("a.in");
	ofstream fout("a.out");
	int T, N, K;
	fin >> T;
	vector<pair<double,double>> PK;
	vd side_area;
	for (int t = 0; t < T; ++t) {
		fin >> N >> K;
		PK.resize(N);
		side_area.resize(N);
		int r, h;
		for (int i = 0; i < N; ++i) {
			fin >> r >> h;
			PK[i] = { r, h };
		}
		sort(PK.begin(), PK.end(), greater<pair<double, double>>());
		for (int i = 0; i < N; ++i) {
			side_area[i] = 2.0 * M_PI*PK[i].first*PK[i].second;
		}
		double best_res = 0;
		for (int i = 0; i < N; ++i) {
			double curr_res = M_PI * PK[i].first*PK[i].first + side_area[i];
			vd curr_side_a(side_area.begin() + i+1, side_area.end());
			if (curr_side_a.size() < K - 1) {
				best_res = max(best_res, curr_res);
				break;
			}
			sort(curr_side_a.begin(), curr_side_a.end(), greater<double>());
			for (int k = 0; k < K-1; ++k) {
				curr_res += curr_side_a[k];
			}
			best_res = max(best_res, curr_res);
		}
		fout << "Case #" << t + 1 << ": " << std::fixed
			 <<std::setprecision(15)<<best_res << '\n';
	}
	
	return 0;
}