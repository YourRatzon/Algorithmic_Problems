#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

/*
ID: jamerz1
PROG: tour
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
#include <assert.h>
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

// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

// TIMER
std::clock_t start;
double duration;
void start_timer() { start = std::clock(); }
void print_timer() {
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << '\n';
}
// END TIMER

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-10;
bool eq(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

struct Point {
	Point():x(0), y(0){}
	Point(int _x, int _y) : x(_x), y(_y) {}
	int x;
	int y;
};

ll fact(int k) {
	ll res = 1;
	while (k) {
		res *= k;
		--k;
	}
	return res;
}
ll nChooseK(int n, int k) {
	ll res = 1;
	ll fact_k = fact(k);
	while (k) {
		res *= n;
		--n;
		--k;
	}
	return res / fact_k;
}

int main(int argc, char *argv[]) {
	//start_timer();
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	ifstream fin("fb1.in");
	ofstream fout("fb1.out");

	int T, N, x, y;
	ll curr_res = 0;

	fin >> T;
	vector<unordered_map< ll, int>> pt_idx_to_distsq_counts;
	vector<Point> points;
	for (int i = 0; i < T; ++i) {
		fin >> N;
		curr_res = 0;
		pt_idx_to_distsq_counts.assign(N, unordered_map < ll, int >());
		points.resize(N);
		for (int j = 0; j < N; ++j) {
			fin >> x >> y;
			points[j] = Point(x, y);
		}
		for (int j = 0; j < N-1; ++j) {
			for (int k = j + 1; k < N; ++k) {
				int delta_x = points[j].x - points[k].x;
				int delta_y = points[j].y - points[k].y;

				ll curr_distsq = delta_x * delta_x + delta_y * delta_y;
				auto it = pt_idx_to_distsq_counts[j].find(curr_distsq);
				if (it == pt_idx_to_distsq_counts[j].end())
					pt_idx_to_distsq_counts[j][curr_distsq] = 1;
				else
					pt_idx_to_distsq_counts[j][curr_distsq]++;

				it = pt_idx_to_distsq_counts[k].find(curr_distsq);
				if (it == pt_idx_to_distsq_counts[k].end())
					pt_idx_to_distsq_counts[k][curr_distsq] = 1;
				else
					pt_idx_to_distsq_counts[k][curr_distsq]++;
			}
		}
		for (int j = 0; j < N; ++j) {
			for (auto entry : pt_idx_to_distsq_counts[j]) {
				curr_res += nChooseK(entry.second, 2);
			}
		}
		fout << "Case #" << i + 1 << ": " << curr_res << '\n';
	}


	//print_timer();
	return 0;
}