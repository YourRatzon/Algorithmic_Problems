#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

/*
ID: jamerz1
PROG: tour
LANG: C++11
*/

// C++11
#include <tuple>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <array>
#include <iterator>

// C++03
#include <assert.h>
#include <climits>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <queue>
#include <math.h>
#include <map>
#include <cstdio>
#include <ctime>
#include <list>
#include <set>
#include <stdio.h>
#include <bitset>
#include <functional> 
#include <locale>
#include <vector>
#include <streambuf>
#include <ctime>

#include <iostream>


//#define F first
//#define S second

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;

// fast input
#define scan_fast(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

// TIMER
std::clock_t start;
double duration;
void start_timer() { start = std::clock(); }
void print_timer() {
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << '\n';
}
// END TIMER

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

double EPS = 1e-10;
double PI = cos(-1);
const int INF = int(2e9);
#define M_PI       3.14159265358979323846


ii operator+(const ii& lhs, const ii& rhs) {
	return{ lhs.first + rhs.first, lhs.second + rhs.second };
}

map < char, ii > moves {
	{'N', {0,1}}, { 'S', {0,-1} }, { 'W', {-1,0} }, { 'E', {1,0} }
};

vector<vector<int>> DP;
int n_farmer, n_bessie;

vector<ii> farmer;
vector<ii> bessie;

int dist_sq(int f, int b) {
	int delta_x = (farmer[f].first - bessie[b].first);
	int delta_y = (farmer[f].second - bessie[b].second);
	return delta_x*delta_x + delta_y*delta_y;
}
int solve(int x, int y) {

	if (x >= n_farmer || y >= n_bessie)
		return INF;

	int bessie_goes = INF;
	int farmer_goes = INF;
	int both_go = INF;

	if (y + 1 < n_bessie&&DP[x][y + 1] == -1)
		solve(x, y + 1);
	if (y + 1 < n_bessie)
		bessie_goes = DP[x][y + 1] + dist_sq(x, y + 1);
	
	if (x + 1 < n_farmer&&DP[x + 1][y] == -1)
		solve(x + 1, y);
	if (x + 1 < n_farmer)
		farmer_goes = DP[x + 1][y] + dist_sq(x + 1, y);

	
	if (x + 1 < n_farmer&&y + 1 < n_bessie&&DP[x + 1][y + 1] == -1)
		solve(x + 1, y + 1);
	if (x + 1 < n_farmer&&y + 1 < n_bessie)
		both_go = DP[x + 1][y + 1] + dist_sq(x + 1, y + 1);

	

	DP[x][y] = min(farmer_goes, min(bessie_goes, both_go));
	return DP[x][y];
}

int main() {

	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("radio.in");
	ofstream fout("radio.out");

	fin >> n_farmer >> n_bessie;
	n_farmer++;
	n_bessie++;
	farmer.resize(n_farmer);
	bessie.resize(n_bessie);

	int Fx, Fy, Bx, By;
	fin >> Fx >> Fy >> Bx >> By;
	farmer[0] = { Fx, Fy };
	bessie[0] = { Bx, By };
	// build paths;
	string farmer_path;
	fin >> farmer_path;
	for (int i = 0; i < farmer_path.size(); ++i) {
		ii next_move = moves[farmer_path[i]];
		ii next_spot = farmer[i] + next_move;
		farmer[i + 1] = next_spot;
	}
	string bessie_path;
	fin >> bessie_path;
	for (int i = 0; i < bessie_path.size(); ++i) {
		ii next_move = moves[bessie_path[i]];
		ii next_spot = bessie[i] + next_move;
		bessie[i + 1] = next_spot;
	}

	DP.assign(n_farmer, vector<int>(n_bessie, -1));

	DP[n_farmer - 1][n_bessie - 1] = 0;
	//for (int r = 0; r < n_farmer; ++r) {
	//	int d = dist_sq(r, n_bessie - 1);
	//	DP[r][n_bessie - 1] = d;
	//}
	//for (int c = 0; c < n_bessie; ++c) {
	//	int d = dist_sq(n_farmer - 1, c);
	//	DP[n_farmer - 1][c] = d;
	//}

	solve(0, 0);

	fin.close();
	fout << DP[0][0] << '\n';
	fout.close();


	//print_timer();
	return 0;
}