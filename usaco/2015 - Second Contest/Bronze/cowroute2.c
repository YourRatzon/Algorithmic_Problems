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

const unsigned int MAX_COST = 1010;

int main()
{
	ifstream fin("cowroute.in");
	int A, B, N;
	fin >> A >> B >> N;
	int curr_cost, curr_m, temp;
	vector<vi> routes(N);
	vi prices(N);
	for (int i = 0; i < N; ++i) {
		fin >> curr_cost >> curr_m;
		routes[i] = vector<int>(curr_m);
		prices[i] = curr_cost;
		for (int j = 0; j < curr_m; ++j) {
			fin >> routes[i][j];
		}
	}

	int min_cost = MAX_COST;
	for (int i = 0; i < N; ++i) {
		int j = 0;
		while (j < routes[i].size()-1 && routes[i][j] != A)
			j++;
		if (j == routes[i].size() - 1) continue;
		unordered_set<int> stops;
		bool b = false;
		//currently, routes[i][j] == A, so need to increment j
		j++;
		for (; j < routes[i].size(); ++j) {
			//load up the hash with the stops following A in route[i]
			stops.insert(routes[i][j]);
			if (routes[i][j] == B) b = true;
		}
		if (b) min_cost = min(min_cost, prices[i]);
		for (int j = 0; j < N; ++j) {
			if (j == i) continue;
			int k = routes[j].size() - 1;
			while (k >= 1 && routes[j][k] != B) 
				--k;
			if (k == 0) continue;
			//currently, routes[j][k] == B, so need to decrement
			--k;
			for (; k >= 0; --k) {
				if (stops.find(routes[j][k]) != stops.end()) {
					min_cost = min(min_cost, prices[i]+prices[j]);
					break;
				}
			}
			
		}
	}

	ofstream fout("cowroute.out");
	if (min_cost == MAX_COST)
		min_cost = -1;
	fout << min_cost << '\n';

	return 0;
}