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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int N, k, G, B;
	cin >> N >> k >> G >> B;
	string res = "";
	int curr = 0;
	bool Gnow = true;
	for (int i = 0; i < N; ++i) {
		if (curr == k) {
			if (Gnow) {
				res.push_back('B');
				--B;
				Gnow = false;
				curr = 1;
			}
			else {
				res.push_back('G');
				--G;
				Gnow = true;
				curr = 1;
			}
		}
		else { // curr < k
			if (Gnow) {
				if (G >= B) {
					res.push_back('G');
					--G;
					curr++;
				}
				else {
					res.push_back('B');
					--B;
					Gnow = false;
					curr = 1;
				}
			} 
			else { // Bnow
				if (B >= G) {
					res.push_back('B');
					--B;
					curr++;
				}
				else {
					res.push_back('G');
					--G;
					Gnow = true;
					curr = 1;
				}
			}
		}

		if (G < 0 || B < 0) {
			cout << "NO\n";
			return 0;
		}
	}
	cout << res << '\n';

	return 0;
}