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

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1e6 + 5;

struct Floor {
	Floor() : price(0), cows(0) {}
	Floor(int p) : price(p), cows(0) {}
	ll price;
	ll cows;
};

bool operator>(const Floor& lhs, const Floor& rhs) {
	double lhs_gain = lhs.price / double(lhs.cows) - lhs.price / double(lhs.cows + 1);
	double rhs_gain = rhs.price / double(rhs.cows) - rhs.price / double(rhs.cows + 1);
	return lhs_gain < rhs_gain;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	ifstream fin("tallbarn.in");
	ofstream fout("tallbarn.out");
	ll N, K;
	fin >> N >> K;
	priority_queue<Floor, vector<Floor>, greater<Floor>> floors;
	ll p = 0;
	ll total_p = 0;
	vector<Floor> fvec(N);
	for (int i = 0; i < N; ++i) {
		fin >> p;
		total_p += p;
		fvec[i] = Floor(p);
	}
	ll save_K = K;
	for (int i = 0; i < N; ++i) {
		long double ratio = save_K / (long double)(total_p);
		ll curr_cows = floor((long double)fvec[i].price * ratio) - 250;
		if (curr_cows > 0) {
			fvec[i].cows = min(fvec[i].price, curr_cows);
			K -= fvec[i].cows;
		}
	}
	for (int i = 0; i < N; ++i) {
		if (fvec[i].cows == 0) {
			fvec[i].cows = 1;
			--K;
		}
		floors.push(fvec[i]);
	}
	while (K) {
		Floor top = floors.top();
		floors.pop();
		top.cows++;
		floors.push(top);
		--K;
	}
	long double res = 0;
	while (!floors.empty()) {
		Floor f = floors.top();
		floors.pop();
		res += f.price / (double)(f.cows);
	}
	fout << ll(round(res)) << '\n';
	return 0;
}