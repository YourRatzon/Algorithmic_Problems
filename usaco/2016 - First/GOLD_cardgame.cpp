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
const int MAX_N = 2 * 1e5 + 1;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ifstream fin("cardgame.in");
	ofstream fout("cardgame.out");
	int N,x;
	fin >> N;
	set<int> my_cards, his_high, his_low;
	for (int i = 1; i <= 2 * N; ++i)
		my_cards.insert(i);
	for (int i = 0; i < N / 2; ++i) {
		fin >> x;
		his_high.insert(x);
		my_cards.erase(x);
	}
	for (int i = 0; i < N / 2; ++i) {
		fin >> x;
		his_low.insert(x);
		my_cards.erase(x);
	}
	int res = 0;
	auto it = his_high.rbegin();
	while (it != his_high.rend()) {
		auto myit = my_cards.upper_bound(*it);
		if (myit != my_cards.end()) {
			++res;
			my_cards.erase(prev(my_cards.end()));
		}
		++it;
	}
	for (int x : his_low) {
		auto myit = my_cards.lower_bound(x);
		if (myit != my_cards.begin()) {
			++res;
			my_cards.erase(my_cards.begin());
		}
	}
	fout << res << '\n';
	return 0;
}