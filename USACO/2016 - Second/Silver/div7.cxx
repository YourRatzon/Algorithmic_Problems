#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

/*
ID: jamerz1
PROG: angry
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
#define M_PI 3.14159265358979323846


int main() {

	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("div7.in");
	ofstream fout("div7.out");

	int N;
	fin >> N;
	vector<int> cow_ids(N);
	vector<vector<int>> DP(N, vector<int>(7, 0));
	for (int i = 0; i < N; ++i) {
		fin >> cow_ids[i];
	}
	for (int j = 0; j < 7; ++j) {
		DP[0][j] = (((cow_ids[0] + j) % 7) == 0);
	}
	for (int i = 1; i < N; ++i) {
		for (int j = 0; j < 7; ++j) {
			int prev_col = (cow_ids[i] + j) % 7;
			if (DP[i - 1][prev_col] > 0)
				DP[i][j] = DP[i - 1][prev_col] + 1;
			else if (prev_col == 0)
				DP[i][j] = 1;
		}
	}

	int best_res = 0;
	for (int i = 0; i < N; ++i) {
		best_res = max(best_res, DP[i][0]);
	}

	fout << best_res << '\n';
	fin.close();
	fout.close();


	//print_timer();
	return 0;
}