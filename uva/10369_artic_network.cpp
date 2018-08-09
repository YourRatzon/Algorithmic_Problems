
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

vector<double> prim(const vii& posts) {
		int N = posts.size();
		vector<vd> adjmat(N, vd(N, INF));
		for (int i = 0; i < posts.size();++i) {
			for (int j = i+1; j < posts.size(); ++j) {
				double w = pow(posts[i].first-posts[j].first,2) +
									 pow(posts[i].second-posts[j].second,2);
				adjmat[i][j] = adjmat[j][i] = w;
			}
		}

		vd weights;
		vb selected(N);
		vii min_e(N, {INF,-1}); // {weight, to}
 		min_e[0].first = 0;
		for (int i = 0; i < N; ++i) {
			int v = -1;
			for (int j = 0; j < N; ++j) {
				if (!selected[j] && (v==-1 || min_e[j].first < min_e[v].first))
					v = j;
			}

			selected[v] = true;
			if (min_e[v].second != -1)
				weights.push_back(min_e[v].first);

			for (int u = 0; u < N; ++u) {
				if (adjmat[u][v] < min_e[u].first)
					min_e[u] = {adjmat[u][v], v};
			}
		}
		return weights;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int T,S,P,x,y;
	cin>>T;
	while(T--) {
		cin>>S>>P;
		vii posts(P);
		for (int i = 0; i < P; ++i) {
			cin>>x>>y;
			posts[i] = {x,y};
		}
		vector<double> weights = prim(posts);
		sort(weights.begin(), weights.end(), greater<double>());
		cout<<fixed<<setprecision(2)<<sqrt(weights[S-1])<<'\n';
	}

  return 0;
}
