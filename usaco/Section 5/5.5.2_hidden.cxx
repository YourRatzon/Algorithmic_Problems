//#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

/*
ID: jamerz1
PROG: hidden
LANG: C++11
*/

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
typedef unsigned int uint;
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

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;


int L;

void fix(vi& I, int& sz) {
	int longest = 1;
	int curr = 1;
	int idx = 0;
	while (idx < I.size()-1) {
		if (I[idx + 1] - I[idx] <= sz) {
			curr++;
		}
		else {
			longest = max(longest, curr);
			curr = 1;
		}
		++idx;
	}
	longest = max(longest, curr);

	if (longest > 1) {
		idx = 0;
		curr = 1;
		vi newI;
		while (idx < I.size() - 1) {
			if (I[idx + 1] - I[idx] <= sz) {
				curr++;
			}
			else {
				if (curr == longest)
					newI.push_back(I[idx]);
				curr = 1;
			}
			++idx;
		}
		if (curr == longest)
			newI.push_back(I[idx]);

		I = newI;
	}
	sz = sz * longest;
}

int main() {
	ifstream fin("hidden.in");
	ofstream fout("hidden.out");
	fin >> L;
	string line(L,' ');
	for (int i= 0; i < L; ++i)
		fin >> line[i];
	line.insert(line.end(), line.begin(), line.end());
	int sz = 0;
	vi I;
	for (int i = 0; i < line.size(); ++i)
		I.push_back(i);
	while (sz < L && I.size()>1) {
		fix(I, sz);
		if (I.size() == 1)
			break;
		char minc = 'z';
		for (int i : I)
			minc = min(line[i], minc);
		vi newI;
		for (int i : I) {
			if (line[i%L] == minc && i + 1 < 2 * L)
				newI.push_back(i + 1);
		}
		I = newI;
		++sz;
	}
	int res = I[0] - sz;
	if (res < 0)
		res += L;
	else
		res %= L;
	fout << res << '\n';
	return 0;
}