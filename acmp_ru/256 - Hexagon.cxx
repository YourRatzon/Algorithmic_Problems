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

const int MAX_N = 202;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//start_timer();
	
	ifstream fin("INPUT.TXT");
	ofstream fout("OUTPUT.TXT");
	int N;
	fin >> N;
	char type;
	double X = 0, Y = 0, Z = 0;
	int val;
	for (int i = 0; i < N; ++i) {
		fin >> type >> val;
		if (type == 'X') X += val;
		else if (type == 'Y') Y += val;
		else Z += val;
	}
	fin.close();
	int final_x = 0;
	double final_y = 0;
	final_x += Y;
	final_x += Z;
	final_y += X;
	final_y += Y / 2;
	final_y -= Z / 2;
	final_x = abs(final_x);
	final_y = fabs(final_y);
	int x_moves = final_x;
	int y_moves = int(round(final_y - double(x_moves) / 2.0));
	int res = x_moves + max(y_moves,0);
	fout << res << '\n';
	fout.close();
	//print_timer();
	return 0;
}