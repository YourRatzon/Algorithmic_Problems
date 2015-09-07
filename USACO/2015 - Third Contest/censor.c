#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
/*
ID: jamerz1
PROG: censor
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
string S, T;
int n, m, b[MAX_N];

void kmpPreprocess() { // call this before calling kmpSearch()
	int i = 0, j = -1; b[0] = -1; // starting values
	while (i < m) { // pre-process the pattern string P
		while (j >= 0 && T[i] != T[j]) j = b[j]; // if different, reset j using b
		i++; j++; // if same, advance both pointers
		b[i] = j; // observe i = 8, 9, 10, 11, 12 with j = 0, 1, 2, 3, 4
	}
}

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	

	ifstream fin("censor.in");
	fin >> S >> T;
	fin.close();
	//kmpPreprocess();
	list<char> S_list, T_list;
	for (int i = 0; i < S.size(); ++i) {
		S_list.push_back(S[i]);
		if (i < T.size())
			T_list.push_back(T[i]);
	}

	int count = 0;
	list<char>::iterator iS = S_list.begin();
	list<char>::iterator iT = T_list.begin();
	list<char>::iterator iS2 = iS;

	while (iS != S_list.end()) {
		if (*iS == *iT) {
			count++;
			iS2 = iS;
			if (count == T.size()) {
				for (int i = 0; i < T.size(); ++i) {
					iS2 = S_list.erase(iS2);
					if (iS2 != S_list.begin())
						iS2--;

				}
				for (int i = 0; iS2 != S_list.begin() && i < T.size()-2; ++i) {
						iS2--;
				}
				iT = T_list.begin();
				//int dist = std::distance(S_list.begin(), iS2);
				iS = iS2;
				//iS = std::prev(iS2, min(int(T.size() - 2), dist));
				count = 0;
			}
			else {
				++iS;
				++iT;
			}
		}
		else {
			count = 0;
			if (iT != T_list.begin()) {
				for (int i = 0; iT != T_list.begin(); ++i) {
					iS--;
					iT--;
				}
				iS++;
			}
			else
				iS++;
		}
	}

	ofstream fout("censor.out");
	for (iS = S_list.begin(); iS != S_list.end(); ++iS)
		fout << *iS;
	fout << '\n';
	fout.close();
	return 0;
}