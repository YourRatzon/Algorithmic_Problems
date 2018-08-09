
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

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
#define M_PI		3.14159265358979323846
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
typedef vector<bool> vb;
typedef vector<char> vc;
typedef vector<double> vd;

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1e5 + 3;

struct Node {
		int v;
		string p;
		bool operator<(const Node& other) {
			if (p.size() != other.p.size())
				return p.size() < other.p.size();
			return p < other.p;
		}
};

void solve(vector<Node>& nodes) {
	sort(nodes.begin(),nodes.end());
	if (nodes[0].p != "") {
		cout<<"not complete\n";
		return;
	}

	vector<Node> tree(MAX_N+1, {-1,""});
	tree[1] = nodes[0];
	for (int i = 1; i < nodes.size(); ++i) {
		int id = 1;
		for (char c : nodes[i].p) {
			if (tree[id].v == -1) {
				cout<<"not complete\n";
				return;
			}
			id = id * 2;
			if (c == 'R')
				++id;
		}
		if (tree[id].v != -1) {
			cout<<"not complete\n";
			return;
		}
		tree[id] = nodes[i];
	}

	cout<<nodes[0].v;
	for (int i = 1; i < nodes.size(); ++i)
		cout<<' '<<nodes[i].v;
	cout<<'\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	string in;
	string delim = ",";
	vector<Node> nodes;
	while(cin>>in) {
		if (in == "()") {
			solve(nodes);
			nodes.clear();
			continue;
		}
		int val = stoi(in.substr(1,in.size()-1));
		string path = in.substr(in.find(delim)+1);
		path = path.substr(0,path.size()-1);
		nodes.push_back({val, path});
	}

  return 0;
}
