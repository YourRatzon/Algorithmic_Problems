//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

//#define F first
//#define S second

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration (msec): " << __duration * 1000 << '\n';
}
// END TIMER

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

double EPS = 1e-16;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ll, ll> llll;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<llll> vllll;
typedef vector<int> vi;
typedef vector<ull> vull;


# define M_PI		3.14159265358979323846
const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1000 + 5;


struct Node {
	Node(int _id) : id(_id) {}
	int id;
	vector<Node*> children;
};
int N, t, k;
Node * root;
void DFS(Node * curr) {
	for (Node * node : curr->children) {
		cout << curr->id << ' ' << node->id << '\n';
		DFS(node);
	}
}
void success() {
	cout << N << '\n';
	DFS(root);
	exit(0);
}
void fail() {
	cout << -1 << '\n';
	exit(0);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> t >> k;
	int x, idx = 1;
	root = new Node(idx);
	++idx;
	Node * curr = root;
	int nleaves = 0;
	for (int i = 0; i < t; ++i) {
		cin >> x;
		if (i + 1 == t)
			nleaves += x;
		else
			nleaves += x - 1;
		for (int j = 0; j < x; ++j) {
			curr->children.push_back(new Node(idx));
			++idx;
		}
		curr = curr->children[0];
	}
	if (nleaves == k)
		success();
	else if (nleaves < k)
		fail();
	else {
		vector<vector<Node*>> level_leaves(t+1, vector<Node*>());
		vector<vector<Node*>> level_inner(t+1, vector<Node*>());
		queue<Node*> q;
		q.push(root);
		vi dist(N + 1, INF);
		dist[root->id] = 0;
		while (!q.empty()) {
			Node* u = q.front();
			q.pop();
			int ud = dist[u->id];
			for (Node* node : u->children) {
				int curr_d = ud + 1;
				dist[node->id] = curr_d;
				if (node->children.empty())
					level_leaves[curr_d].push_back(node);
				else {
					level_inner[curr_d].push_back(node);
					q.push(node);
				}
			}

		}
		for (int lev = 1; lev <= t - 1; ++lev) {
			int leaf_idx = 0;
			for (Node * node : level_inner[lev]) {
				while (nleaves>k && node->children.size()>1 &&
						leaf_idx<level_leaves[lev].size()) { 
					Node* curr_leaf = level_leaves[lev][leaf_idx];
					++leaf_idx;
					curr_leaf->children.push_back(node->children.back());
					node->children.pop_back();
					--nleaves;
					if (nleaves == k)
						success();
				}
			}
		}

		fail();
	}
	return 0;
}