
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

struct rect {
	rect(double a,double b,double c,double d):xl(a),xr(b),yt(c),yb(d) {}
	double xl, xr, yt, yb;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	char type;
	double xul, yul, xbr, ybr;
	vector<rect> rects;
	while(cin>>type && type !='*') {
		cin>>xul>>xbr>>yul>>ybr;
		rects.push_back(rect(xul,yul,xbr,ybr));
	}
	double x,y;
	int point_id = 1;
	while(cin>>x>>y && (x != 9999.9 || y!= 9999.9)) {
		bool in = false;
		for (int i = 0; i < rects.size(); ++i) {
			rect r = rects[i];
			if (x>r.xl && x<r.xr && y<r.yt && y>r.yb) {
				cout<<"Point "<<point_id<<" is contained in figure "<<i+1<<'\n';
				in = true;
			}
		}
		if (!in)
			cout<<"Point "<<point_id<<" is not contained in any figure\n";

		point_id++;
	}

  return 0;
}
