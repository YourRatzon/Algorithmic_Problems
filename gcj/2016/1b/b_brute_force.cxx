

#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << __duration << '\n';
}
// END TIMER

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
//char _;

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-9;
bool eq(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = ll(1e18);
const int MAX_N = 1e7;

ll min_diff = INF_LL;
string min_A = "ZZZZZZZZZZZZZZZZZZ", min_B = "ZZZZZZZZZZZZZZZZZZ";

void update_res(string& A, string& B, ll diff) {

	if (diff < min_diff) {
		min_diff = diff;
		min_A = A;
		min_B = B;
	}
	else if (diff == min_diff) {
		if (A < min_A) {
			min_A = A;
			min_B = B;
		}
		else if (A == min_A && B < min_B) {
			min_A = A;
			min_B = B;
		}
	}
}
void set_indicies(string& A, string& B, int& a, int& b, bool& use_A) {
	while (a < A.size() && b < B.size()) {
		if (A[a] == '?') {
			use_A = true;
			break;
		}
		else if (B[b] == '?') {
			use_A = false;
			break;
		}

		else if (a < b && A[a] != '?')
			++a;
		else if (b < a && B[b] != '?')
			++b;
		else if (a == b && A[a] != '?' && B[b] != '?')
			++a;
	}
	if (a == A.size()) {
		use_A = false;
		while (b < B.size() && B[b] != '?')
			++b;
	}
	if (b == B.size()) {
		use_A = true;
		while (a < A.size() && A[a] != '?')
			++a;
	}
}

map < pair<string, string>, ll> memo;


ll solve(string A, string B, int a, int b) {
	if (a >= A.size() && b >= B.size()) {
		ll num_A = stoll(A);
		ll num_B = stoll(B);
		ll diff = abs(num_A - num_B);
		update_res(A, B, diff);
		return diff;
	}

	bool use_A = false;
	set_indicies(A,B,a, b, use_A);
	if (a < A.size() || b < B.size()) {

		for (int i = 0; i < 10; ++i) {
			if (use_A)
				A[a] = ('0' + i);
			else
				B[b] = ('0' + i);

			if (memo.count({ A, B }) == 0)
				memo[{A, B}] = solve(A, B, a, b);
		}
	}
	else {
		if (memo.count({ A, B }) == 0)
			memo[{A, B}] = solve(A, B, a, b);
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//start_timer();

	ifstream fin("b.in");
	ofstream fout("b.out");

	int T;
	fin >> T;
	string A, B;
	for (int t = 0; t < T; ++t) {
		fin >> A >> B;
		min_diff = INF_LL;
		min_A = "ZZZZZZZZZZZZZZZZZZ";
		min_B = "ZZZZZZZZZZZZZZZZZZ";
		memo.clear();
		solve(A, B, 0, 0);
		fout << "Case #" << t + 1 << ": ";
		fout << min_A << ' ' << min_B << '\n';
		fout.flush();
	}

	//print_timer();
	return 0;
}