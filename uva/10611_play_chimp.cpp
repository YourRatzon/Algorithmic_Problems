
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

vi heights;

void solve (int h) {
	int L = 0;
	int R = heights.size()-1;

	int best_shorter = 0;
	while (L<=R) {
			int mid = L + (R-L)/2;
			if (heights[mid] < h) {
				best_shorter = heights[mid];
				L = mid+1;
			}
			else {
				R = mid-1;
			}
	}
	if (best_shorter>0)
		cout<<best_shorter<<' ';
	else
	  cout<<"X ";

	L = 0;
	R = heights.size()-1;
	ll min_taller = INF_LL;
	while (L<=R) {
		int mid = L + (R-L)/2;
		if (heights[mid]>h) {
			min_taller = heights[mid];
			R = mid-1;
		}
		else {
			L = mid+1;
		}
	}
	if (min_taller<INF_LL)
		cout<<min_taller<<'\n';
	else
		cout<<"X\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N,Q;
	cin>>N;
	heights.resize(N);
	for (int i = 0; i < N; ++i) {
		cin>>heights[i];
	}
	cin>>Q;
	int h;
	for (int i = 0; i < Q; ++i) {
		cin>>h;
		auto it = std::upper_bound(heights.begin(),heights.end(),h);
		if (it == heights.end()) {
			--it;
			while (it != heights.begin() && *it == h)
				--it;
			if (heights[0] == h)
				cout<<"X X\n";
			else
				cout<<*it<<" X\n";
		}
		else {
			int min_bigger = *it;
			while (it != heights.begin() && *it >= h)
				--it;
			if (heights[0] == h)
					cout<<"X "<<min_bigger<<'\n';
			else
					cout<<*it<<' '<<min_bigger<<'\n';
		}
		//solve(h);
	}

  return 0;
}
