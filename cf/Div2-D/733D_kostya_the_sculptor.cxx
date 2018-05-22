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

double EPS = 1e-9;
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

struct Dims {
	int a, b, c;
	int idx;
};
double get_rad(Dims d) {
	return double(min(d.a, min(d.b, d.c))) / 2;
}

bool sort_first_two(Dims& lhs, Dims& rhs) {
	if (lhs.a != rhs.a)
		return lhs.a < rhs.a;
	else if (lhs.b != rhs.b)
		return lhs.b < rhs.b;
	else
		return lhs.c < rhs.c;
}

void solve_first_two(vector<Dims>& P, double& best_double_rad,
					ii& best_double_idxs) {
	sort(P.begin(), P.end(), sort_first_two);
	int idx = 1;
	int last = 0;
	while (idx < P.size()) {
		while (idx < P.size() && P[idx].a == P[idx - 1].a &&
			P[idx].b == P[idx - 1].b)
			++idx;
		if (idx - 1 > last) {
			Dims d1 = P[idx - 1];
			Dims d2 = P[idx - 2];
			Dims d3 = { d1.a, d1.b, d1.c + d2.c, -1 };
			double curr_rad = get_rad(d3);
			if (curr_rad > best_double_rad){
				best_double_rad = curr_rad;
				best_double_idxs = { d1.idx, d2.idx };
			}
		}
		last = idx;
		++idx;
	}
}

bool sort_last_two(Dims& lhs, Dims& rhs) {
	if (lhs.c != rhs.c)
		return lhs.c < rhs.c;
	else if (lhs.b != rhs.b)
		return lhs.b < rhs.b;
	else
		return lhs.a < rhs.a;
}
void solve_last_two(vector<Dims>& P, double& best_double_rad,
	ii& best_double_idxs) {
	sort(P.begin(), P.end(), sort_last_two);
	int idx = 1;
	int last = 0;
	while (idx < P.size()) {
		while (idx < P.size() && P[idx].c == P[idx - 1].c &&
			P[idx].b == P[idx - 1].b)
			++idx;
		if (idx - 1 > last) {
			Dims d1 = P[idx - 1];
			Dims d2 = P[idx - 2];
			Dims d3 = { d1.a + d2.a, d1.b, d1.c, -1 };
			double curr_rad = get_rad(d3);
			if (curr_rad > best_double_rad){
				best_double_rad = curr_rad;
				best_double_idxs = { d1.idx, d2.idx };
			}
		}
		last = idx;
		++idx;
	}
}

bool sort_first_last(Dims& lhs, Dims& rhs) {
	if (lhs.a != rhs.a)
		return lhs.a < rhs.a;
	else if (lhs.c != rhs.c)
		return lhs.c < rhs.c;
	else
		return lhs.b < rhs.b;
}

void solve_first_last(vector<Dims>& P, double& best_double_rad,
	ii& best_double_idxs) {
	sort(P.begin(), P.end(), sort_first_last);
	int idx = 1;
	int last = 0;
	while (idx < P.size()) {
		while (idx < P.size() && P[idx].a == P[idx - 1].a &&
			P[idx].c == P[idx - 1].c)
			++idx;
		if (idx - 1 > last) {
			Dims d1 = P[idx - 1];
			Dims d2 = P[idx - 2];
			Dims d3 = { d1.a, d1.b+d2.b, d1.c, -1 };
			double curr_rad = get_rad(d3);
			if (curr_rad > best_double_rad){
				best_double_rad = curr_rad;
				best_double_idxs = { d1.idx, d2.idx };
			}
		}
		last = idx;
		++idx;
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	int a, b, c;
	vector<Dims> P(n);
	double best_single_rad = 0;
	int best_single_idx = 1;
	for (int i = 0; i < n; ++i) {
		cin >> a >> b >> c;
		vi temp = { a, b, c };
		sort(temp.begin(), temp.end());
		P[i] = { temp[0],temp[1],temp[2], i+1 };
		double curr_rad = get_rad(P[i]);
		if (curr_rad > best_single_rad) {
			best_single_rad = curr_rad;
			best_single_idx = i + 1;
		}
	}
	double best_double_rad = 0;
	ii best_double_idxs = { 0, 0 };
	solve_first_two(P, best_double_rad, best_double_idxs);
	solve_last_two(P, best_double_rad, best_double_idxs);
	solve_first_last(P, best_double_rad, best_double_idxs);

	if (best_single_rad > best_double_rad) {
		cout << 1 << '\n';
		cout << best_single_idx << '\n';
	}
	else {
		cout << 2 << '\n';
		cout << best_double_idxs.first << ' '<<best_double_idxs.second << '\n';
	}
	return 0;
}
