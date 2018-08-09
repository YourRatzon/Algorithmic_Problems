
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
const ll MOD = ll(1e9 + 7);
const int MAX_N = int(1e6 + 5);

vll counts;

string get_diff(vll& counts1) {
    string diff = "";
    int minc = INF;
    for (int c : counts1) {
        if (c>= 0)
            minc=min(minc, c);
    }
    for (int i = 0; i < counts1.size(); ++i) {
        if (counts1[i]>=0)
            diff += to_string(counts1[i]-minc);
    }
    return diff;
}

string get_diff2(vll& counts2) {
    string diff = "";
    int maxc = -1;
    for (int c : counts2) {
        if (c>= 0)
            maxc=max(maxc, c);
    }
    for (int i = 0; i < counts2.size(); ++i) {
        if (counts2[i]>=0)
            diff += to_string(maxc-counts2[i]);
    }
    return diff;
}

ll solve(string& S, int K, int l, int r) {
    if (K == 1)
        return (S.size()*(S.size()+1))/2;

    if (r-l < 1)
        return 0;
    int mid = l+(r-l)/2;
    ll res = (solve(S, K, l, mid) + solve(S,K,mid+1,r))  % MOD;
    int idx;
    unordered_map<string,ll> diffs;
    vll counts1 = counts, counts2 = counts;
    for (int i = mid+1; i <= r; ++i) {
        if (S[i] < 'a') idx = S[i]-'A' + 26;
        else 			      idx = S[i]-'a';
        counts1[idx]++;
        string diff = get_diff(counts1);
        diffs[diff]++;
    }
    for (int i = mid; i >= l; --i) {
        if (S[i] < 'a') idx = S[i]-'A' + 26;
        else 			      idx = S[i]-'a';
        counts2[idx]++;
        string diff2 = get_diff2(counts2);
        res = (res + diffs[diff2]) % MOD;
    }
    return res % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, K;
    string S;
    cin >> N >> S;
    set<char> seen(S.begin(), S.end());
    K = seen.size();
    int idx;
    counts.assign(52, -1);
    for (char c : S) {
        if (c < 'a') idx = c-'A'+26;
        else 				 idx = c-'a';
        counts[idx] = 0;
    }
    ll res = solve(S, K, 0, S.size()-1);
    cout<<res<<'\n';
    return 0;
}
