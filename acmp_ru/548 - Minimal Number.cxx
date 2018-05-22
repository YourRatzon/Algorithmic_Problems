#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>


/*
ID: jamerz1
PROG: cbarn
LANG: C++11
*/

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << __duration << '\n';
}
// END TIMER

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

void equalize_lengths(string& A, string &B, int save_a, int a, int b) {
	string a_suffix = A.substr(save_a, a - save_a + 1);
	int len_B_tail = B.size() - b;
	int times_to_add = len_B_tail / a_suffix.size();
	for (int i = 0; i < times_to_add; ++i)
		A.append(a_suffix);
	int remainder = len_B_tail % a_suffix.size();
	for (int i = 0; i < remainder; ++i) {
		A.push_back(a_suffix[i]);
	}
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//start_timer();

	ifstream fin("INPUT.TXT");
	ofstream fout("OUTPUT.TXT");

	int T = 1;
	for (int t =0;t<T;++t) {

		string A, B, res;
		fin >> A >> B;
		int a = 0, b = 0;
		int Asz = A.size();
		int Bsz = B.size();
		while (a < Asz && b < Bsz) {
			int save_a = a;
			int save_b = b;
			while (a<A.size() && b < B.size() && A[a] == B[b]) {
				++a;
				++b;
			}
			if (a == Asz) {
				if (b == Bsz) {
					res.push_back(A[save_a]);
					a = save_a + 1;
					b = save_b;
				}
				else {
					res.push_back(B[save_b]);
					a = save_a;
					b = save_b + 1;
				}
			}
			else if (b == Bsz) {
				res.push_back(A[save_a]);
				b = save_b;
				a = save_a + 1;
			}
			else {
				if (A[a] < B[b]) {
					res.push_back(A[save_a]);
					a = save_a + 1;
					b = save_b;
				}
				else { // A[a] > B[b]
					res.push_back(B[save_b]);
					b = save_b + 1;
					a = save_a;
				}
			}
		}
		if (a < Asz) {
			res.append(A.substr(a, Asz - a));
		}
		else if (b < Bsz)
			res.append(B.substr(b, Bsz-b));
		fout << res << '\n';
	}

	fin.close();
	fout.close();
	//print_timer();
	return 0;
}