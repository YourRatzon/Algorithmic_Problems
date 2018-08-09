
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
typedef vector<double> vd;
typedef unsigned int uint;

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1e6 + 5;

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0);
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int N,M;
    fin>>N>>M;
    vector<uint> A(N), B(M);
    for (int i = 0; i < N; ++i)
        fin>>A[i];
    for (int i = 0; i < M; ++i)
        fin>>B[i];

    vector<uint> C(M*N);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
        	C[i*M + j] = A[i]*B[j];

		uint mask = (1<<8)-1;
		int R = 256;
		vector<uint> D(M*N);
		for (int t = 0; t < 4; ++t) {
			vi count(R+1);
			for (int i = 0; i < M*N; ++i)
				count[((C[i]>>8*t) & mask) + 1]++;
			for (int i = 0; i < R; ++i)
				count[i+1] += count[i];
			for (int i = 0; i < M*N; ++i)
				D[count[(C[i]>>8*t) & mask]++] = C[i];
			for (int i = 0; i < M*N; ++i)
				C[i] = D[i];
		}

		ll res = 0;
		for (int i = 0; i < C.size(); i+=10)
			res+=C[i];
    fout<<res<<'\n';
    return 0;
}
