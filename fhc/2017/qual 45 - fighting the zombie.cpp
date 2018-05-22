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
const int MAX_N = 1000 + 5;
struct Spell {
	Spell(const string& spell) {
		Z = 0;
		istringstream ss(spell);
		ss >> num;
		ss.get();
		ss >> sides;
		if (!ss.eof()) {
			ss >> Z;
		}
	}

	Spell() : sides(0), num(0), Z(0) {}
	int sides;
	int num;
	int Z;
};

const int MAX_H = 450;
long double DP[22][22][MAX_H];
long double solve(int sides, int num, int h) {
	if (h >= MAX_H)
		return 0.0;
	if (h < 0)
		return 1.0;
	if (DP[sides][num][h] != -1)
		return DP[sides][num][h];
	if (h == 0){
		DP[sides][num][h] = 1.0;
		return DP[sides][num][h];
	}
	if (num == 1) {
		DP[sides][num][h] = max(0.0l, long double(sides - h + 1) / long double(sides));
		return DP[sides][num][h];
	}
	long double res = 0.0;
	for (int i = 1; i <= sides; ++i) {
		res += solve(sides, num - 1, h - i) / long double(sides);
	}
	return DP[sides][num][h] = res;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	
	//ifstream fin("fightingthezombie.in");
	ifstream fin("c.in");
	ofstream fout("c.out");
	
	for (int i = 0; i < 22; ++i)
		for (int j = 0; j < 22; ++j)
			for (int k = 0; k < MAX_H; ++k)
				DP[i][j][k] = -1;

	int T;
	fin >> T;
	for (int t = 1; t <= T; ++t) {
		int H,S;
		fin >> H>>S;
		string line;
		long double best_res = 0.0;
		for (int i = 0; i < S; ++i) {
			fin >> line;
			Spell curr(line);
			long double curr_res = solve(curr.sides, curr.num, H-curr.Z);
			best_res = max(curr_res, best_res);
		}
	
		fout << "Case #"<<t<<": "<<fixed<<setprecision(6)<<best_res<< '\n';
	}
	return 0;
}