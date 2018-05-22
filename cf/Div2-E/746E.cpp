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


vi cards;
void fail() {
	cout << -1 << '\n';
	exit(0);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N, M;
	cin >> N >> M;
	cards.resize(N);
	int neven=0, nodd = 0;
	set<int> seen;
	set<int> dups;
	for (int i = 0; i < N; ++i) {
		cin >> cards[i];
		if (cards[i] % 2 == 0)
			neven++;
		else
			nodd++;
		if (seen.count(cards[i]) == 0)
			seen.insert(cards[i]);
		else
			dups.insert(i);
	}

	set<int> evens, odds;
	for (int i = 1; i <= min(int(5e5),M); ++i) {
		if (seen.count(i) != 0)
			continue;

		if (i % 2 == 0)
			evens.insert(i);
		else
			odds.insert(i);
	}
	int res = 0;
	int midx = 1;
	for (int i : dups) {
		if (nodd < neven) { // need odd
			if (odds.empty())
				fail();
			int new_odd = *odds.begin();
			odds.erase(odds.begin());
			if (cards[i] % 2 == 0) {
				--neven;
				++nodd;
			}
			cards[i] = new_odd;
		}
		else if (neven < nodd){ // need even
			if (evens.empty())
				fail();
			int new_even = *evens.begin();
			evens.erase(evens.begin());
			if (cards[i] % 2 == 1) {
				--nodd;
				++neven;
			}
			cards[i] = new_even;
		}
		else {
			if (cards[i] % 2 == 0) {
				if (evens.empty())
					fail();
				int new_even = *evens.begin();
				evens.erase(evens.begin());
				cards[i] = new_even;
			}
			else {
				if (odds.empty())
					fail();
				int new_odd = *odds.begin();
				odds.erase(odds.begin());
				cards[i] = new_odd;
			}
		}
		++res;
	}
	int idx = 0;
	while (neven < nodd) {
		if (evens.empty())
			fail();
		if (cards[idx] % 2 == 1) {
			int new_even = *evens.begin();
			evens.erase(evens.begin());
			cards[idx] = new_even;
			++neven;
			--nodd;
			++res;
		}
		++idx;
	}
	idx = 0;
	while (nodd < neven) {
		if (odds.empty())
			fail();
		if (cards[idx] % 2 == 0) {
			int new_odd = *odds.begin();
			odds.erase(odds.begin());
			cards[idx] = new_odd;
			++nodd;
			--neven;
			++res;
		}
		++idx;
	}
	cout << res << '\n';
	for (int x : cards)
		cout << x << ' ';
	cout << '\n';
	return 0;
}