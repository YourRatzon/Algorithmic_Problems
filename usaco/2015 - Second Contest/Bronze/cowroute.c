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
	int min_cost = MAX_COST;
	int curr_cost, curr_m, temp;
	
	for (int i = 0; i < N; ++i) {
		bool a = false, b = false;
		fin >> curr_cost >> curr_m;
		for (int j = 0; j < curr_m; ++j) {
			fin >> temp;
			if (!a && temp == A)
				a = true;
			else if (a && temp == B) {
				b = true;
			}
		}
		if (a && b)
			min_cost = min(min_cost, curr_cost);
	}
	ofstream fout("cowroute.out");
	if (min_cost == MAX_COST)
		min_cost = -1;
	fout << min_cost << '\n';

	return 0;
}