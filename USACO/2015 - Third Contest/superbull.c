#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
/*
ID: jamerz1
PROG: superbull
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

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	

	ifstream fin("superbull.in");
	int N;
	fin >> N;
	AdjMatrix.assign(N, vi(N, 0));
	vi teams(N);
	for (int i = 0; i < N; ++i) {
		fin >> teams[i];
	}
	fin.close();

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i == j) continue;
			AdjMatrix[i][j] = teams[i] ^ teams[j];
		}
	}
	
	vector<bool> in_tree(N, false);
	vector<int> distance(N, 0);
	vector<int> source(N, 0);
	in_tree[0] = true;
	int tree_size = 1;
	int tree_cost = 0;
	for (int i = 0; i < N; ++i) {
		distance[i] = AdjMatrix[0][i];
	}
	while (tree_size < N) {
		int max_dist = 0, max_node = 0;
		for (int i = 0; i < N; ++i) {
			if (!in_tree[i] && distance[i]>max_dist) {
				max_dist = distance[i];
				max_node = i;
			}
		}
		tree_cost += distance[max_node];
		in_tree[max_node] = true;
		tree_size++;
		for (int i = 0; i < N; ++i) {
			if (AdjMatrix[max_node][i] > distance[i]) {
				distance[i] = AdjMatrix[max_node][i];
				source[i] = max_node;
			}
		}
	}
	ofstream fout("superbull.out");
	fout << tree_cost<< '\n';
	fout.close();
	return 0;
}