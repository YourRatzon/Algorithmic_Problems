
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

ifstream fin("input.txt");
ofstream fout("output.txt");
vi nums;
int k1, k2;

void get_stats(int l, int r) {
    if (l>=r)
        return;

		int pivot = nums[l + (r-l)/2];
    int lo = l, hi = r;
		while(lo<=hi) {
			while(nums[lo]<pivot) ++lo;
			while(nums[hi]>pivot) --hi;
			if (lo<=hi) {
				swap(nums[lo],nums[hi]);
				++lo, --hi;
			}
		}
		if (k1 <= hi)
			get_stats(l, hi);
    if (k2 >= lo)
      get_stats(lo, r);
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    int N;
    fin>>N>>k1>>k2;
    k1-=1, k2-=1;
    int A,B,C,a1,a2;
    fin>>A>>B>>C>>a1>>a2;
    nums.resize(N);
    nums[0]=a1, nums[1]=a2;
    for (int i = 2; i < N; ++i)
        nums[i] = A*nums[i-2] + B*nums[i-1] + C;

    get_stats(0, N-1);
		for (int i = k1; i <= k2; ++i)
        fout<<nums[i]<<' ';

    return 0;
}
