#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>


/*
ID: jamerz1
PROG: cbarn
LANG: C++11
*/

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

const int MAX_B = 1e6 + 4;
vii cows_x;
int N, B;
int MAX_Y = 0;
int MAX_X = 0;

std::string get_file_contents(const char *filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
bool compare_by_y(const ii& lhs, const ii& rhs) {
	return lhs.second < rhs.second;
}

int get_inner_res(int x, int y) {
	int SW = 0, NW = 0, SE = 0, NE = 0;
	int x_idx = 0;
	while (x_idx<N&&cows_x[x_idx].first < x) {
		if (cows_x[x_idx].second < y)
			SW++;
		else
			NW++;
		++x_idx;
	}
	while (x_idx < N) {
		if (cows_x[x_idx].second < y)
			SE++;
		else
			NE++;
		++x_idx;
	}
	return max(max(SW, NW), max(SE, NE));
}
int get_outer_res(int x) {
	int min_res = INF;
	int bottom_y = 0;
	int top_y = MAX_Y + 1; // make B even
	while (bottom_y + 2 < top_y) {
		int bottom_mid = bottom_y + (top_y - bottom_y) / 3;
		if (bottom_mid % 2 == 1)
			bottom_mid--;
		int top_mid = top_y - (top_y - bottom_y) / 3;
		if (top_mid % 2 == 1)
			top_mid++;
		int min_bottom = get_inner_res(x, bottom_mid);
		int min_top = get_inner_res(x, top_mid);
		if (min_bottom < min_top)
			top_y = top_mid; // throw out top third;
		else
			bottom_y = bottom_mid; // throw out bottom third;

		int curr_min_res = min(min_bottom, min_top);
		min_res = min(min_res, curr_min_res);
		if (bottom_mid + 2 >= top_mid)
			break;
	}
	return min_res;
}

int ternary_search() {
	int min_res = INF;
	int left_x = 0;
	int right_x = MAX_X + 1; // max X even
	while (left_x + 2 < right_x) {
		int left_mid = left_x + (right_x - left_x) / 3;
		if (left_mid % 2 == 1)
			left_mid--;
		int right_mid = right_x - (right_x - left_x) / 3;
		if (right_mid % 2 == 1)
			right_mid++;
		int min_left = get_outer_res(left_mid);
		int min_right = get_outer_res(right_mid);
		if (min_left == min_right) {
			left_x -= 2;
			right_x -=2;
		}
		else if (min_left < min_right)
			right_x = right_mid; //throw out right third
		else
			left_x = left_mid; // throw out left third
		int curr_min_res = min(min_left, min_right);
		min_res = min(min_res, curr_min_res);
		if (left_mid + 2 >= right_mid)
			break;
	}
	return min_res;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//start_timer();

	ifstream fin("balancing.in");
	ofstream fout("balancing.out");
	char filename[] = "balancing.in";
	string file_contents = get_file_contents(filename);
	stringstream ss(file_contents);
	int x, y;
	ss >> N;
	cows_x.resize(N);

	for (int i = 0; i < N; ++i) {
		ss >> x >> y;
		cows_x[i] = { x, y };
		MAX_Y = max(MAX_Y, y);
		MAX_X = max(MAX_X, x);
	}
	sort(cows_x.begin(), cows_x.end());
	int min_res = ternary_search();

	fout << min_res << '\n';
	fin.close();
	fout.close();
	//print_timer();
	return 0;
}