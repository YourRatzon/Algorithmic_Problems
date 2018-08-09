
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

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

const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 1e6 + 5;

bool terminal(vector<string> board) {
	if (board[0][0]!='.'&&board[0][0]==board[1][1]&&board[1][1]==board[2][2])
		return true;
	if (board[0][2]!='.'&&board[0][2]==board[1][1]&&board[1][1]==board[2][0])
		return true;
	for (int i = 0; i <3;++i) {
		if (board[i][0]!='.'&&board[i][0]==board[i][1]&&board[i][1]==board[i][2])
			return true;
		if (board[0][i]!='.'&&board[0][i]==board[1][i]&&board[1][i]==board[2][i])
			return true;
	}
	return false;
}

unordered_set<string> legal_boards;
void generate_legal_boards() {
	queue<pair<vector<string>,bool>> q;
	legal_boards.insert(".........");
	q.push({{"...","...","..."},true});
	while (!q.empty()) {
		pair<vector<string>,bool> pp = q.front();
		q.pop();
		vector<string> board = pp.first;
		bool x = pp.second;
		for (int i = 0; i <3;++i) {
			for (int j = 0; j < 3; ++j) {
					if (board[i][j] == '.') {
						board[i][j] = (x ? 'X' : 'O');
						string board_hash = board[0]+board[1]+board[2];
						if (legal_boards.count(board_hash) == 0) {
							legal_boards.insert(board_hash);
							if (!terminal(board))
								q.push({board, !x});
						}
						board[i][j] = '.';
					}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N;
	cin>>N;
	generate_legal_boards();
	for (int t = 0; t < N; ++t) {
		string board = "";
		string curr = "";
		for (int i = 0; i <3;++i) {
			cin>>curr;
			board += curr;
		}

		auto it = legal_boards.find(board);
		if (it != legal_boards.end())
			cout<<"yes\n";
		else
			cout<<"no\n";
	}

  return 0;
}
