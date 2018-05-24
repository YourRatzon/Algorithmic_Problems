
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

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = ll(1e9 + 7);

vector<vll> DP;
vll Apts, Bpts;
string A,B;

ll S(int i , int j) {
  if (i < 0 || j < 0)
    return 0;
  if ((A[i] == 'W' && B[j] == 'L' && Apts[i]>Bpts[j]) ||
      (A[i] == 'L' && B[j] == 'W' && Apts[i]<Bpts[j]))
    return Apts[i]+Bpts[j];
  else
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    DP.assign(N,vll(N,0));
    Apts.resize(N), Bpts.resize(N);
    cin>>A;
    for (int i = 0; i < N; ++i) {
      cin>>Apts[i];
    }
    cin>>B;
    for (int i = 0; i < N; ++i) {
      cin>>Bpts[i];
    }
    DP[0][0] = S(0,0);
    for (int i = 1; i < N; ++i) {
        DP[0][i] = max(DP[0][i-1],S(0,i));
        DP[i][0] = max(DP[i-1][0],S(i,0));
    }

    for (int i = 1; i < N; ++i) {
      for (int j = 1; j < N; ++j) {
          DP[i][j] = max(DP[i][j],DP[i-1][j]);
          DP[i][j] = max(DP[i][j],DP[i][j-1]);
          DP[i][j] = max(DP[i][j], DP[i-1][j-1] + S(i,j));
      }
    }
    cout<<DP[N-1][N-1]<<'\n';
    return 0;
}
