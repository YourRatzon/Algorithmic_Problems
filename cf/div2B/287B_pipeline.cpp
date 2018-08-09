
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

ll get_max(ll K) {
    return (K*(K-1))/2 + 1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll N, K;
    cin>>N>>K;

    if (N > get_max(K)) {
        cout<<-1<<'\n';
        return 0;
    }
		if (N == 1) {
			cout<<0<<'\n';
			return 0;
		}
    if (N<=K) {
        cout<<1<<'\n';
        return 0;
    }
    N--, K--;
    ll L = 1, R = K;
    ll res;
    while (L <= R) {
        ll num = L + (R-L)/2;
        ll sum = K*(K+1)/2 - (K-num)*(K-num+1)/2;
        if (sum == N) {
            res = num;
            break;
        }
        else if (sum > N)
            R = num-1;
        else if (N-sum <= K-num) {
            res = num+1;
            break;
        }
        else
            L = num+1;
    }
    cout<<res<<"\n";
    return 0;
}
