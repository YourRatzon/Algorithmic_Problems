
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

int gcd(int a, int b) {
		if (b == 0)
			return a;
		else
			return gcd(b, a%b);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;
	while(cin>>N && N) {
		vi nums(N);
		for (int i = 0; i < N; ++i) {
			cin>>nums[i];
		}
		int count = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = i+1; j < N; ++j) {
				if (gcd(nums[i],nums[j]) == 1)
					count++;
			}
		}
		if (count){
			int nC2 = (N*(N-1))/2;
			double res = sqrt(double(6 * nC2) / count);
			cout <<std::fixed<<std::setprecision(6)<<res<<'\n';
		}
		else
			cout<<"No estimate for this data set.\n";
	}

  return 0;
}
