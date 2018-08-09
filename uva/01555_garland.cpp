
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

double minB;
int N;

double check(double Hlast, double Hcurr) {
	double Hnext;
	double minh = min(Hlast,Hcurr);
	for (int i=3;i<=N;++i) {
		Hnext = 2.0*(Hcurr+1)-Hlast;
		if (Hnext < 0)
			return -1;

		minh = min(minh, Hnext);
		Hlast = Hcurr;
		Hcurr = Hnext;
	}
	minB = min(minB, Hnext);
	return minh;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	double A;
	while (cin>>N>>A) {
		minB = 1e6;
		double L = 0.00, R = A;
		while (L<=R) {
			double H2 = L + (R-L)/2;
			double minh = check(A,H2);
			if (eq_(minh,0.0))
				break;
			else if (minh > 0)
				R = H2 - 0.000000001;
			else
				L = H2 + 0.000000001;
		}
		cout<< fixed << setprecision(2) << minB <<'\n';
	}

  return 0;
}
