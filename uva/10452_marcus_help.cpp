
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

vector<vc> grid;
int M,N;

bool legal_move(int r, int c) {
		return r>=0 && r < M && c>= 0 && c < N;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	vc targets = {'I', 'E', 'H','O', 'V', 'A', '#'};
	vi rmoves = {0,-1,0};
	vi cmoves = {-1,0,1};
	vector<string> commands = {"left", "forth", "right"};
	int T = 0;
	cin>>T;
	for (int t = 0; t < T; ++t) {
		int r,c;
		cin>>M>>N;
		grid.assign(M,vc(N));
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
					cin >> grid[i][j];
					if (grid[i][j] == '@') {
						r=i, c=j;
					}
			}
		}

		for (int i = 0; i < targets.size(); ++i) {
			for (int j = 0; j < rmoves.size(); ++j) {
				int newr = r+rmoves[j];
				int newc = c+cmoves[j];
				if (legal_move(newr,newc) && grid[newr][newc] == targets[i]) {
					r = newr;
					c = newc;
					cout<<commands[j];
					if (targets[i] != '#')
						cout<<' ';
					break;
				}
			}
		}
		cout<<'\n';
	}


  return 0;
}
