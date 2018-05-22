#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

/*
ID: jamerz1
PROG: angry
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

const int R_MAX = int(5 * 1e8 + 1);

vector<int> bales;
int n_bales, n_cows;

bool strong_enough(ll power) {
	int idx = 0;
	int cows_left = n_cows;
	while (idx < bales.size() && cows_left > 0) {
		ll left = bales[idx];
		ll right = left + 2 * power;
		cows_left--;
		while (idx < bales.size() && bales[idx] <= right)
			++idx;
	}
	if (idx == bales.size())
		return true;
	else
		return false;
}

int main() {

	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("angry.in");
	ofstream fout("angry.out");


	fin >> n_bales >> n_cows;
	bales.resize(n_bales);
	for (int i = 0; i < n_bales;++i) {
		fin >> bales[i];
	}
	if (n_bales == 1) {
		fout << 0 << '\n';
		return 0;
	}

	sort(bales.begin(), bales.end());

	ll min_power = R_MAX;

	ll low = 1;
	ll high = R_MAX;
	while (low <= high) {
		ll mid = low + (high - low) / 2;
		if (strong_enough(mid)) {
			min_power = min(min_power, mid);
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	fout << min_power << '\n';

	fin.close();
	fout.close();


	//print_timer();
	return 0;
}