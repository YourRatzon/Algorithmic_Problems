
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

vi rmoves = {-1,-2,-2,-1,1,2,2,1};
vi cmoves = {-2,-1,1,2,2,1,-1,-2};

bool legal(int r, int c) {
	return r>=0 && r < 8 && c >=0 && c < 8;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	string from,to;
	while(cin>>from>>to) {
		int rfrom = from[1] - '0' - 1;
		int cfrom = from[0] - 'a';
		int rto = to[1]-'0'-1;
		int cto = to[0]-'a';
		if (rfrom == rto && cfrom == cto) {
			cout<<"To get from " + from + " to " + to + " takes 0 knight moves.\n";
			continue;
		}
		vector<vb> visited(8,vb(8,false));
		queue<pair<ii,int>> q;
		q.push({{rfrom,cfrom},0});
		while(!q.empty()) {
			pair<ii,int> p = q.front();
			q.pop();
			int r = p.first.first;
			int c = p.first.second;
			int d = p.second;
			for (int i=0;i<rmoves.size();++i) {
				int rnew = r+rmoves[i];
				int cnew = c+cmoves[i];
				if (legal(rnew,cnew) && !visited[rnew][cnew]) {
					if (rnew == rto && cnew == cto) {
						cout<<"To get from " + from + " to " + to + " takes "
								<< d+1 <<" knight moves.\n";
						q = {};
						break;
					}
					q.push({{rnew,cnew},d+1});
				}
			}
		}
 	}

  return 0;
}
