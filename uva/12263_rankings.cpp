
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T, N, M;
	int u, v, uorder, vorder;
	vi ranking;
	vi id_to_order;
	set<ii> swaps;
	cin>>T;
	while(T--) {
		cin >> N;
		ranking.resize(N+1);
		id_to_order.resize(N+1);
		for (int i = 1; i <= N; ++i) {
			cin >> ranking[i];
			id_to_order[ranking[i]] = i;
		}
		cin >> M;
		swaps.clear();
		for (int i = 0; i < M; ++i) {
			cin >> u >> v;
			if (id_to_order[u] > id_to_order[v])
				swap(u, v);
			swaps.insert({u, v});
		}

		bool changed = true;
		while (changed) {
			changed = false;
			for (auto it = swaps.begin(); it != swaps.end();) {
				u = (*it).first;
				v = (*it).second;
				uorder = id_to_order[u];
				vorder = id_to_order[v];
				if (uorder+1==vorder) {
					it = swaps.erase(it);
					swap(ranking[uorder], ranking[vorder]);
					swap(id_to_order[u], id_to_order[v]);
					changed = true;
				}
				else {
					++it;
				}
			}
		}
		if (swaps.empty()) {
			for (int i = 1; i < ranking.size(); ++i) {
				cout<<ranking[i];
				if (i+1 < ranking.size())
					cout<<' ';
			}
		}
		else
			cout<<"IMPOSSIBLE";
		cout<<'\n';

	}
  return 0;
}
