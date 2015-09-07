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
	ifstream fin("crosswords.in");
	ofstream fout("crosswords.out");

	int N, M;
	char in;
	fin >> N >> M;
	CW.resize(N);
	for (int i = 0; i < N; ++i)
	{
		CW[i].resize(M);
		for (int j = 0; j < M; ++j)
		{
			fin >> in;
			if (in == '.')
				CW[i][j] = true;
			else
				CW[i][j] = false;
		}
	}
	
	vii clues;
	int count = 0;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			// vert
			if (i > 0 && i + 2 < N) {
				if (!CW[i - 1][j] && CW[i][j] && CW[i + 1][j] && CW[i + 2][j]){
					clues.push_back({ i, j });
					count++;
					continue;
				}
			}
			else if (i + 2 < N) {
				if (CW[i][j] && CW[i + 1][j] && CW[i + 2][j]){
					clues.push_back( { i, j } );
					count++;
					continue;
				}
			}
			// horiz
			if (j > 0 && j + 2 < M) {
				if (!CW[i][j - 1] & CW[i][j] && CW[i][j + 1] && CW[i][j + 2]){
					clues.push_back({ i, j });
					count++;
					continue;
				}
			}
			else if (j + 2 < M){
				if (CW[i][j] && CW[i][j + 1]  && CW[i][j + 2]){
					clues.push_back({ i, j });
					count++;
					continue;
				}
			}
		}
	}
	fout << count << '\n';
	for (auto p : clues)
	{
		fout << p.first + 1 << ' ' << p.second+ 1 << '\n';
	}

	return 0;
}
