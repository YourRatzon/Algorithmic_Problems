
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
    int T,N;
    ll K,V;
    string name;
    int start,end;
    cin>>T;
    for (int t = 1; t <= T; ++t) {
        cin>>N>>K>>V;
        if (K*V >= N) {
            start = 0;
            end = (K * V % N)-1;
        }
        else {
            start = (V-1)*K;
            end = V*K-1;
        }
        cout<<"Case #"<<t<<":";
        int left = K;
        for (int i = 0; i < N; ++i) {
            cin>>name;
            if ((i>= start && i<= end) || (left == N-i)) {
                cout<<' '<<name;
                --left;
            }
        }
        cout<<'\n';
    }
    return 0;
}
