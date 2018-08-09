
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

double EPS = 1e-10;
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

	double x1,y1,x2,y2,x3,y3,x4,y4;
	double xres,yres;
	vector<pair<double,double>> seg;

	while(cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4) {
		if (x2==x3 && y2 == y3)
			seg = {{x1,y1},{x2,y2},{x4,y4}};
		else if (x1 == x3 && y1 == y3)
			seg = {{x2,y2},{x1,y1},{x4,y4}};
		else if (x1 == x4 && y1 == y4)
			seg = {{x2,y2},{x1,y1},{x3,y3}};
		else
		  seg = {{x1,y1},{x2,y2},{x3,y3}};

		xres = seg[2].first - (seg[1].first - seg[0].first);
		yres = seg[2].second- (seg[1].second- seg[0].second);

		cout<<std::fixed<<std::setprecision(3)<<xres<<' '<<yres<<'\n';
	}

  return 0;
}
