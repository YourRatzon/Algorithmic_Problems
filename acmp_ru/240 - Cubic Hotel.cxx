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

vector<vector<vector<char>>> faces;
vector<vector<vector<char>>> cube;

void remove_cube(int r, int c, int d) {
	cube[r][c][d] = ' ';
}

void read_input(ifstream& fin, int N) {
	for (int i = 0; i < N; ++i) {
		for (int face = 0; face < 6; ++face) {
			for (int j = 0; j < N; ++j) {
				fin >> faces[face][i][j];
			}
		}
	}
}

void remove_dots(int N) {
	// front dots
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			if (faces[0][r][c] == '.') {
				for (int d = 0; d < N; ++d)
					remove_cube(r, c, d);
			}
		}
	}
	// left dots
	for (int r = 0; r < N; ++r) {
		for (int d = N - 1; d >= 0; --d) {
			if (faces[1][r][N - 1 - d] == '.') {
				for (int c = 0; c < N; ++c)
					remove_cube(r, c, d);
			}
		}
	}
	// top dots
	for (int d = N - 1; d >= 0; --d) {
		for (int c = 0; c < N; ++c) {
			if (faces[4][N - 1 - d][c] == '.') {
				for (int r = 0; r < N; ++r)
					remove_cube(r, c, d);
			}
		}
	}
}

void color_and_fix(int N) {

	bool removed = true;
	while (removed) {
		removed = false;
		// color front face
		for (int r = 0; r < N; ++r) {
			for (int c = 0; c < N; ++c) {
				char color = faces[0][r][c];
				if (color == '.')
					continue;
				for (int d = 0; d < N; ++d) {
					if (cube[r][c][d] != ' ') {
						if (cube[r][c][d] == color) // all good!
							break;
						else if (cube[r][c][d] == '?') {  // all good!
							cube[r][c][d] = color;
							break;
						}
						else {// bad cube: remove and look for next one
							remove_cube(r, c, d);
							removed = true;
						}
					}
				}
			}
		}
		// color left face
		for (int r = 0; r < N; ++r) {
			for (int d = N - 1; d >= 0; --d) {
				char color = faces[1][r][N - 1 - d];
				if (color == '.')
					continue;
				for (int c = 0; c < N; ++c) {
					if (cube[r][c][d] != ' ') {
						if (cube[r][c][d] == color) // all good!
							break;
						else if (cube[r][c][d] == '?') {  // all good!
							cube[r][c][d] = color;
							break;
						}
						else {// bad cube: remove and look for next one
							remove_cube(r, c, d);
							removed = true;
						}
					}
				}
			}
		}

		// color back face
		for (int r = 0; r < N; ++r) {
			for (int c = N - 1; c >= 0; --c) {
				char color = faces[2][r][N - 1 - c];
				if (color == '.')
					continue;
				for (int d = N - 1; d >= 0; --d) {
					if (cube[r][c][d] != ' ') {
						if (cube[r][c][d] == color) // all good!
							break;
						else if (cube[r][c][d] == '?') {  // all good!
							cube[r][c][d] = color;
							break;
						}
						else {// bad cube: remove and look for next one
							remove_cube(r, c, d);
							removed = true;
						}
					}
				}
			}
		}

		// color right face 
		for (int r = 0; r < N; ++r) {
			for (int d = 0; d < N; ++d) {
				char color = faces[3][r][d];
				if (color == '.')
					continue;
				for (int c = N - 1; c >= 0; --c) {
					if (cube[r][c][d] != ' ') {
						if (cube[r][c][d] == color) // all good!
							break;
						else if (cube[r][c][d] == '?') {  // all good!
							cube[r][c][d] = color;
							break;
						}
						else {// bad cube: remove and look for next one
							remove_cube(r, c, d);
							removed = true;
						}
					}
				}
			}
		}

		// color top face
		for (int d = N - 1; d >= 0; --d) {
			for (int c = 0; c < N; ++c) {
				char color = faces[4][N - 1 - d][c];
				if (color == '.')
					continue;
				for (int r = 0; r < N; ++r) {
					if (cube[r][c][d] != ' ') {
						if (cube[r][c][d] == color) // all good!
							break;
						else if (cube[r][c][d] == '?') {  // all good!
							cube[r][c][d] = color;
							break;
						}
						else {// bad cube: remove and look for next one
							remove_cube(r, c, d);
							removed = true;
						}
					}
				}
			}
		}

		// color bottom face
		for (int d = 0; d < N; ++d) {
			for (int c = 0; c < N; ++c) {
				char color = faces[5][d][c];
				if (color == '.')
					continue;
				for (int r = N - 1; r >= 0; --r) {
					if (cube[r][c][d] != ' ') {
						if (cube[r][c][d] == color) // all good!
							break;
						else if (cube[r][c][d] == '?') {  // all good!
							cube[r][c][d] = color;
							break;
						}
						else {// bad cube: remove and look for next one
							remove_cube(r, c, d);
							removed = true;
						}
					}
				}
			}
		}
	}
}

int count_max_blocks(int N) {
	int res = 0;
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			for (int d = 0; d < N; ++d)
				if (cube[r][c][d] != ' ')
					res++;
		}
	}
	return res;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//start_timer();

	ifstream fin("INPUT.TXT");
	int N;
	fin >> N;
	cube.assign(N, vector<vector<char>>(N, vector<char>(N,'?')));
	faces.assign(6, vector<vector<char>>(N, vector<char>(N, '?')));

	read_input(fin, N);
	fin.close();

	remove_dots(N);
	color_and_fix(N);
	int max_blocks_left = count_max_blocks(N);

	ofstream fout("OUTPUT.TXT");
	fout << max_blocks_left << '\n';
	fout.close();
	//print_timer();
	return 0;
}