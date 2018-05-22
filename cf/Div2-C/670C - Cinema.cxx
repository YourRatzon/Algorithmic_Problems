

#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << __duration << '\n';
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
bool eq(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS);
}

const int INF = int(2e9);
const ll INF_LL = ll(1e18);
const int MAX_N = 1e7;


vi sci_langs;
vi sub_langs;
vi movie_langs;
map<int, int> sci_lang_counts;
map<int, int> sub_lang_counts;
map<int, int> movie_lang_counts;

map<int, int> lang_to_movie_idx;
map<int, int> sub_to_movie_idx;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//start_timer();

	int N;
	cin >> N;
	sci_langs.resize(N);
	for (int i = 0; i < N; ++i) {
		cin >> sci_langs[i];
		sci_lang_counts[sci_langs[i]]++;
	}

	int M;
	cin >> M;
	movie_langs.resize(M);
	sub_langs.resize(M);
	int lang;
	for (int i = 0; i < M; ++i) {
		cin >> movie_langs[i];
		movie_lang_counts[movie_langs[i]] = 0;
		lang_to_movie_idx[movie_langs[i]] = i + 1;
	}
	for (int i = 0; i < M; ++i) {
		cin >> sub_langs[i];
		sub_lang_counts[sub_langs[i]] = 0;
		sub_to_movie_idx[sub_langs[i]] = i + 1;
	}

	ll best_res = 0;
	int best_movie = 1;
	vi cand_movies;
	for (int i = 0; i < M; ++i) {
		ll curr_res = sci_lang_counts[movie_langs[i]];
		if (curr_res > best_res) {
			best_res = curr_res;
			best_movie = i + 1;
		}
	}
	ll bestest_res = 0;
	for (int i = 0; i < M; ++i) {
		ll curr_res = sci_lang_counts[movie_langs[i]];
		if (curr_res == best_res && sub_langs[i] != movie_langs[i]) {
			curr_res += sci_lang_counts[sub_langs[i]];
		}
		if (curr_res > bestest_res) {
			bestest_res = curr_res;
			best_movie = i + 1;
		}
	}
	cout << best_movie << '\n';

	//print_timer();
	return 0;
}