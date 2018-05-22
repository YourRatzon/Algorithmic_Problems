				 //#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
				 using namespace std;

//#define F first
//#define S second

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

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1e6 + 5;

vi A;
vi P;
int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	ifstream fin("subrev.in");
	ofstream fout("subrev.out");
	int N;
	int res = 0;
	fin >> N;
	A.resize(N);
	for (int i = 0; i < N; ++i) {
		fin >> A[i];
	}
	P.assign(A.size() + 1, -1);
	vi LIS(A.size() + 1, 1);
	for (int i = 0; i < A.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			if (A[j] < A[i] && LIS[j] + 1 > LIS[i]) {
				LIS[i] = LIS[j] + 1;
				P[i] = j;
			}
		}
	}
	for (int k = 0; k < A.size(); ++k) {
		int pos = k;
		set<int> path;
		while (pos != -1) {
			path.insert(pos);
			pos = P[pos];
		}
		vi B;
		vi Bidx;
		for (int j = 0; j < A.size(); ++j) {
			if (path.find(j) == path.end()) {
				B.push_back(A[j]);
				Bidx.push_back(j);
			}
		}
		vi P2(B.size() + 1, -1);
		vi LDS(B.size() + 1, 1);
		for (int i = 0; i < B.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (B[j]>B[i] && LDS[j] + 1 > LDS[i]) {
					LDS[i] = 1 + LDS[j];
					P2[i] = j;
				}
			}
		}
		for (int i = 0; i < B.size(); ++i) {
			int pos = i;
			vi path;
			while (pos != -1) {
				path.push_back(Bidx[pos]);
				pos = P2[pos];
			}
			for (int j = 0, l = path.size() - 1; j < l; ++j, --l) {
				swap(A[path[j]], A[path[l]]);
			}
			
			LIS.assign(A.size() + 1, 1);
			for (int i = 0; i < A.size(); ++i) {
				for (int j = 0; j < i; ++j) {
					if (A[j] < A[i] && LIS[j] + 1 > LIS[i]) {
						LIS[i] = LIS[j] + 1;
					}
				}
			}
			int curr = 0;
			for (int i = 0; i < A.size(); ++i)
				curr = max(curr, LIS[i]);
			for (int j = 0, l = path.size() - 1; j < l; ++j, --l) {
				swap(A[path[j]], A[path[l]]);
			}
			res = max(res, curr);
		}

	}
	fout << res << '\n';
	return 0;
}