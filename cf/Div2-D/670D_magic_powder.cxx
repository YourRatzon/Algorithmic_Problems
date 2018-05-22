

#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << __duration << '\n';
}
// END TIMER

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
//char _;

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-9;
bool eq(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = ll(1e18);
const int MAX_N = 1e7;



vll need, have;
struct item {
	item(){}
	item(ll nu, ll mo, ll eed) : num(nu), more(mo), need(eed) {}
	ll num;
	ll more;
	ll need;
};

vector < item > cookies;

bool is_possible(ll mid, ll powder) {
	
	for (int i = 0; i < cookies.size(); ++i) {
		if (cookies[i].num < mid) {
			powder -= cookies[i].more;
			powder -= cookies[i].need * (mid - (cookies[i].num+1));
		}
		if (powder < 0)
			return false;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//start_timer();

	ll N, powder;
	cin >> N >> powder;
	need.resize(N);
	cookies.resize(N);
	have.resize(N);
	for (int i = 0; i < N; ++i) {
		cin >> need[i];
	}
	for (int i = 0; i < N; ++i) {
		cin >> have[i];
		ll num = have[i] / need[i];
		ll more = need[i] - (have[i] % need[i]);
		cookies[i] = item(num, more, need[i]);
	}
	
	ll low = 0;
	ll high = 2e9 + 10;
	ll best_res = 0;
	while (low <= high) {
		ll mid = low + (high - low) / 2;
		if (is_possible(mid, powder)) {
			best_res = mid;
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	cout << best_res << '\n';
	//print_timer();
	return 0;
}