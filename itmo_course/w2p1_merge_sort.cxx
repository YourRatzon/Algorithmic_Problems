
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


vi nums;
vi mergevec;
ifstream fin("input.txt");
ofstream fout("output.txt");

void merge(int l, int m, int r) {
	int i = l, j = m+1;
	for (int k = l; i <= m || j <= r; ++k) {
		if (j > r || (i<=m && nums[i] <= nums[j])) {
			mergevec[k]=nums[i];
			++i;
		}
		else {
			mergevec[k]=nums[j];
			++j;
		}
	}
	for (int k = l; k<=r;++k)
		nums[k]=mergevec[k];

	fout<<l<<' '<<r<<' '<<nums[l]<<' '<<nums[r]<<'\n';
}

void merge_sort(int l, int r) {
	if (l==r) {
		return;
	}
	int m = (l + r)/2;
	merge_sort(l,m);
	merge_sort(m+1,r);
	merge(l, m, r);
}

int main() {
	// ios_base::sync_with_stdio(false);
	// cin.tie(0);
	int n;
	fin>>n;
	nums.resize(n+1);
	mergevec.resize(n+1);
	for (int i=1;i<=n;++i)
		fin>>nums[i];

	merge_sort(1, n);
	for (int i = 1; i <= n; ++i)
		fout<<nums[i]<<' ';
	fout<<'\n';
  return 0;
}
