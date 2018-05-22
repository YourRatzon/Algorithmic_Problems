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

struct WashingMachine {
	WashingMachine(ll cycle_t) : cycle_time(cycle_t) , num_loads(0) {}
	ll cycle_time;
	ll num_loads;
};

struct WashingMachineComp {
	bool operator()(const WashingMachine& lhs, const WashingMachine& rhs) const
	{
		return lhs.cycle_time*(lhs.num_loads+1) > 
			   rhs.cycle_time*(rhs.num_loads+1);
	}
};
typedef ll DryerEndTime;

int main() {
	
	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	int T;
	ifstream fin("laundro_matt_example_input.txt");

	fin >> T;
	ofstream fout("laundro.out");
	int loads, machines, dryers, dry_time;
	ll cycle_time;
	for (int t = 0; t < T; ++t) {
		fin >> loads >> machines >> dryers >> dry_time;
		std::priority_queue < WashingMachine, vector<WashingMachine>, WashingMachineComp> pq;
		for (int i = 0; i < machines; ++i) {
			fin >> cycle_time;
			pq.push(WashingMachine(cycle_time));
		}

		for (int i = 0; i < loads; ++i) {
			WashingMachine curr_machine = pq.top();
			pq.pop();
			curr_machine.num_loads++;
			pq.push(curr_machine);
		}
		vector<ll> load_end_times;
		while (!pq.empty()) {
			WashingMachine curr_machine = pq.top();
			pq.pop();
			for (int i = 1; i <= curr_machine.num_loads; ++i) {
				ll end_time = curr_machine.cycle_time * i;
				load_end_times.push_back(end_time);
			}
		}
		
		sort(load_end_times.begin(), load_end_times.end());
		ll res = 0;
		if (dryers >= machines) { // one load per drier
			res = load_end_times.back() + dry_time;
		}
		else {
			std::priority_queue < DryerEndTime, vector<DryerEndTime>, greater<DryerEndTime>> dryer_pq;
			for (int i = 0; i < dryers; ++i)
				dryer_pq.push(0);
			for (int i = 0; i < load_end_times.size(); ++i) {
				ll load_end_time = load_end_times[i];
				DryerEndTime curr_dryer_end_time = dryer_pq.top();
				dryer_pq.pop();
				DryerEndTime new_dryer_end_time = max(curr_dryer_end_time, load_end_time) + dry_time;
				res = max(res, new_dryer_end_time);
				dryer_pq.push(new_dryer_end_time);
			}
		}
		fout << "Case #" << t + 1 << ": " << res << '\n';
	}
	

	fin.close();
	fout.close();


	//print_timer();
	return 0;
}