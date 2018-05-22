#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

/*
ID: jamerz1
PROG: schlnet
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
#include <math.h>
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

//#define F first
//#define S second

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;


template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

const double PI = 3.14159265;
const int INF = INT_MAX;
int A_MAX = 1e9;
int A_MIN = -1e9;
double EPS = 1e-10;
const int MAX_N = 1e6 + 2e5;

vi nums;
vector<bool> covered;
vector<bool> to_change;
vi uncovered;

vector<int> primeVec;
bitset<MAX_N + 2> primeBS;
map<int, int> primeMAP;



void sieve(long long max)
{
	primeBS.set();
	primeBS[0] = primeBS[1] = 0;
	// once i > sqrt(max), the loop will be skipped, and i will just be added
	// as prime if primes[i].
	for (ll i = 2; i <= max; ++i)
	{
		if (primeBS[i])
		{
			for (long long j = i * i; j <= max; j += i)
				primeBS[j] = false;
			primeVec.push_back(int(i));
		}
	}
}

vi pi(MAX_N);
vi rub(MAX_N);
vi palis;

string num_str;
bool is_pali(int L, int R) {
	if (R - L < 1)
		return true;
	else
		return (num_str[L] == num_str[R] ? is_pali(L + 1, R - 1) : false);
}

int main(int argc, char *argv[]) {
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	sieve(MAX_N);

	int pal_count = 0;
	for (int i = 1; i < MAX_N; ++i) {
		stringstream ss;
		ss << i;
		num_str = ss.str();
		if (is_pali(0, num_str.size() - 1))
			pal_count++;
		rub[i] = pal_count;
	}

	int p_idx = 0;
	for (int i = 1; i < MAX_N; ++i) {
		while (p_idx < primeVec.size() && primeVec[p_idx] <= i)
			p_idx++;
		pi[i] = p_idx;
	}
	int p, q;
	cin >> p >> q;
	double A = double(p)/ double(q);
	
	int res;
	for (int i = MAX_N-1; i >= 0; --i) {
		if (double(pi[i]) <= double(A * double(rub[i]))) {
			cout << i << '\n';
			return 0;
		}
	}

	cout << "Palindromic tree is better than splay tree\n";
	return 0;
}