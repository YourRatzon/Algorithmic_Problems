
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(NULL));
    int N,M,q;
    set<int> rows, cols;
    set<ii> cells1, save;
    cin>> N >> M >> q;
    vi lrows(N, INF), rrows(N, -1), tcols(N, INF), bcols(N, -1);
    int r,c;
    for (int i = 0; i < q; ++i) {
        cin>>r>>c;
        --r, --c;
        lrows[r] = min(lrows[r],c);
        rrows[r] = max(rrows[r],c);
        tcols[c] = min(tcols[c],r);
        bcols[c] = max(bcols[c],r);
        cells1.insert({r,c});
    }
    int best_res = -1;
    int curr_res = 0;
    save = cells1;
    for (int i = 0; i < N; ++i) {
        if (lrows[i] != INF) {
            cells1.erase({i, lrows[i]});
            rows.insert(i);
        }
    }
    for (ii p : cells1) {
        cols.insert(p.second);
    }
    curr_res = rows.size() + cols.size();
    best_res=max(curr_res,best_res);

    rows.clear(), cols.clear();
    cells1=save;
    for (int i = 0; i < N; ++i) {
        if (rrows[i] != -1) {
            cells1.erase({i, rrows[i]});
            rows.insert(i);
        }
    }
    for (ii p : cells1) {
        cols.insert(p.second);
    }
    curr_res = rows.size() + cols.size();
    best_res=max(curr_res,best_res);

    rows.clear(), cols.clear();
    cells1=save;
    for (int i = 0; i < N; ++i) {
        if (tcols[i] != INF) {
            cells1.erase({tcols[i], i});
            cols.insert(i);
        }
    }
    for (ii p : cells1) {
        rows.insert(p.first);
    }
    curr_res = rows.size() + cols.size();
    best_res=max(curr_res,best_res);

    rows.clear(), cols.clear();
    cells1=save;
    for (int i = 0; i < N; ++i) {
        if (bcols[i] != -1) {
            cells1.erase({bcols[i], i});
            cols.insert(i);
        }
    }
    for (ii p : cells1) {
        rows.insert(p.first);
    }
    curr_res = rows.size() + cols.size();
    best_res=max(curr_res,best_res);

    int res = N + M - 1 - best_res;
    cout<<res<<'\n';
    return 0;
}