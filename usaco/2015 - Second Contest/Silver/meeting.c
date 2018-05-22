#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
/*
ID: jamerz1
PROG: meeting
LANG: C++11
*/

// C++11
#include <tuple>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <array>

// C++03
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

#include <iostream>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const unsigned int MAX_V = 101;
const unsigned int MAX_T = 10001;


vector<vii> BessieGraph;
vector<vii> ElsieGraph;
bool DPb[MAX_V][MAX_T];
bool DPe[MAX_V][MAX_T];

int main()
{
	int N, M;

	ifstream fin("meeting.in");
	fin >> N >> M;
	ofstream fout("meeting.out");

	if (N == 1) {
		fout << 0 << '\n';
		return 0;
	}

	BessieGraph.resize(N + 1);
	ElsieGraph.resize(N + 1);
	int u, v, wB, wE;
	for (int i = 0; i < M; ++i) {
		fin >> u >> v >> wB >> wE;
		BessieGraph[u].push_back({ v, wB });
		ElsieGraph[u].push_back({ v, wE });
	}
	fin.close();

	memset(DPb, 0, MAX_T * MAX_V * sizeof(bool));
	memset(DPe, 0, MAX_T * MAX_V * sizeof(bool));
	DPb[1][0] = true;
	DPe[1][0] = true;

	for (int u = 1; u <= N; ++u) {
		for (int t = 0; t < MAX_T; ++t)
		{
			if (DPb[u][t]) {
				for (int i = 0; i < BessieGraph[u].size(); ++i) {
					ii v = BessieGraph[u][i];
					DPb[v.first][t + v.second] = true;
				}
			}
			if (DPe[u][t]) {
				for (int i = 0; i < ElsieGraph[u].size(); ++i) {
					ii v = ElsieGraph[u][i];
					DPe[v.first][t + v.second] = true;

				}
			}
		}
	}
	for (int i = 0; i < MAX_T; ++i) {
		if (DPb[N][i] && DPe[N][i]){
			fout << i << '\n';
			fout.close();

			return 0;
		}
	}
	fout << "IMPOSSIBLE\n";
	fout.close();
	return 0;
}