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

const int MAX_N = 1005;

struct Cell {
	Cell() :
		N(false), S(false), W(false), E(false) {}
	bool N, S, W, E;
};

vector<ii> moves = { { -1, 0 } , { 1, 0 }, { 0, -1 } , { 0, 1 } };

ii operator+(const ii& lhs, const ii&rhs) {
	return{ lhs.first + rhs.first, lhs.second + rhs.second };
}

vector<vector<int>> graph;
vector<vector<Cell>> farm;
vector<vector<bool>> visited;

ii make_move(ii curr_pt, char move) {
	int row = curr_pt.first;
	int col = curr_pt.second;
	switch (move) {
	case 'N':
		farm[row][col].E = true;
		farm[row][col + 1].W = true;
		row--;
		break;
	case 'S':
		farm[row + 1][col].E = true;
		farm[row + 1][col + 1].W = true;
		row++;
		break;
	case 'W':
		farm[row][col].S = true;
		farm[row + 1][col].N = true;
		col--;
		break;
	case 'E':
		farm[row][col + 1].S = true;
		farm[row + 1][col + 1].N = true;
		col++;
		break;
	default:
		break;
	}
	return{ row, col };
}

ii translate(int x, int y) {
	return{ x + MAX_N, y + MAX_N };
}

bool legal_move(int r, int c) {
	return r >= 0 && r <= MAX_N * 2 && c >= 0 && c <= MAX_N * 2;
}

bool wall(int r, int c, int new_r, int new_c) {
	if (r > new_r) // north
		return farm[r][c].N;
	else if (r < new_r) //south
		return farm[r][c].S;
	else if (c > new_c) // west
		return farm[r][c].W;
	else // east
		return farm[r][c].E;
}

void DFS(int i, int j) {
	stack<ii> st;
	
	visited[i][j] = true;
	st.push({ i, j });
	int r, c;
	while (!st.empty()) {
		ii v = st.top();
		st.pop();
		r = v.first;
		c = v.second;
		for (int i = 0; i < moves.size(); ++i) {
			int new_r = moves[i].first + r;
			int new_c = moves[i].second + c;
			if (legal_move(new_r, new_c) && !visited[new_r][new_c] &&
				!wall(r, c, new_r, new_c)) {
				visited[new_r][new_c] = true;
				st.push({ new_r, new_c });
			}
		}
	}
}
int main() {

	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("gates.in");
	ofstream fout("gates.out");

	graph.assign(MAX_N*2+1, vector<int>(MAX_N*2+1));
	farm.assign(MAX_N * 2 + 1, vector<Cell>(MAX_N * 2 + 1, Cell()));

	int N;
	fin >> N;
	ii curr_pt = translate(0,0);
	char move;
	for (int i = 0; i < N; ++i) {
		fin >> move;
		curr_pt = make_move(curr_pt, move);
	}


	visited.assign(MAX_N * 2 + 1, vector<bool>(MAX_N * 2 + 1, false));
	int CC_count = 0;
	for (int r = 0; r <= MAX_N * 2; ++r) {
		for (int c = 0; c <= MAX_N * 2; ++c) {
			if (!visited[r][c]) {
				DFS(r, c);
				CC_count++;
			}
		}
	}

	fout << CC_count - 1 << '\n';
	fin.close();
	fout.close();


	//print_timer();
	return 0;
}