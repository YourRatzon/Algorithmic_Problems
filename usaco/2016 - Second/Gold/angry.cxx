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


const double R_MAX = (5 * 1e8 + 1);
const int X_MAX = int(1e9);

vector<int> bales;
int n_bales;

bool burn_left_bales(double power, double X, int start_idx = -1) {
	int idx;
	if (start_idx == -1) {
		idx = 0;
		while (idx + 1 < bales.size() && bales[idx + 1] <= X)
			++idx;
	}
	else
		idx = start_idx;

	if (idx == 0 && bales[0] > X) // no bales on left
		return true;

	int low = idx;
	// go to left-most bale that can be reached by cow thrown at X with <power>
	bool moved = false;
	low++;
	while (low - 1 >= 0 && bales[low - 1] + power >= X) {
		--low;
		moved = true;
	}
	if (low == 0 && bales[low]+power>=X) // reached left-most bale
		return true;

	else if (!moved || low == 0 || power <= 1+EPS) // couldn't reach any bales or no power left
		return false;
	else
		return burn_left_bales(power - 1, bales[low], low);
}

bool burn_right_bales(double power, double X, int start_idx = -1) {
	int idx;
	if (start_idx == -1) {
		idx = 0;
		while (idx < bales.size() && bales[idx] < X)
			++idx;
	}
	else
		idx = start_idx;

	if (idx == bales.size()) // no bales on right
		return true;

	int high = idx;
	bool moved = false;
	high--;
	// go to right-most bale that can be reached by cow thrown at X with <power>
	while (high + 1 < bales.size() && X + power >= bales[high + 1]) {
		++high;
		moved = true;
	}
	if (high +1 == bales.size() && X+power>= bales[high]) // reached right-most bale
		return true;

	else if (!moved || high+1== bales.size() || power <= 1+EPS) // couldn't reach any bales or no power left
		return false;
	else
		return burn_right_bales(power - 1, bales[high], high);
}

int MIN_LEFT = 2e9;
int MAX_RIGHT = 0.0;

bool strong_enough(double power, double& X) {
	double left = MIN_LEFT-EPS;
	double right = MAX_RIGHT+EPS;
	while (left <= right) {
		double mid = round(10*(left + (right - left) / 2))/10;
		bool burnt_left = burn_left_bales(power, mid);
		bool burnt_right = burn_right_bales(power, mid);
		X = mid;
		if (burnt_left && burnt_right) // burnt all 
			return true;
		else if (burnt_left) // burnt left but not right
			left = mid + .1;
		else if (burnt_right) // burnt right but not left
			right = mid - .1;
		else // not left not right
			return false;
	}
	return false;
}

int main() {

	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("angry.in");
	ofstream fout("angry.out");


	fin >> n_bales;
	bales.resize(n_bales);
	for (int i = 0; i < n_bales; ++i) {
		fin >> bales[i];
		MIN_LEFT = min(MIN_LEFT, bales[i]);
		MAX_RIGHT = max(MAX_RIGHT, bales[i]);
	}


	sort(bales.begin(), bales.end());

	double min_power = R_MAX;

	double low = 0.0;
	double high = R_MAX;
	double X;
	double loc;
	while (low <= high) {
		double mid = round((low + (high - low) / 2) * 10)/10;
		if (strong_enough(mid, X)) {
			if (mid < min_power) {
				loc = X;
				min_power = mid;
			}
			high = mid - 0.1;
		}
		else {
			low = mid + 0.1;
		}
	}



	fout << std::fixed;
	fout << std::setprecision(1)<<min_power << '\n';

	//fout << loc << '\n';

	fin.close();
	fout.close();


	//print_timer();
	return 0;
}