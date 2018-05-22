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
const int MAX_N = 1e5;

struct query {
	query() {}
	query(int _idx, char _new_c, char _prev_c) 
		: idx(_idx), new_c(_new_c), prev_c(_prev_c) {}
	int idx;
	char new_c;
	char prev_c;
};

vector<query> queries;
vi results;

int main(int argc, char *argv[]) {
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	int N, Q;
	cin >> N >> Q;
	queries.resize(Q);
	results.resize(Q);
	string Str;
	cin >> Str;
	char new_c;
	int q;
	for (int i = 0; i < Q; ++i) {
		cin >> q >> new_c;
		char prev_c = Str[q - 1];
		query new_q(q - 1, new_c, prev_c);
		queries[i] = new_q;
		Str[q-1] = new_c;
	}
	if (N == 1) {
		for (int i = 0; i < Q; ++i) {
			cout << 0 << '\n';
		}
		return 0;
	}

	int res = 0;
	for (int i = 0; i < Str.size()-1; ++i) {
		if (Str[i] == '.' && Str[i + 1] == '.')
			res++;
	}
	results[Q - 1] = res;
	// Can assume N>1 (handled this case already)
	for (int i = Q - 1; i > 0; --i) {
		query curr_q = queries[i];
		if (curr_q.new_c != '.') {
			if (curr_q.prev_c == '.') {
				if (curr_q.idx < N-1) {
					if (Str[curr_q.idx + 1] == '.')
						res++;
				}
				if (curr_q.idx > 0) {
					if (Str[curr_q.idx - 1] == '.')
						res++;
				}
			}
			// else prev_c != '.' and query didn't change anything
		}
		else { // curr_q.new_c == '.'
			if (curr_q.prev_c != '.') {
				if (curr_q.idx < N - 1) {
					if (Str[curr_q.idx + 1] == '.')
						res--;
				}
				if (curr_q.idx > 0) {
					if (Str[curr_q.idx - 1] == '.')
						res--;
				}
			}
			// else prev_c == '.' and query didn't change anything
		}
		Str[curr_q.idx] = curr_q.prev_c;
		results[i - 1] = res;
	}

	for (int i = 0; i < results.size(); ++i) {
		cout << results[i] << '\n';
	}
	return 0;
}