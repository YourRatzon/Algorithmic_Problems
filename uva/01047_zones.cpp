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
typedef unsigned int uint;
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


bool is_set(int n, int bit) {
	return (n & (1 << bit)) != 0;
}

void set_bit(uint& n, int bit) {
	n |= (1 << bit);
}

bool next_bits(vb& bits, int b) {
	if (b == 0)
		return false;

	int idx = bits.size() - 1;
	while (idx >= 0 && bits[idx] == true)
		--idx;
	if (idx <= 0)
		return false;
	--idx;
	while (idx >= 0 && bits[idx] == false)
		--idx;
	if (idx < 0)
		return false;

	bits[idx] = 0;
	bits[idx + 1] = 1;
	int num1s = 0;
	for (int i = idx + 2; i < bits.size(); ++i) {
		if (bits[i])
			num1s++;
	}
	for (int i = idx + 2; i < bits.size(); ++i, num1s--) {
		if (num1s>0)
			bits[i] = 1;
		else
			bits[i] = 0;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	//ofstream cout("uva.out");

	int n, b, m, k=1;
	while (cin >> n >> b && n != 0) {
		vi customers(n);
		for (int i = 0;i < n; ++i)
			cin >> customers[i];
		cin >> m;
		vector<uint> common(m);
		vi common_count(m);
		int t;
		for (int i = 0; i < m; ++i) {
			cin >> t;
			int x;
			uint curr=0;
			for (int j = 0; j < t; ++j) {
				cin >> x;
				set_bit(curr, x-1);
			}
			common[i] = curr;
			cin >> common_count[i];
		}
		int best_sum = 0;
		vb best_bits;
		vb bits(b,true);
		bits.insert(bits.end(), n-b,false);
		do {
			int sum = 0;
			for (int i = 0; i < n; ++i) {
				if (bits[i]) {
					sum += customers[i];
				}
			}
			for (int j = 0; j < m; ++j) {
				int hits = 0;
				for (int i = 0; i < n; ++i) {
					if (is_set(common[j],i) && bits[i])
						hits++;
				}
				if (hits >= 2)
					sum -= (hits - 1)*common_count[j];
			}
			if (sum > best_sum) {
				best_sum = sum;
				best_bits = bits;
			}
		} while (next_bits(bits, b));

		cout << "Case Number  "<< k << '\n';
		cout << "Number of Customers: " << best_sum<<'\n';
		cout << "Locations recommended: ";
		int seen = 0;
		for (int i = 0; i < best_bits.size(); ++i) {
			if (best_bits[i]) {
				cout << i + 1<<(seen == b-1 ? "":" ");
				seen++;
			}
		}
		cout << "\n\n";
		++k;
	}
	return 0;
}