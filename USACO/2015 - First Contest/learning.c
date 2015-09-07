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
	ifstream fin("learning.in");
	ofstream fout("learning.out");

	int N, A, B;
	fin >> N >> A >> B;
	map<int, pair<int,bool>> cows;
	vector<pair<int, bool>> cows1(N);
	string spots;
	int weight;
	for (int i = 0; i < N; ++i)
	{
		fin >> spots >> weight;
		if (spots == "S")
			cows1[i] = { weight, true };
		else
			cows1[i] = { weight, false };
	}
	sort(cows1.begin(), cows1.end());
	for (int i = 0; i < N; ++i)
		cows[i] = cows1[i];

	int total = 0;
	int l_dist, r_dist;
	
	// Take care of all new cows < cow[0];
	if (cows[0].first > A) {
		if (cows[0].second)//the first cow is >= A and is spotted, so is A.
		{
			total += min(cows[0].first - A, B - A + 1);
		}
		A += min(cows[0].first - A, B - A + 1);
	}

	// deal with new cows >= cow[0]
	// at each iteration we'll deal with new cows in range: [cow[i], cow[i+1)
		for (int i = 1; i < N && A<=B; )
		{
			if (cows[i].first < A)
				continue;
		
			int mid = (cows[i].first + cows[i - 1].first) / 2;
			l_dist = A - cows[i - 1].first;
			r_dist = cows[i].first - A;
			if (l_dist < r_dist){
				if (cows[i - 1].second){
					total += min(mid - A + 1, B - A + 1);
					A += min(mid - A + 1, B - A + 1);
				}
				else {
					A += min(mid - A, B - A + 1);
				}
				if (A > cows[i].first) i++;
				continue;
			}
			else if (r_dist < l_dist){
				if (cows[i].second){
					total += min(cows[i].first - A + 1, B - A + 1);
				}
				A += min(cows[i].first - A + 1, B - A + 1);
				if (A > cows[i].first) i++;
				continue;

			}
			else if (r_dist == l_dist) {
				if(cows[i].second || cows[i - 1].second)
					total += min(cows[i].first - A + 1, B - A + 1);
				A += min(cows[i].first - A + 1, B - A + 1);
				if (A > cows[i].first) i++;
				continue;
			}
		}
	//deal with new cows > heaviest old cow (cows[N-1])
	if (A <= B)
	{
		if (cows[N - 1].second)
		{
			total += B - A + 1;
		}
	}
	fout << total << '\n';

	return 0;
}
