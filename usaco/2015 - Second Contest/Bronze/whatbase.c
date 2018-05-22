#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
/*
ID: jamerz1
PROG: whatbase
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

int compute(string num, int base) {
	return (num[0]-'0') * base*base + (num[1]-'0')* base + num[2] - '0';
}
int main()
{
	ifstream fin("whatbase.in");
	int K;
	string num1, num2;
	fin >> K;
	ofstream fout("whatbase.out");

	for (int i = 0; i < K; ++i) {
		fin >> num1 >> num2;
		std::unordered_map<int,int> poss_X;
		for (int b = 10; b <= 15000; ++b) {
			poss_X[compute(num1, b)] = b;
		}
		for (int b = 10; b <= 15000; ++b) {
			int res_Y = compute(num2, b);
			if (poss_X[res_Y]) {
				fout << poss_X[res_Y] << ' ' << b << '\n';
				break;
			}
		}
	}
	fin.close();
	fout.close();
	return 0;
}