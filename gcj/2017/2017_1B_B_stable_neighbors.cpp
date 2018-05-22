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

string IMP = "IMPOSSIBLE";

struct ball {
	ball() : color('X') {}
	ball(char c, string n) : color(c), name(n) {}
	char color;
	string name;
};

int N, R, O, Y, G, B, V;
vector<ball> balls;

map<char, vc> color_to_opt = { { 'R', { 'B', 'Y' } }, { 'B', { 'R', 'Y' } },
							   { 'Y', { 'B', 'R' } } };

void try_to_fix(string &str) {
	swap(str[0], str[1]);
	int idx = 2;
	while (idx < str.size() - 1 && str[idx] == str[idx - 1]) {
		swap(str[idx], str[idx + 1]);
		idx += 2;
	}
}

bool check(string &str) {
	if (str.size() < 2)
		return true;
	if (str[0] == str.back())
		return false;
	for (int i = 0; i < str.size() - 1; ++i) {
		if (str[i] == str[i + 1])
			return false;
	}
	int x;
	return true;
}

string solve_small() {
	vector<ball> Bballs, Rballs, Yballs;
	for (ball b : balls) {
		if (b.color == 'B')
			Bballs.push_back(b);
		else if (b.color == 'R')
			Rballs.push_back(b);
		else
			Yballs.push_back(b);
	}

	deque<char> res;
	int b = Bballs.size(), r = Rballs.size(), y = Yballs.size();
	map<char, int> color_to_count = { { 'B', b }, { 'R', r }, { 'Y',y } };
	vector<pair<int, char>> options;
	if (b > 0)
		options.push_back({ b, 'B' });
	if (r > 0)
		options.push_back({ r, 'R' });
	if (y > 0)
		options.push_back({ y, 'Y' });

	while (!options.empty() && 
		(Bballs.size()>0 || Rballs.size()>0 || Yballs.size()>0)) {
		sort(options.begin(), options.end(), greater<pair<int, char>>());
		char newc = options[0].second;
		string to_add;
		if (newc == 'B') {
			to_add = Bballs.back().name;
			Bballs.pop_back();
		}
		else if (newc == 'R') {
			to_add = Rballs.back().name;
			Rballs.pop_back();
		}
		else {
			to_add = Yballs.back().name;
			Yballs.pop_back();
		}

		color_to_count[newc]--;
		
		if (res.empty() || res.back() != to_add.back()) {
			for (char c : to_add)
				res.push_back(c);
		}
		else {
			for (char c : to_add)
				res.push_front(c);
		}

		set<char> color_opts;
		vc tmp = color_to_opt[res[0]];
		for (char c : tmp)
			color_opts.insert(c);
		tmp = color_to_opt[res.back()];
		for (char c : tmp)
			color_opts.insert(c);
		
		options.clear();
		for (char c : color_opts) {
			int count = color_to_count[c];
			if (count > 0)
				options.push_back({ count, c });
		}
	}
	string res_str = "";
	if (Bballs.size() > 0 || Rballs.size() > 0 || Yballs.size() > 0)
		return IMP;
	else {
		for (char c : res)
			res_str.push_back(c);

		if (res_str.size() > 1 && res_str[0] == res_str.back()) {
			try_to_fix(res_str);
			if (!check(res_str)) {
				return IMP;
			}
		}
	}
	return res_str;
}

ball single_group(char mix, char single, int& nmix, int& nsingle, int nother,
	bool& only_group) {
	if (nmix == 0)
		return ball('X', "");

	if (nmix > nsingle)
		return ball('X', IMP);
	
	ball res_ball(single, "");
	while (nmix > 0) {
		res_ball.name += mix;
		res_ball.name += single;
		--nmix, --nsingle;
	}

	if (nsingle == 0) {
		if (nother == 0){
			if (only_group)
				return ball('X', IMP);
			else {
				only_group = true;
				return res_ball;
			}
		}
		else
			return ball('X', IMP);
	}
	else if (only_group) {
		return ball('X', IMP);
	}
	else {
		res_ball.name.insert(res_ball.name.begin(),single);
		//--nsingle;
	}
	return res_ball;
 }

int main() {
	//	ios_base::sync_with_stdio(false);
	//	cin.tie(0);
	ifstream fin("b.in");
	ofstream fout("b.out");
	int T;
	fin >> T;
	for (int t = 0; t < T; ++t) {
		balls.clear();
		fin >> N >> R>>O>>Y>>G>>B>>V;

		bool only_group = false;
		ball rball = single_group('G', 'R', G, R, N - G - R, only_group);
		ball yball = single_group('V', 'Y', V, Y, N - V - Y, only_group);
		ball bball = single_group('O', 'B', O, B, N - O - B, only_group);

		string res;
		if (rball.name == IMP || yball.name == IMP || bball.name == IMP) {
			res = IMP;
		}
		else if (only_group) {
			if (!rball.name.empty())
				res = rball.name;
			else if (!yball.name.empty())
				res = yball.name;
			else
				res = bball.name;
		}
		else {
			for (int i = 0; i < R; ++i)
				balls.push_back(ball('R', "R"));
			for (int i = 0; i < Y; ++i)
				balls.push_back(ball('Y', "Y"));
			for (int i = 0; i < B; ++i)
				balls.push_back(ball('B', "B"));

			res = solve_small();
			if (res.size() == 1 && 
			    (!rball.name.empty() || !yball.name.empty() || 
				 !bball.name.empty())) {
				res = IMP;
			}
			else if (res != IMP) {
				if (!rball.name.empty()) {
					int idx = res.find('R');
					res.replace(idx, 1, rball.name);
				}
				if (!yball.name.empty()) {
					int idx = res.find('Y');
					res.replace(idx, 1, yball.name);
				}
				if (!bball.name.empty()) {
					int idx = res.find('B');
					res.replace(idx, 1, bball.name);
				}
			}
		}
		fout << "Case #" << t + 1 << ": " << res << '\n';
	}

	return 0;
}