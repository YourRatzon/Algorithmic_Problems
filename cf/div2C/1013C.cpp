
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
const int MAX_N = int(1e6 + 5);

vi nums;
vi best_nums;

ll old(int N) {
    ll xbl = INF, ybl = INF;
    ll xtr = -INF, ytr = -INF;
    ll x,y;
    for (int l = 0, r = 2*N-1; l<r; ++l, --r) {
        x = nums[l];
        y = nums[r];
        xbl = min(x,xbl);
        ybl = min(y,ybl);
        xtr = max(x, xtr);
        ytr = max(y, ytr);
    }
    ll res = (xtr-xbl)*(ytr-ybl);
    return res;
}

ll good(int N) {
    sort(nums.begin(), nums.end());
    int min_diff = INF;
    int idx = 0;
    for (int i = 0; i <= N; ++i) {
        int diff = nums[i+N-1]-nums[i];
        if (diff < min_diff) {
            min_diff = diff;
            idx = i;
        }
    }

    vi Y, X;
    for (int i = 0; i < 2*N; ++i) {
        if (i < idx || i > idx+N-1)
            X.push_back(nums[i]);
        else
            Y.push_back(nums[i]);
    }

    ll xbl = INF, ybl = INF;
    ll xtr = -INF, ytr = -INF;
    ll x,y;
    for (int i = 0; i < N; ++i) {
        x = X[i];
        y = Y[i];
        xbl = min(x,xbl);
        ybl = min(y,ybl);
        xtr = max(x, xtr);
        ytr = max(y, ytr);
    }
    ll res = (xtr-xbl)*(ytr-ybl);
    ll old_res = old(N);
    return min(old_res,res);
}

ll bad(int N) {
    ll res = INF_LL;
    do {
        ll curr = old(N);
        if (curr<res) {
            res = curr;
            best_nums = nums;
        }
    } while(next_permutation(nums.begin(), nums.end()));
    return res;
}

void read_in(int N) {
    for (int i = 0; i < 2 * N; ++i) {
        cin >> nums[i];
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(NULL));
    int N;
    cin>> N;
    nums.resize(2 * N);
    read_in(N);
    ll res = good(N);
    cout << res << '\n';
    return 0;
}