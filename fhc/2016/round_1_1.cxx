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


int T, N;

int solve(vector<int>& values) {
	int idx = 0;
	int res = 0;
	while (idx < N) {
		int last_val = values[idx];
		++idx;
		int curr_contest_n_problems = 1;
		while (idx < N && curr_contest_n_problems < 4) {
			if (values[idx] - last_val <= 0) { // next num is <= curr
				res += 4 - curr_contest_n_problems;
				break;
			}
			else if (values[idx] - last_val <= 10) {
				last_val = values[idx];
				++idx;
				curr_contest_n_problems++;
			}
			else if (values[idx] - last_val > 10) {
				last_val += 10;
				res++;
				curr_contest_n_problems++;
			}
		}
		if (idx == N)
			res += 4 - curr_contest_n_problems;
	}
	return res;
}

int main() {
	
	start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("coding_contest_creation.txt");

	fin >> T;
	ofstream fout("coding_contest.out");
	vector<int> values;
	for (int t = 0; t < T; ++t) {
		fin >> N;
		values.resize(N);
		for (int i = 0; i < N; ++i)
			fin >> values[i];

		int res = solve(values);
		fout << "Case #" << t + 1 << ": " << res << '\n';
	}
	

	fin.close();
	fout.close();


	print_timer();
	return 0;
}