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


vector<vector<bool>> CW;

int main()
{
	ifstream fin("cowjog.in");
	ofstream fout("cowjog.out");

	int N;
	fin >> N;
	int temp;
	vi speeds(N);
	for (int i = 0; i < N; ++i)
	{
		fin >> temp >> speeds[i];
	}
	vi mins;
	mins.push_back(speeds[N - 1]);
	int mins_i = 0;

	for (int i = N - 2; i >= 0; --i)
	{
		if (speeds[i] > mins[mins_i]){
			continue;
		}
		else if (speeds[i] <= mins[mins_i]){
			mins.push_back(speeds[i]);
			mins_i++;
		}
	}
	fout << mins_i + 1 << '\n';
	return 0;
}
