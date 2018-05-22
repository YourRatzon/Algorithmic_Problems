#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

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
//char _;

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }
double EPS = 1e-9;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const int MAX_N = 1e5 + 3;

struct trie_node {
	trie_node() : count(0), left(nullptr), right(nullptr) {}
	int count;
	trie_node* left;
	trie_node* right;
};

class Trie {
public:
	Trie() : root(new trie_node()), num_levels(31){}
	void insert(int num) {
		trie_node * curr = root;
		for (int i = num_levels-1; i >= 0; --i) {
			bool curr_bit = ((num & (1 << i)) != 0);
			if (!curr_bit) {
				if (!curr->left)
					curr->left = new trie_node();
				curr = curr->left;
			}
			else {
				if (!curr->right)
					curr->right = new trie_node();
				curr = curr->right;
			}
		}
		curr->count++;
	}
	void remove(int num) {
		remove_helper(root, num, 30);
	}
	void remove_helper(trie_node* curr, int num, int msb_idx) {
		bool msb_bit = ((num & (1 << msb_idx)) != 0);
		if (msb_idx == 0) {
			if (!msb_bit) {
				curr->left->count--;
				if (curr->left->count == 0) {
					delete curr->left;
					curr->left = nullptr;
				}
			}
			else {
				curr->right->count--;
				if (curr->right->count == 0) {
					delete curr->right;
					curr->right = nullptr;
				}
			}
		}
		else {
			if (!msb_bit)
				remove_helper(curr->left, num, msb_idx-1);
			else
				remove_helper(curr->right, num, msb_idx-1);

			if (curr->left && curr->left->count == 0 && 
				!curr->left->left && !curr->left->right) {
				delete curr->left;
				curr->left = nullptr;
			}
			if (curr->right && curr->right->count == 0 &&
				!curr->right->left && !curr->right->right) {
				delete curr->right;
				curr->right = nullptr;
			}
		}
	}

	void set_bit(int& num, int bit_idx) {
		num |= (1 << bit_idx);
	}

	int get_max_xor(int num) {
		trie_node * curr = root;
		int res = 0;
		for (int i = num_levels - 1; i >= 0; --i) {
			bool curr_bit = ((num & (1 << i)) != 0);
			if (!curr_bit) {
				if (curr->right) {
					set_bit(res, i);
					curr = curr->right;
				}
				else if (curr->left) {
					curr = curr->left;
				}
				else
					break;
				
			}
			else { // 1
				if (curr->left) { // 0
					set_bit(res, i);
					curr = curr->left;
				}
				else if (curr->right)
					curr = curr->right;
				else
					break;
			}
		}
		return res;
	}
private:
	trie_node * root;
	int num_levels;
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int q, val;
	char type;
	cin >> q;
	Trie tr;
	tr.insert(0);
	for (int i = 0; i < q; ++i) {
		cin >> type >> val;
		if (type == '+')
			tr.insert(val);
		else if (type == '-')
			tr.remove(val);
		else
			cout << tr.get_max_xor(val) << '\n';
	}
	
	return 0;
}