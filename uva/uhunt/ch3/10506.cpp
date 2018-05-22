#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
/*
ID: jamerz1
PROG: fence6
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
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;


template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

const int MAX_N = 2097153;
const double INF = 2e9 + 1;


vector<vii> AdjList;
int get_bottom_x_digits(int num, int digits, int base) {
	int res = 0;
	for (int i = 0; i < digits; ++i) {
		res += (num % base) * pow(base,i);
		num /= base;
	}
	return res;
}

vi reverse_euler_cycle;
vector<vi> edge_digits;

void get_euler_cycle(int u) {
	stack<int> st;
	while (true) {
		ii p;
		if (AdjList[u].size() == 0) {
			reverse_euler_cycle.push_back(u);
			if (st.empty())
				break;
			u = st.top();
			st.pop();
		}
		else {
			st.push(u);
			p = AdjList[u][0];
			AdjList[u].erase(AdjList[u].begin());
			int v = p.first;
			int w = p.second;
			edge_digits[u][v] = w;
			u = v;	
		}
	} 
}

string to_padded_str(int num, int n_digits, int base) {
	string res(n_digits, ' ');
	int dig;
	for (int i = n_digits-1; i >= 0; --i) {
		dig = num % base;
		num /= base;
		res[i] = '0' + dig;
	}
	return res;
}

int main(int argc, char *argv[]) {
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	int n_digits, base;
	while (cin >> n_digits >> base) {
		if (n_digits == 1) {
			for (int i = 0; i < base; ++i)
				cout << i;
			cout << '\n';
			continue;
		}

		const int vert_digits = n_digits - 1;
		int n_verts = pow(base, vert_digits);
		AdjList.assign(n_verts, vii());
		for (int i = 0; i < n_verts; ++i) {
			int u = i;
			for (int dig = 0; dig < base; ++dig) {
				int v = u * base + dig;
				v = get_bottom_x_digits(v, vert_digits, base);
				AdjList[u].push_back({ v, dig });
			}
		}

		edge_digits.assign(n_verts, vi(n_verts, 0));
		get_euler_cycle(0);
		int cycle_sz = reverse_euler_cycle.size();
		vi euler_cylce(cycle_sz);
		for (int i = 0; i < cycle_sz; ++i)
			euler_cylce[i] = reverse_euler_cycle[cycle_sz - 1 - i];

		cout << to_padded_str(euler_cylce[0], vert_digits, base);
		int count = vert_digits;
		for (int i = 0; count < pow(base,n_digits); ++i, ++count) {
			cout << char('0' + edge_digits[euler_cylce[i]][euler_cylce[i + 1]]);
		}
		cout << '\n';

	}
	return 0;

}
