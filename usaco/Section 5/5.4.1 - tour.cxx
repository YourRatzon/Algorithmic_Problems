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
void start_timer() {start = std::clock();}
void print_timer() {	
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << '\n';
}
// END TIMER

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

const double PI = 3.14159265;
const int INF = INT_MAX;
int A_MAX = 1e9;
int A_MIN = -1e9;
double EPS = 1e-10;
const int MAX_N = 5e5 + 5;

vector<vector<int>> FlightsTo, FlightsBack;
std::unordered_map<string, int> city_to_id;
vector<vector<bool>> graph;
vector<vector<int>> paths;

int main(int argc, char *argv[]) {
	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);
	
	ifstream fin("tour.in");
	int cities, flights;
	fin >> cities >> flights;
	graph.assign(cities, vector<bool>(cities, false));
	paths.assign(cities, vi(cities, 0));

	string city1, city2;
	for (int city_id = 0; city_id < cities; ++city_id) {
		fin >> city1;
		city_to_id[city1] = city_id;
	}
	int city1_id, city2_id;
	for (int i = 0; i < flights; ++i) {
		fin >> city1 >> city2;
		city1_id = city_to_id[city1];
		city2_id = city_to_id[city2];
		graph[city1_id][city2_id] = true;
		graph[city2_id][city1_id] = true;
	}
	fin.close();
	
	paths[0][0] = 1;
	for (int i = 0; i < cities - 1; ++i) {
		for (int j = i + 1; j < cities; ++j) {
			paths[i][j] = -1;
			for (int k = 0; k < j; ++k) {
				if (graph[k][j] && paths[i][k] > 0 && paths[i][k] > paths[i][j])
					paths[i][j] = paths[i][k];
			}
			paths[i][j]++;
			paths[j][i] = paths[i][j];
		}
	}

	int answer = 1;
	for (int i = 0; i < cities; ++i) {
		if (graph[i][cities - 1] && paths[i][cities - 1]>answer)
			answer = paths[i][cities - 1];
	}

	ofstream fout("tour.out");
	fout << answer << '\n';
	fout.close();
	//print_timer();
	return 0;
}