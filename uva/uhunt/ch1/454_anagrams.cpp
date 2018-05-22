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
const int MAX_N = 1e6 + 5;

int main() {
	//	ios_base::sync_with_stdio(false);
	//	cin.tie(0);

	int T;
	cin >> T;
	cin.get();
	cin.get();
	for (int t = 0; t < T; ++t) {
		string line;
		set<string> seen;
		vector<string> lines;
		map<string, vi> key_to_idx;
		while (getline(cin, line) && !line.empty()) {
			lines.push_back(line);
			int idx = lines.size() - 1;
			string key;
			for (char c : line)
				if (c != ' ')
					key.push_back(c);
			sort(key.begin(), key.end());
			auto it = key_to_idx.find(key);
			if (it != key_to_idx.end())
				key_to_idx[key].push_back(idx);
			else
				key_to_idx[key] = { idx };
		}
		
		vector<string> anagrams;
		for (auto& e : key_to_idx) {
			vi idxs = e.second;
			for (int i = 0; i < idxs.size(); ++i) {
				for (int j = i + 1; j < idxs.size(); ++j) {
					string a = lines[idxs[i]];
					string b = lines[idxs[j]];
					if (a > b)
						swap(a, b);
					string anagram = a + " = " + b;
					anagrams.push_back(anagram);
				}
			}
		}
		sort(anagrams.begin(), anagrams.end());
		for (string& s : anagrams)
			cout << s << '\n';
		if (t+1<T)
			cout << '\n';
	}
	return 0;
}