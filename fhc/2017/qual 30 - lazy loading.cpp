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
const int MAX_N = 1000 + 5;


int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	
	ifstream fin("b.in");
	ofstream fout("b.out");

	int T;
	fin >> T;
	for (int t = 1; t <= T; ++t) {
		int N;
		fin >> N;
		vi W(N);
		for (int i = 0; i < N; ++i) {
			fin >> W[i];
		}
		sort(W.begin(), W.end(), greater<int>());
		int res = 0;
		deque<int> dq(W.begin(), W.end());
		while (!dq.empty()) {
			int curr_front = dq.front();
			dq.pop_front();
			int curr_w = curr_front;
			while (!dq.empty() && curr_w < 50) {
				curr_w += curr_front;
				dq.pop_back();
			}
			if (curr_w >= 50)
				++res;
			else 
				break;
		}
		fout << "Case #"<<t<<": "<<res<< '\n';
	}
	return 0;
}