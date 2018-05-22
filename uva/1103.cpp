#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
/*
ID: jamerz1
PROG: rockers
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
typedef vector<ull> vull;
typedef vector<ll> vll;


template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

const int MAX_N = 501;
const double INF = 2e9;

vector<vector<bool>> picture;
vector<vector<bool>> blank;

vector<vector<bool>> visited;
int rows, hex_cols, cols;
vii moves = { {1,0} , {-1,0} , {0,1} , {0,-1} };
void DFS(int r, int c) {
	stack<ii> st;
	st.push({ r, c });
	while (!st.empty()) {
		ii p = st.top();
		st.pop();
		r = p.first;
		c = p.second;
		blank[r][c] = true;
		visited[r][c] = true;
		int new_r, new_c;
		for (int i = 0; i < moves.size(); ++i) {
			new_r = r + moves[i].first;
			new_c = c + moves[i].second;
			if (new_r >= 0 && new_r < rows && new_c >= 0 && new_c < cols) {
				if (!visited[new_r][new_c] && picture[new_r][new_c] == true)
					st.push({ new_r, new_c });
			}
		}
	}
}

void DFS2(int r, int c) {

	stack<ii> st;
	st.push({ r, c });
	while (!st.empty()) {
		ii p = st.top();
		st.pop();
		r = p.first;
		c = p.second;
		blank[r][c] = true;
		int new_r, new_c;
		for (int i = 0; i < moves.size(); ++i) {
			new_r = r + moves[i].first;
			new_c = c + moves[i].second;
			if (new_r >= 0 && new_r < rows+2 && new_c >= 0 && new_c < cols+2) {
				if (!blank[new_r][new_c])
					st.push({ new_r, new_c });
			}
		}
	}
}

// A (Ankh):   2
// J (Wedjat): 4
// D (Djed):   6
// S (Scarab): 5
// W (Was):    1
// K (Akhet):  3

std::unordered_map<int, char> CC_to_code = { { 2, 'A' }, { 4, 'J' }, { 6, 'D' }, { 5, 'S' }, { 1, 'W' }, { 3, 'K' } };



int CC_count = 0;

int main(int argc, char *argv[]) {
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	//ofstream fout("egypt.out");

	string line;
	unsigned int x;
	std::stringstream ss;
	int t = 1;

	while (cin >> rows >> hex_cols) {
		if (rows == 0)
			break;

		cols = hex_cols * 4;
		picture.assign(rows, vector<bool>(cols));
		visited.assign(rows, vector<bool>(cols, false));

		for (int r = 0; r < rows; ++r) {
			cin >> line;
			for (int c = 0; c < hex_cols; ++c) {
				ss << std::hex << line[c];
				ss >> x;
				ss.clear();
				bitset<4> bs(x);
				for (int i = 0; i < 4; ++i)
					picture[r][4 * c + i] = bs[3-i];
			}
		}
		string res = "";
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				if (!visited[r][c] && picture[r][c] == true) {
					// found a hieroglyph edge
					blank.assign(rows, vector<bool>(cols, false));
					DFS(r,c);
					// blank now contains hieroglyph
					// insert white border all around
					for (int i = 0; i < rows; ++i) {
						blank[i].insert(blank[i].begin(), false);
						blank[i].push_back(false);
					}
					blank.insert(blank.begin(), vector<bool>(cols+2, false));
					blank.insert(blank.end(), vector<bool>(cols+2, false));

					CC_count = 0;
					for (int r2 = 0; r2 < rows+2; ++r2) {
						for (int c2 = 0; c2 < cols+2; ++c2) {
							if (!blank[r2][c2]) {
								CC_count++;
								DFS2(r2, c2);
							}
						}
					}
					if (CC_count == 0)
						CC_count = 1;
					res.push_back(CC_to_code[CC_count]);
				}
			}
		}
		sort(res.begin(), res.end());
		
		cout <<"Case " << t << ": " <<res << '\n';
		
		//fout << "Case " << t << ": " << res << '\n';

		++t;
	}
	//fout.close();

	return 0;

}
