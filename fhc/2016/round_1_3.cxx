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
#define scan_fast(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
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
double PI = cos(-1);
const int INF = int(2e9);
#define M_PI       3.14159265358979323846

int main() {
	
	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	int T;
	ifstream fin("yachtzee.txt");

	int n_steps, A, B;
	vector<ll> step_prices;
	fin >> T;
	ofstream fout("yachtzee.out");
	for (int t = 0; t < T; ++t) {
		double res = 0;
		fin >> n_steps >> A >> B;
		double range_size = B - A;
		step_prices.resize(n_steps);
		for (int i = 0; i < step_prices.size(); ++i)
			fin >> step_prices[i];

		int idx = 0;
		ll curr_cost = 0;
		while (curr_cost <= A) {
			curr_cost += step_prices[idx];
			++idx;
			idx %= n_steps;
		}
		if (curr_cost > B) {
			res = double(B + A) / 2.0;
			fout << std::fixed;
			fout << std::setprecision(12) << "Case #" << t + 1 << ": " << res << '\n';
			continue;
		}
		if (idx == 0) {
			idx = n_steps - 1;
		}
		else {
			--idx;
		}
		res += (double(curr_cost - A) / range_size) * (double(step_prices[idx]+(A-(curr_cost-step_prices[idx])))/2.0);
		++idx;
		idx %= n_steps;

		ll last_cost = curr_cost;
		while (curr_cost + step_prices[idx]<= B) {
				curr_cost += step_prices[idx];
				res += (double(curr_cost - last_cost) / range_size) * (double(step_prices[idx]) / 2.0);
				last_cost = curr_cost;

			++idx;
			idx %= n_steps;
		}
		curr_cost = B;
		res += (double(curr_cost - last_cost) / range_size) * (double(curr_cost-last_cost) / 2.0);

		fout << std::fixed;
		fout << std::setprecision(12)<<"Case #" << t + 1 << ": " << res << '\n';
	}
	

	fin.close();
	fout.close();


	//print_timer();
	return 0;
}