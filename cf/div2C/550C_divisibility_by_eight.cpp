
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

	string s;
	cin>>s;
	for (int i = 0; i<s.size();++i) {
		int num = s[i]-'0';
		if (num % 8 == 0) {
			cout<<"YES\n"<<num<<'\n';
			return 0;
		}
	}
	for (int i = 0; i<s.size();++i) {
		for (int j = i+1; j<s.size();++j) {
			int num = 10*(s[i]-'0') + (s[j]-'0');
			if (num % 8 == 0) {
				cout<<"YES\n"<<num<<'\n';
				return 0;
			}
		}
	}
	for (int i = 0; i<s.size();++i) {
		for (int j = i+1; j<s.size();++j) {
			for (int k = j+1;k<s.size();++k) {
				int num = 100*(s[i]-'0') + 10*(s[j]-'0') + (s[k]-'0');
				if (num % 8 == 0) {
					cout<<"YES\n"<<num<<'\n';
					return 0;
				}
			}
		}
	}

	cout<<"NO\n";

  return 0;
}
