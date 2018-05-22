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

//PI
# define M_PI		3.14159265358979323846
// fast input
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

// TIMER
std::clock_t __start;
double __duration;
void start_timer() { __start = std::clock(); }
void print_timer() {
	__duration = (std::clock() - __start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << __duration << '\n';
}
// END TIMER

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

vector<bool>visited(26, false);
int score2(string s) {
	return (s[0] == s[1]) ? 2 : 0;	
}
int score3(string s){
	if (s[0] == s[1] && s[1] == s[2])
		return 3;
	else if (s[0] != s[1] && s[1] != s[2] && s[0] != s[2])
		return 0;
	else
		return 2;
}
unordered_map<string, int>score_map = { { "abac", 2 }, { "abcb", 2 }, { "abab", 3 }, { "aabb", 3 }, { "abba", 4 }, { "abbb", 3 }, { "abaa", 3 }, { "aaba", 3 }, { "aaab", 3 }, { "aaaa", 5 } };
int score4(string s) {
	std::unordered_map<char,char> dict;
	char val = 'a';
	for (int i = 0; i < 4; ++i) {
		if (dict.count(s[i]) == 0) {
			dict[s[i]] = val;
			++val;
		}
	}
	string res;
	for (int i = 0; i < 4; ++i) {
		res.push_back(dict[s[i]]);
	}
	if (score_map.count(res) != 0)
		return score_map[res];
	else
		return 0;
}
int curr_score = 0; 
int best_score = 0;
string best_tel;
string curr_tel;
int get_score(string& curr_tel) {
	string curr;
	int idx = 0;
	int last_idx = 0;
	int score = 0;
	while (idx < curr_tel.size()) {
		while (idx < curr_tel.size() && curr_tel[idx] != '-')
			++idx;
		int len = idx-last_idx;
		if (len == 2)
			score += score2(curr_tel.substr(last_idx, len));
		else if (len == 3)
			score += score3(curr_tel.substr(last_idx, len));
		else
			score += score4(curr_tel.substr(last_idx, len));
		++idx;
		last_idx = idx;
	}
	return score;
}

void update_res() {
	curr_score = get_score(curr_tel);
	if (curr_score > best_score) {
		best_score = curr_score;
		best_tel = curr_tel;
	}
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//start_timer();

	ifstream fin("INPUT.TXT");

	string tel;
	fin >> tel;
	fin.close();
	//4-3
	curr_tel = tel.substr(0, 4) + "-" + tel.substr(4, 3);
	update_res();
	//3-4
	curr_tel = tel.substr(0, 3) + "-" + tel.substr(3, 4);
	update_res();
	//3-2-2
	curr_tel = tel.substr(0, 3) + "-" + tel.substr(3, 2) + "-" + tel.substr(5, 2);
	update_res();
	// 2-3-2
	curr_tel = tel.substr(0, 2) + "-" + tel.substr(2, 3) + "-" + tel.substr(5, 2);
	update_res();
	// 2-2-3
	curr_tel = tel.substr(0, 2) + "-" + tel.substr(2, 2) + "-" + tel.substr(4, 3);
	update_res();


	ofstream fout("OUTPUT.TXT");
	fout << best_tel << '\n';
	fout << best_score << '\n';
	fout.close();
	//print_timer();
	return 0;
}