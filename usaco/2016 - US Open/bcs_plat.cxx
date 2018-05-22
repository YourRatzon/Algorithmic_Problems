

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


struct Pic {
	int R, C; 
	vi tiles;
	set<ii> cell_set;
	ii start_cell;
	vector<vector<char>> grid;
	vector<vector<bool>> visited;
	vector<vector<ii>> solutions;
	static vii moves;

	Pic() : R(0), C(0) {}
	Pic(int _r, int _c) {
		tiles.assign(26, 0);
		R = _r, C = _c;
		grid.assign(R, vector<char>(C));
	}

	bool legal_move(int r, int c) {
		return r >= 0 && r < R&&c >= 0 && c < C;
	}

	void set_start_cell() {
		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
				if (grid[r][c] != '.') {
					start_cell = { r, c };
					return;
				}
			}
		}
	}
	void rotate_90() {
		vector<vector<char>> new_grid(C,vector<char>(R));
		for (int new_r = 0; new_r < C; ++new_r) {
			for (int new_c = 0; new_c < R; ++new_c) {
				new_grid[new_r][new_c] = grid[R - 1 - new_c][new_r];
			}
		}
		grid = new_grid;
		swap(R, C);
	}
	void flip() {
		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
				swap(grid[r][c], grid[r][C - 1 - c]);
			}
		}
	}

	void fill_matches(int my_r, int my_c, Pic& match_pic) {
		match_pic.visited.assign(match_pic.R, vector<bool>(match_pic.C, false));
		vii covered_cells;
		bool res = DFS(my_r, my_c, match_pic.start_cell.first, 
			match_pic.start_cell.second, match_pic, covered_cells);
		if (res)
			match_pic.solutions.push_back(covered_cells);
	}
	bool DFS(int my_r, int my_c, int his_r, int his_c, 
		Pic& match_pic, vii& covered_cells) {
		covered_cells.push_back({ my_r, my_c });
		match_pic.visited[his_r][his_c] = true;
		for (int i = 0; i < moves.size(); ++i) {
			int my_new_r = my_r + moves[i].first;
			int my_new_c = my_c + moves[i].second;
			int his_new_r = his_r + moves[i].first;
			int his_new_c = his_c + moves[i].second;
			if (match_pic.legal_move(his_new_r, his_new_c) &&
				!match_pic.visited[his_new_r][his_new_c] &&
				match_pic.grid[his_new_r][his_new_c] != '.') {

				if (legal_move(my_new_r, my_new_c) &&
					match_pic.grid[his_new_r][his_new_c] == 
					grid[my_new_r][my_new_c]) {
					bool res = DFS(my_new_r, my_new_c, his_new_r, his_new_c, match_pic, covered_cells);
					if (!res) {
						covered_cells.clear();
						return false;
					}
				}
				else {
					covered_cells.clear();
					return false;
				}
			}
		}
		return true;
	}
};

vii Pic::moves = { { 1, 0 }, { -1, 0 }, { 0, -1 }, { 0, 1 } };

struct Piece {
	Piece() {}
	Piece(Pic& pic) {
		grids.resize(8);
		for (int i = 0; i < 4; ++i) {
			grids[i] = pic;
			pic.rotate_90();
		}
		pic.flip();
		for (int i = 0; i < 4; ++i) {
			grids[4+i] = pic;
			pic.rotate_90();

		}
	}
	void fill_top_left_locs(Pic& start_pic) {
		for (int i = 0; i < grids.size(); ++i) {
			grids[i].set_start_cell();
			// now we'll try every cell of start_pic to be a start cell 
			for (int r = 0; r < start_pic.R; ++r) {
				for (int c = 0; c < start_pic.C; ++c) {
					start_pic.fill_matches(r, c, grids[i]);
				}
			}
		}
	}

	vector<Pic> grids; //8 perspectives
};

bool possible(Pic& start_pic, vector<Piece>& pieces, int i, int j, int k) {
	vi pieces_tiles;
	pieces_tiles.assign(26, 0);
	for (int c = 0; c < 26; ++c) {
		if (start_pic.tiles[c] != pieces[i].grids[0].tiles[c] +
							   	  pieces[j].grids[0].tiles[c] +
								  pieces[k].grids[0].tiles[c]  ) 
			return false;
	}
	return true;
}

void solve(Pic& start_pic, vector<Piece>& pieces, int I, int J, int K, ll &res)
{
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			for (int k = 0; k < 8; ++k) {
				for (int ci = 0; ci < pieces[I].grids[i].solutions.size(); ++ci) {
					for (int cj = 0; cj < pieces[J].grids[j].solutions.size(); ++cj) {
						for (int ck = 0; ck < pieces[K].grids[k].solutions.size(); ++ck) {
							set<ii> covered_cells;
							covered_cells.insert(pieces[I].grids[i].solutions[ci].begin(), 
												 pieces[I].grids[i].solutions[ci].end());
							covered_cells.insert(pieces[J].grids[j].solutions[cj].begin(),
												 pieces[J].grids[j].solutions[cj].end());
							covered_cells.insert(pieces[K].grids[k].solutions[ck].begin(),
												 pieces[K].grids[k].solutions[ck].end());

							if (covered_cells == start_pic.cell_set) {
								res++;
								return;
							}
						}
					}
				}
			}
		}
	}
	
}
int main() {
	/*ios_base::sync_with_stdio(false);
	cin.tie(0);*/
	//start_timer();

	ifstream fin("bcs.in");
	int K, R, C;
	fin >> K;
	fin >> R >> C;
	Pic start_pic(R, C);
	char in;
	for (int r = 0; r < R; ++r) {
		for (int c = 0; c < C; ++c) {
			fin >> in;
			start_pic.grid[r][c] = in;
			if (in != '.') {
				start_pic.tiles[in - 'a']++;
				start_pic.cell_set.insert({ r, c });
			}
		}
	}
	vector<Piece> pieces(K);
	for (int i = 0; i < K; ++i) {
		fin >> R >> C;
		Pic temp_pic(R, C);
		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
				fin >> in;
				temp_pic.grid[r][c] = in;
				if (in != '.')
					temp_pic.tiles[in-'a']++;
			}
		}
		pieces[i] = Piece(temp_pic);
		pieces[i].fill_top_left_locs(start_pic);
	}
	fin.close();

	ll res = 0;
	for (int i = 0; i < K; ++i) {
		for (int j = i + 1; j < K; ++j) {
			for (int k = j + 1; k < K; ++k) {
				if (!possible(start_pic, pieces, i, j, k))
					continue;

				solve(start_pic, pieces, i,j,k, res);
			}
		}
	}

	ofstream fout("bcs.out");
	fout << res << '\n';
	fout.close();

	//print_timer();
	return 0;
}