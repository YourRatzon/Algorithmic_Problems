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

int MAX_N;
vector<vii> costs;
vi S;
vi W;

short get_cost(int a, int b, int n) {
  int c = a^b;
  int cost = 0;
  for (int i = 0; i < n; ++i) {
    if  ((c & (1<<i)) == 0) { // 0 bit
      cost += W[n-1-i];
    }
  }
  return cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m,q;
    cin>>n>>m>>q;
    W.resize(n);
    for (int i = 0; i < n; ++i)
      cin>>W[i];

    MAX_N = int(pow(2,n));
    costs.assign(MAX_N, vii());
    S.assign(MAX_N, 0);
    string bin;
    for (int i = 0; i < m; ++i) {
      cin>>bin;
      int x = stoi(bin, nullptr, 2);
      S[x]++;
    }

    for (int i = 0; i < MAX_N; ++i) {
      for (int j = 0; j < MAX_N; ++j) {
        short curr_cost = get_cost(i,j,n);
        costs[i].push_back({curr_cost,j});
      }
      sort(costs[i].begin(), costs[i].end());
    }


    int K;
    vector<vector<int>> queries(MAX_N, vector<int>());
    vii queries_order(q);
    vi res(q, 0);
    map<ii,int> q_to_id;
    for (int i = 0; i < q; ++i) {
        cin >> bin >> K;
        int x = stoi(bin, nullptr, 2);
        queries_order[i] = {x, K};
        queries[x].push_back(K);
        q_to_id[{x,K}] = i;
    }

    for (int i = 0; i < MAX_N; ++i) {
        if (queries[i].empty())
            continue;
        sort(queries[i].begin(),queries[i].end());
        int curr_num = 0;
        int k = 0;
        for (int j = 0; j < queries[i].size(); ++j) {
            K = queries[i][j];
            while (k < costs[i].size() && costs[i][k].first <= K) {
                curr_num += S[costs[i][k].second];
                ++k;
            }
            int id = q_to_id[{i,K}];
            res[id] = curr_num;
        }
    }
    for (int x : res)
        cout<<x<<'\n';
    return 0;
}
