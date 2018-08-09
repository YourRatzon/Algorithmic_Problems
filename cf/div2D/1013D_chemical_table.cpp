
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
const int MOD = int(1e9 + 7);

int nsets;
vi parent;
vi ranks;

void make_set(int N) {
  nsets=N;
  ranks.assign(N, 0);
  parent.resize(N);
  iota(parent.begin(),parent.end(),0);
}

int find_set(int u) {
  if (parent[u] == u) return u;
  return parent[u] = find_set(parent[u]);
}

void unite(int u, int v) {
  int pu = find_set(u);
  int pv = find_set(v);
  if (pu == pv)
    return;

  --nsets;
  if (pu < pv)
    swap(pu,pv);
  parent[pv]=pu;
  if (ranks[pu]==ranks[pv])
    ranks[pu]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(NULL));
    int N,M,q;
    cin>>N>>M>>q;
    make_set(N+M);
    int r,c;
    for (int i = 0; i < q; ++i) {
        cin>>r>>c;
        --r, --c;
        unite(r,N+c);
    }
    cout<<nsets-1<<'\n';
    return 0;
}
