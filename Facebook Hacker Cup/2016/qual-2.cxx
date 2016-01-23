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

vector<vector<char>> adj_matrix;
vector<vector<bool>> visited;
int rows, cols;
vector<ii> moves = { {1,0}, {-1,0}, {0,1}, {0, -1} };

bool LegalMove(int r, int c) {
	return (r >= 0 && r < rows && c >= 0 && c < cols);
}

int DFS(int r, int c, vii& curr_cc_out) {
	visited[r][c] = true;
	int cc_size = 0;
	for (int i = 0; i < moves.size(); ++i) {
		int new_r = r+moves[i].first;
		int new_c = c+moves[i].second;
		if (LegalMove(new_r, new_c) && adj_matrix[new_r][new_c] != '*' && !visited[new_r][new_c]) {
			cc_size += DFS(new_r, new_c, curr_cc_out);
		}
	}
	curr_cc_out.push_back({ r, c });
	return cc_size + 1;
}

int main(int argc, char *argv[]) {
	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("fb2.in");
	ofstream fout("fb2.out");
	int T, N, P;
	vector<int> prices;
	fin >> T;
	for (int t = 0; t < T; ++t) {
		fin >> N >> P;
		prices.resize(N);
		for (int i = 0; i < N; ++i)
			fin >> prices[i];
		ll res = 0;
		ll curr_sum = 0;
		int left = 0;
		for (int right = 0; right < N; ++right) {
			curr_sum += prices[right];
			while (left <= right && curr_sum > P){
				curr_sum -= prices[left];
				left++;
			}
			res += (right - left + 1);
		}
		fout << "Case #" << t + 1 << ": " << res << '\n';
	}
	//print_timer();
	return 0;
}