//#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

/*
ID: jamerz1
PROG: hidden
LANG: C++11
*/

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

double EPS_ = 1e-16;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS_);
}

//#define F first
//#define S second

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
typedef pair<int, int> ii;
typedef pair<double, double> dd;

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
typedef vector<string> vs;

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;

struct Node {
	Node(int _val, int _idxs, string& _ops) : val(_val), idxs(_idxs), ops(_ops) {}
	int val;
	int idxs;
	string ops;
};

int exec_op(int a, int b, char op) {
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a*b;
	case '/':
		return a / b;
	default:
		break;
	}
	return -1;
}


int num_set(int num) {
	int res = 0;
	for (int i = 0; i < 6; ++i) {
		if (num & (1 << i) != 0)
			++res;
	}
	return res;
}

void set_bit(int& num, int bit) {
	num = num | (1 << bit);
}
int main()  {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	int C;
	cin >> C;
	for (int c = 0; c < C; ++c) {
		vector<Node> nodes;
		set<ii> seen;
		vi nums(6);
		for (int i = 0; i < 6; ++i) {
			cin >> nums[i];
			string ops = "";
			int mask = 0;
			set_bit(mask, i);

			nodes.push_back(Node(nums[i], mask, ops));
			//seen.insert({ nums[i], mask});
		}
		int T;
		cin >> T;
		for (int n = 0; n < 3; ++n) {
			//cout << "n: " << n << "; nodes.size(): " << nodes.size() << '\n';
			vector<Node> new_nodes;
			for (int i = 0; i < nodes.size(); ++i) {
				for (int j = i + 1; j < nodes.size(); ++j) {
					int left_mask = nodes[i].idxs;
					int right_mask = nodes[j].idxs;
					int new_mask = left_mask | right_mask;
					if (num_set(new_mask) != num_set(left_mask) + num_set(right_mask)) {
						continue;
					}
					string curr_ops = nodes[i].ops + '\n' + nodes[j].ops;

					for (char op : {'+', '-', '*', '/'}) {
						if (op == '/' && (nodes[j].val == 0 || 
										  nodes[i].val % nodes[j].val != 0))
							continue;
						int new_val = exec_op(nodes[i].val, nodes[j].val ,op);
						//if (seen.find({ new_val, new_mask }) != seen.end())
						//	continue;
						int mask = 0;
						string new_ops = curr_ops + to_string(nodes[i].val) + " " + op + " " + 
									to_string(nodes[j].val);
						new_nodes.push_back(Node(new_val, new_mask, new_ops));
						//seen.insert({ new_val, new_mask });
					}
					//cout << "i: " << i << "; seen.size(): " 
					//	<< seen.size() << '\n';
				}
			}
			nodes.insert(nodes.end(), new_nodes.begin(), new_nodes.end());
		}

		int min_diff = INF;
		int best_idx = 0;
		for (int i = 0; i < nodes.size(); ++i) {
			int curr_diff = abs(nodes[i].val - T);
			if (curr_diff < min_diff) {
				min_diff = curr_diff;
				best_idx = i;
			}
		}

		cout << "Target: " << T << '\n';
		cout << nodes[best_idx].ops << '\n';
		cout << "Best approx: " << nodes[best_idx].val << '\n';
		cout << '\n';
	}
	return 0;
}