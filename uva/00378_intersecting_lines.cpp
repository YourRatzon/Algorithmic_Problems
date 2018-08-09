
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N;
	cin >> N;
	cout <<fixed<<setprecision(2)<<"INTERSECTING LINES OUTPUT\n";
	double x1, y1, x2, y2, x3, y3, x4, y4;
	for (int i = 0; i < N; ++i) {
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
		if (x1 == x2 || x3 == x4) {
			if (x1 == x2 && x3 == x4) {
				if (x1 == x3)
					cout<<"LINE\n";
				else
					cout<<"NONE\n";
			}
			else if (x1 == x2) {
				double m2 = (y4-y3)/(x4-x3);
				double b2 = y3-m2*x3;
				cout<<"POINT "<<x1<<' '<< m2*x1 + b2<<'\n';
			}
			else { // x3 == x4
				double m1 = (y2-y1)/(x2-x1);
				double b1 = y1-m1*x1;
				cout<<"POINT "<<x3<<' '<< m1*x3 + b1<<'\n';

			}
		}
		else {
			double m1 = (y2-y1)/(x2-x1);
			double m2 = (y4-y3)/(x4-x3);
			double b1 = y1-m1*x1;
			double b2 = y3-m2*x3;
			if (m1 == m2) {
				if (b1 == b2)
					cout<<"LINE\n";
				else
					cout<<"NONE\n";
			}
			else {
				double interx = (b2-b1)/(m1-m2);
				double intery = m1 * interx + b1;
				cout<<"POINT "<<interx<<' '<<intery<<'\n';
			}
		}
	}
	cout << "END OF OUTPUT\n";

  return 0;
}
