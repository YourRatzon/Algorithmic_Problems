
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
typedef vector<double> vd;

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1e6 + 5;

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n;
	fin>>n;
	vi nums(n);
	for (int i=0;i<n;++i) {
		fin>>nums[i];
	}

	for (int i=0;i<n;++i) {
		int min_j = i;
		for (int j = i+1; j < n; ++j) {
			if (nums[j] < nums[min_j])
				min_j = j;
		}
		if (i != min_j) {
			swap(nums[i], nums[min_j]);
			fout<<"Swap elements at indices "<<i+1<<" and "<<min_j+1<<".\n";
		}
	}

	fout<<"No more swaps needed.\n";
	for (int x : nums)
		fout<<x<<' ';
	fout<<'\n';
  return 0;
}
