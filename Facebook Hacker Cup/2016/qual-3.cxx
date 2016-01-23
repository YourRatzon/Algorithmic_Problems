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
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
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
bool eq(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);

vector<vector<char>> grid;
int T, N;

void fill(int row, int col) {
	int idx = col;
	while (idx >= 0 && grid[row][idx] == '.') {
		grid[row][idx] = 'X';
		--idx;
	}
	idx = col + 1;
	while (idx < N && grid[row][idx] == '.') {
		grid[row][idx] = 'X';
		++idx;
	}
}

int main(int argc, char *argv[]) {
	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("high_security_example_input.txt");
	ofstream fout("high_security_example_output.txt");
	fin >> T;
	for (int t = 0; t < T; ++t){
		fin >> N;
		grid.assign(2, vector<char>(N));
		for (int row = 0; row < 2; ++row) {
			for (int i = 0; i < N; ++i) {
				fin >> grid[row][i];
			}
		}
		int res = 0;
		if (N == 1) {
			if (grid[0][0] == 'X' && grid[1][0] == 'X')
				res = 0;
			else
				res = 1;
			fout << "Case #" << t + 1 << ": " << res << '\n';
			continue;
		}

		//deal with first col    
		if (grid[0][0] == '.'&&grid[0][1] == 'X') {
			// top row begins with .X
			if (grid[1][0] == '.')
				fill(1, 0);
			grid[0][0] = 'X';
			res++;
		}
		else if (grid[1][0] == '.'&&grid[1][1] == 'X') {
			// bottom row begins with .X
			if (grid[0][0] == '.')
				fill(0, 0);
			grid[1][0] = 'X';
			res++;
		}

		// deal with last col
		if (grid[0][N-1] == '.' && grid[0][N-2] == 'X') {
			// top row ends with "X."
			if (grid[1][N-1] == '.')
				fill(1, N-1);
			grid[0][N-1] = 'X';
			res++;
		}
		else if (grid[1][N-1] == '.' && grid[1][N-2] == 'X') {
			// bottom row ends with "X."
			if (grid[0][N-1] == '.')
				fill(0, N-1);
			grid[1][N-1] = 'X';
			res++;
		}

		//deal with the rest of columns
		for (int i = 1; i < N-1; ++i) {
			if (grid[0][i] =='.' &&grid[0][i - 1] =='X' && grid[0][i + 1] =='X')
			{ // X.X on top row
				if (grid[1][i] == '.')
					fill(1, i);
				grid[0][i] = 'X';
				res++;
			}
			else if (grid[1][i] == '.' &&
					 grid[1][i - 1] == 'X' && 
					 grid[1][i + 1] == 'X') 
			{ // X.X on bottom row
				if (grid[0][i] == '.')
					fill(0, i);
				grid[1][i] = 'X';
				res++;
			}
		}

		// now place guards on wherever still needed
		for (int i = 0; i < N; ++i) {
			if (grid[0][i] == '.') {
				fill(0, i);
				grid[1][i] = 'X';
				res++;
			}
			if (grid[1][i] == '.') {
				fill(1, i);
				grid[0][i] = 'X';
				res++;
			}
		}
		fout << "Case #" << t + 1 << ": " << res << '\n';
	}

	fin.close();
	fout.close();

	//print_timer();
	return 0;
}