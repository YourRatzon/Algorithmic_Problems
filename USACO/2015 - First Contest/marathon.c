#define _CRT_SECURE_NO_WARNINGS

/*
ID: jamerz1
PROG: packrec
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
#include <math.h>
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
typedef pair<int,  int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const unsigned int MAX = 21;


vii points;
vii T;
vi res;

ll dist_cont(int from, int to)
{
	ll total = 0;
	for (int i = from; i < to; ++i)
	{
		total += abs(points[i].first - points[i + 1].first) +
			abs(points[i].second - points[i + 1].second);
	}
	return total;
}

ll dist_two(int from, int to)
{
	return abs(points[from].first - points[to].first) +
		abs(points[from].second - points[to].second);
}

int main()
{
	ifstream fin("marathon.in");
	ofstream fout("marathon.out");

	int N; 
	fin >> N;
	points.resize(N);
	for (int i = 0; i < N; ++i)
	{
		fin >> points[i].first >> points[i].second;
	}

	T.resize(N - 2);
	res.resize(N - 2);

	T[0].first = 0;
	T[0].second =  dist_cont(2, N-1);
	res[0] = T[0].first + T[0].second + dist_two(0, 2);
	int result = res[0];

	for (int k = 1; k <= N - 3; ++k)
	{
		T[k].first = T[k - 1].first + dist_two(k - 1, k);
		T[k].second = T[k - 1].second - dist_two(k + 1, k+2);
		res[k] = T[k].first + T[k].second + dist_two(k, k + 2);
		result = min(result, res[k]);
	}
	fout << result << '\n';
	
	return 0;
}
