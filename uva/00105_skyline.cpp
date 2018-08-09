
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
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	vi heights;
	vii Li, Ri;
	int l,r,h;
	int idx = 0;
	while (cin>>l>>h>>r) {
		Li.push_back({l,idx});
		Ri.push_back({r,idx});
		heights.push_back(h);
		++idx;
	}
	int N = heights.size();

	vii pts(Li.begin(), Li.end());
	pts.insert(pts.end(), Ri.begin(), Ri.end());
	sort(pts.begin(), pts.end());

	vb active(N, false);
	vi res;
	priority_queue<ii> pq;
	int x;
	for (int i = 0; i < pts.size(); ++i) {
		x = pts[i].first;
		idx = pts[i].second;
		h = heights[idx];

		if (active[idx]) {
			active[idx] = false;
			if (idx == pq.top().second) {
				while (!pq.empty() && !active[pq.top().second])
					pq.pop();
				if (res.size()>=2 && res[res.size()-2]==x) {
					res.pop_back();
					res.pop_back();
				}

				res.push_back(x);
				if (pq.empty())
					res.push_back(0);
				else
					res.push_back(pq.top().first);
			}
		}
		else {
			active[idx] = true;
			if (pq.empty() || h > pq.top().first) {
				if (res.size()>=2 && x == res[res.size()-2]) {
					res.pop_back();
					res.pop_back();
				}
				res.push_back(x);
				res.push_back(h);
			}
			pq.push({h,idx});
		}
	}

	cout<<res[0];
	for (int i = 1; i < res.size(); ++i)
		cout<<' '<<res[i];
	cout<<'\n';

  return 0;
}
