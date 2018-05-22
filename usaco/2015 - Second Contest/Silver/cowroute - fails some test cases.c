#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
/*
ID: jamerz1
PROG: cowroute
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

const unsigned int MAX_CITIES = 1001;
ull INF = 1e19;
struct triple {
	int v;
	long long w;
	int route;
};

vector<vector<triple>> graph(MAX_CITIES, vector<triple>());

bool operator>(const triple& a, const triple& b) {
	return a.w < b.w;
}

int main()
{
	ifstream fin("cowroute.in");
	int A,B,N;
	fin >> A>>B >>N;
	int u, v,cities;
	ull w;
	for (int i = 0; i < N; ++i) {
		fin >> w >> cities;
		fin >> u;
		for (int j = 0; j < cities-1; ++j) {
			fin >> v;
			graph[u].push_back({ v, w, i });
			u = v;
		}
	}
	
	vector<ull> dist(MAX_CITIES, INF);
	dist[A] = 0;
	vi path_length(MAX_CITIES, 0);
	path_length[A] = 0;

	priority_queue<triple, vector<triple>, greater<triple>> pq;
	pq.push({ A, 0, -1 });
	while (!pq.empty()) {
		triple front = pq.top();
		pq.pop();
		int d = front.w;
		int u = front.v;
		int curr_route = front.route;
		if (d == dist[u]) {
			for (int j = 0; j < graph[u].size(); ++j) {
				triple v = graph[u][j];
				if (v.route == curr_route)
					v.w = 0;
				if (dist[u] + v.w < dist[v.v]) { // relax 
					dist[v.v] = dist[u] + v.w;
					path_length[v.v] = path_length[u] + 1;
					pq.push({ v.v, dist[v.v], v.route });
				}
			}
		}
	}

	ofstream fout("cowroute.out");
	if (dist[B] == INF)
		fout << "-1 -1\n";
	else
		fout << dist[B] << ' ' << path_length[B] << '\n';
	fout.close();
	return 0;
}