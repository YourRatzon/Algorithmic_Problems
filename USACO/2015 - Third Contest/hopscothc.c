#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
/*
ID: jamerz1
PROG: hopscotch
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
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const int INF = LONG_MAX;

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

const int MAX_N = 1e6 + 1;

vector<vi> AdjMatrix;
int MOD = 1000000007;

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	ifstream fin("hopscotch.in");
	int rows, cols, max_val;
	fin >> rows >> cols >> max_val;
	vector<vi> G(rows, vi(cols));
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			fin >> G[i][j];
		}
	}

	vector<vi> DP(rows, vi(cols, 0));
	for (int i = 0; i < rows; ++i) {
		DP[i][cols - 1] = 0;
	}
	for (int j = 0; j < cols; ++j) {
		DP[rows-1][j] = 0;
	}

	for (int r = rows - 2; r >= 0; --r) {
		for (int c = 0; c < cols - 1; ++c) {
			if (r == 0 && c > 0) // no need to get top row since cant go there
				break;
			DP[r][c] = (G[r][c] != G[rows - 1][cols - 1]);
			for (int r_below = r + 1; r_below < rows - 1; ++r_below) {
				for (int c_right = c + 1; c_right < cols - 1; ++c_right) {
					if (G[r][c] != G[r_below][c_right]) {
						DP[r][c] += DP[r_below][c_right];
						DP[r][c] %= MOD;
					}
				}
			}
		}
	}

	ofstream fout("hopscotch.out");
	fout << DP[0][0] % MOD << '\n';
	fout.close();
	return 0;
}