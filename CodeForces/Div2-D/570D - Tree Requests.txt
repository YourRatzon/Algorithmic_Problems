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


bool is_pali(bitset<26> pali_bs) {
	// a set bit means an odd # of occurence of that letter
	// if is more than one set bit, it's not a pali
	return pali_bs.count() < 2;
}

vector<bool> visited;


struct Node {
	Node() : level(-1), letter('?'), enter(-1), exit(-1) {}
	Node(char let) : level(-1), letter(let), enter(-1), exit(-1) {}
	int level;
	char letter;
	int enter, exit;
	bitset<26> cummulative_parity_up_to_me;
};

vector<Node> Nodes;
vector<vi> AdjList;
vector<vi> level_to_node_idxs;

int N, Q;
int timer;
void DFS(int u, int level) {	
	visited[u] = true;
	timer++;
	Nodes[u].enter = timer;
	Nodes[u].level = level;
	if (level_to_node_idxs[level].size() == 0) {
		// start new level
		level_to_node_idxs[level].push_back(u);
	}
	else {
		// continue existing level
		int prev_node = level_to_node_idxs[level].back();
		level_to_node_idxs[level].push_back(u);
		Nodes[u].cummulative_parity_up_to_me = 
			Nodes[prev_node].cummulative_parity_up_to_me;
	}
	Nodes[u].cummulative_parity_up_to_me.flip(int(Nodes[u].letter-'a'));

	for (int i = 0; i < AdjList[u].size(); ++i) {
		int v = AdjList[u][i];
		if (!visited[v])
			DFS(v, level + 1);
	}

	timer++;
	Nodes[u].exit = timer;
}

bool enter_comp(const int & lhs_node, const int & rhs_node) {
	return Nodes[lhs_node].enter < Nodes[rhs_node].enter;
}
bool exit_comp(const int & lhs_node, const int & rhs_node) {
	return Nodes[lhs_node].exit < Nodes[rhs_node].exit;
}


int main(int argc, char *argv[]) {
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	//ifstream cin("out.out");
	cin >> N >> Q;
	Nodes.resize(MAX_N);
	visited.assign(MAX_N, false);
	AdjList.assign(MAX_N, vi());
	level_to_node_idxs.assign(MAX_N, vi());
	int parent_of_i;

	for (int i = 2; i <= N; ++i) {
		cin >> parent_of_i;
		AdjList[parent_of_i].push_back(i);
	}
	char let;
	for (int i = 1; i <= N; ++i) {
		cin >> let;
		Nodes[i] = Node(let);
	}

	// only run on root since it's a connected tree (every node has a parent)
	timer = 0;
	DFS(1, 1);

	int node_id, hi;
	bitset<26> pali_bs;
	for (int i = 0; i < Q; ++i) {
		cin >> node_id >> hi;
		if (Nodes[node_id].level >= hi || level_to_node_idxs[hi].size() == 0)
			cout << "Yes\n";
		else {
			vector<int>::iterator lower_b =
				lower_bound(level_to_node_idxs[hi].begin(),
				level_to_node_idxs[hi].end(), node_id, enter_comp);

			vector<int>::iterator upper_b =
				lower_bound(level_to_node_idxs[hi].begin(),
				level_to_node_idxs[hi].end(), node_id, exit_comp);

			
			upper_b--;
		
			if (lower_b == level_to_node_idxs[hi].end()	||	//all elements in range are less than node_id.enter 
				Nodes[*lower_b].enter > Nodes[node_id].exit || // or more than node_id.exit
				Nodes[*upper_b].enter > Nodes[node_id].exit || Nodes[*upper_b].exit < Nodes[node_id].enter) {
				cout << "Yes\n";
				continue;
			}

			int left_node = *lower_b;
			int right_node = *upper_b;
			if (lower_b != level_to_node_idxs[hi].begin()) {
				lower_b--;
				pali_bs = Nodes[*lower_b].cummulative_parity_up_to_me ^
					Nodes[right_node].cummulative_parity_up_to_me;
			}
			else {
				pali_bs =
					Nodes[right_node].cummulative_parity_up_to_me;
			}
			if (is_pali(pali_bs))
				cout << "Yes\n";
			else
				cout << "No\n";
		}
	}
	return 0;
}