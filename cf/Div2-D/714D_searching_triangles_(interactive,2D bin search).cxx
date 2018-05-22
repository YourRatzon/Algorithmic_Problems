#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

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
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
//char _;

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-9;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;

struct Rect {
	Rect() : xleft(0), ybot(0), xright(0), ytop(0) {}
	Rect(ll x1, ll y1, ll x2, ll y2) :
		xleft(x1), ybot(y1), xright(x2), ytop(y2) {}
	void print() {
		cout << xleft << ' ' << ybot << ' ' << xright << ' ' << ytop;
	}

	bool valid() {
		return (xright >= xleft && ytop >= ybot);
	}
	bool is_unit() {
		return (xright - xleft == 0 && ytop - ybot == 0);
	}
	ll xleft, ybot, xright, ytop;
};


void query(ll xleft, ll ybot, ll xright, ll ytop) {
	cout << "? " << xleft << ' ' << ybot << ' ' << xright << ' ' << ytop << '\n' << flush;
}

Rect solve(ll xleft, ll ybot, ll xright, ll ytop) {
	int ans;
	ll L = xleft, R = xright;
	ll left_border = xleft;
	//find left border
	while (L <= R) {
		ll M = (L + R) / 2;
		query(M, ybot, xright, ytop);
		cin >> ans;
		if (ans == 1) {
			left_border = M;
			L = M+1;
		}
		else {
			R = M-1;
		}
	}
	L = xleft, R = xright;
	ll right_border = xright;
	// find right border
	while (L <= R) {
		ll M = (L + R) / 2;
		query(xleft, ybot, M, ytop);
		cin >> ans;
		if (ans == 1) {
			right_border = M;
			R = M-1;
		}
		else {
			L = M+1;
		}
	}
	ll B = ybot, T = ytop;
	ll bottom_border = ybot;
	while (B <= T) {
		ll M = (B + T) / 2;
		query(xleft, M,xright,ytop);
		cin >> ans;
		if (ans == 1) {
			bottom_border = M;
			B = M + 1;
		}
		else {
			T = M-1;
		}
	}
	B = ybot, T = ytop;
	ll top_border = ytop;
	while (B <= T) {
		ll M = (B + T) / 2;
		query(xleft, ybot, xright, M);
		cin >> ans;
		if (ans == 1) {
			top_border = M;
			T = M-1;
		}
		else {
			B = M+1;
		}
	}
	return Rect(left_border, bottom_border, right_border, top_border);
}

ll get_horiz_split(ll By, ll Ty) {
	ll My;
	ll N = Ty;
	ll ans1, ans2;
	while (By <= Ty) {
		My = (By + Ty) / 2;
		query(1, 1, N, My);
		cin >> ans1;
		if (ans1 == 0) {
			By = My+1;
		}
		else if (ans1 == 2) {
			Ty = My-1;
		}
		else if (ans1 == 1) {
			query(1, My + 1, N, N);
			cin >> ans2;
			if (ans2 == 1)
				return My;
			else if (ans2 == 0)
				Ty = My-1;
			else
				assert(0 && "ans2 should never = 1");
		}
	}
	assert(0 && "since vert split didn't work, horiz split should definitely work");
}
ll get_vert_split(ll Lx, ll Rx) {
	ll Mx;
	ll N = Rx;
	ll ans1, ans2;
	while (Lx <= Rx) {
		Mx = (Lx + Rx) / 2;
		query(1, 1, Mx, N);
		cin >> ans1;
		if (ans1 == 0) {
			Lx = Mx+1;
		}
		else if (ans1 == 2) {
			Rx = Mx-1;
		}
		else if (ans1 == 1) {
			query(Mx + 1, 1, N, N);
			cin >> ans2;
			if (ans2 == 1)
				return Mx;
			else if (ans2 == 0)
				Rx = Mx-1;
			else 
				assert(0 && "ans2 should never = 1");
			
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ll N;
	cin >> N;

	// Find x=M s.t. [L,M] has 1 rect and [M,R] has 1 rect
	ll M = get_vert_split(1,N);
	Rect rect1, rect2;
	if (M != -1) { // vert split exists
		rect1 = solve(1, 1, M, N);
		rect2 = solve(M + 1, 1, N, N);
	}
	else { // no vert split, but horiz split exists
		M = get_horiz_split(1, N);
		rect1 = solve(1, 1, N, M);
		rect2 = solve(1, M + 1, N, N);
	}
	cout << "! ";
	rect1.print();
	cout << ' ';
	rect2.print();
	cout << '\n' <<flush;
	//
	return 0;
}

