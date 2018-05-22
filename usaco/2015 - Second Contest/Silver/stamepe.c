#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
/*
ID: jamerz1
PROG: stampede
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

const unsigned int MAX_COWS = 50001;
const unsigned int MAX_W = 2 * 38 + 2;

struct triple {
	int x, y;
	double speed;
};
struct point {
	int y;
	double time;
	bool type;
};

bool cow_comp(triple lhs, triple rhs) {
	return lhs.y < rhs.y;
}
bool my_comp(point lhs, point rhs){
	if (lhs.time == rhs.time) {
			return lhs.y < rhs.y;
	}
	return lhs.time < rhs.time;
}

int main()
{
	ifstream fin("stampede.in");
	int N;
	fin >> N;
	vector<triple> cows(N);
	int x, y;
	for (int i = 0; i < N; ++i) {
		fin >> cows[i].x >> cows[i].y >> cows[i].speed;
	}
	std::unordered_map<int, int> y_cow_map;
	std::unordered_map<int, bool> seen_cows;
	vector<point> times;
	// get (y,start_time) pairs
	for (int i = 0; i < N; ++i) {
		double start_time = double(-1 * (cows[i].x + 1)) * cows[i].speed;
		double end_time = start_time + cows[i].speed;
		times.push_back({ cows[i].y, start_time, 1 });
		times.push_back({ cows[i].y, end_time, 0 });
	}

	sort(times.begin(), times.end(), my_comp);
	set<int> seen;
	set<int> active;
	for (int i = 0; i < times.size(); ) {
		int j;
		for (j = i; j < times.size() && times[i].time == times[j].time;++j) {
			if (times[j].type == 1)
				active.insert(times[j].y);
			else
				active.erase(times[j].y);
		}
		if (!active.empty())
			seen.insert(*active.begin());
		i = j;
	}
	ofstream fout("stampede.out");
	fout << seen.size() << '\n';
	fout.close();
	return 0;
}