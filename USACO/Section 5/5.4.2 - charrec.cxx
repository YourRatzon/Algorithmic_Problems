#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

/*
ID: jamerz1
PROG: charrec
LANG: C++11
*/

// C++11
#include <tuple>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <array>
#include <iterator>

// C++03
#include <assert.h>
#include <climits>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <queue>
#include <math.h>
#include <map>
#include <cstdio>
#include <ctime>
#include <list>
#include <set>
#include <stdio.h>
#include <bitset>
#include <functional> 
#include <locale>
#include <vector>
#include <streambuf>
#include <ctime>

#include <iostream>


//#define F first
//#define S second

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;

// fast input
#define scan_fast(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;

// TIMER
std::clock_t start;
double duration;
void start_timer() { start = std::clock(); }
void print_timer() {
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << '\n';
}
// END TIMER

template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

double EPS = 1e-10;
double PI = cos(-1);
const int INF = int(2e9);
#define M_PI       3.14159265358979323846

const int N_CHARS = 27;
const int CHAR_LEN = 20;

struct Match {
	Match() : matched_char('~'), duplicate_line(false), missing_line(false), diff_count(INF) {}
	char matched_char;
	bool duplicate_line;
	bool missing_line;
	int diff_count;
};

map < int, char > idx_to_letter{ { 0, ' ' }, { 1, 'a' }, { 2, 'b' }, { 3, 'c' }, { 4, 'd' }, { 5, 'e' }, { 6, 'f' }, { 7, 'g' }, { 8, 'h' }, { 9, 'i' }, { 10, 'j' }, { 11, 'k' }, { 12, 'l' }, { 13, 'm' }, { 14, 'n' }, { 15, 'o' }, { 16, 'p' }, { 17, 'q' }, { 18, 'r' }, { 19, 's' }, { 20, 't' }, { 21, 'u' }, { 22, 'v' }, { 23, 'w' }, { 24, 'x' }, { 25, 'y' }, { 26, 'z' } };


Match get_best_match(vector<string>& curr_char_stream,
	vector<vector<string>>& alphabet) {
	// find best match when removing each line 1-21
	int dupl_min_chars_mismatched = INF;
	char dupl_matched_char;
	for (int font_pic = 0; font_pic < alphabet.size(); ++font_pic) {
		for (int del_line = 0; del_line < curr_char_stream.size(); ++del_line){
			int curr_letter_diff = 0;
			bool fail = false;
			for (int curr_line = 0, font_line = 0; font_line < 20; ++curr_line, ++font_line) {
				if (curr_line == del_line)
					curr_line++;
				if (curr_line >= curr_char_stream.size()) {
					fail = true;
					break;
				}
				for (int j = 0; j < CHAR_LEN; ++j) {
					if (curr_char_stream[curr_line][j] !=
						alphabet[font_pic][font_line][j])
						curr_letter_diff++;
				}
			}
			if (curr_letter_diff <= 120 && !fail) {
				if (curr_letter_diff < dupl_min_chars_mismatched) {
					dupl_min_chars_mismatched = curr_letter_diff;
					dupl_matched_char = idx_to_letter[font_pic];
				}
			}
		}
	}

	int miss_min_chars_mismatched = INF;
	char miss_matched_char;
	// find best match by removing one line from each font pic and comparing to 19 first lines of char_stream
	for (int font_pic = 0; font_pic < alphabet.size(); ++font_pic) {
		for (int font_del_line = 0; font_del_line < CHAR_LEN; ++font_del_line){ // delete lines 0-19 iteratively
			int curr_letter_diff = 0;
			bool fail = false;
			for (int stream_line = 0, font_line = 0; stream_line < 19; ++stream_line, ++font_line) {
				if (font_line == font_del_line)
					font_line++;
				if (font_line >= 20) {
					fail = false;
					break;
				}
				for (int j = 0; j < CHAR_LEN; ++j) {
					if (curr_char_stream[stream_line][j] !=
						alphabet[font_pic][font_line][j])
						curr_letter_diff++;
				}
			}
			curr_letter_diff * double(20.0 / 19.0);
			if (curr_letter_diff <= 120 && !fail) {
				if (curr_letter_diff < miss_min_chars_mismatched) {
					miss_min_chars_mismatched = curr_letter_diff;
					miss_matched_char = idx_to_letter[font_pic];
				}
			}
		}
	}

	int reg_min_chars_mismatched = INF;
	char reg_matched_char;
	// find best match by comparing 20 lines of font pic to 20 lines of stream
	for (int font_pic = 0; font_pic < alphabet.size(); ++font_pic) {
		int curr_letter_diff = 0;
		for (int stream_line = 0, font_line = 0; stream_line < curr_char_stream.size() && font_line<20; ++stream_line, ++font_line) {
			for (int j = 0; j < CHAR_LEN; ++j) {
				if (curr_char_stream[stream_line][j] !=
					alphabet[font_pic][font_line][j])
					curr_letter_diff++;
			}
		}
		if (curr_letter_diff <= 120) {
			if (curr_letter_diff < reg_min_chars_mismatched) {
				reg_min_chars_mismatched = curr_letter_diff;
				reg_matched_char = idx_to_letter[font_pic];
			}
		}
	}

	Match res;
	if (reg_min_chars_mismatched < miss_min_chars_mismatched && reg_min_chars_mismatched < dupl_min_chars_mismatched) {
		res.matched_char = reg_matched_char;
		res.diff_count = reg_min_chars_mismatched;
	}

	else if (dupl_min_chars_mismatched < miss_min_chars_mismatched) {
	/*	if (dupl_min_chars_mismatched == INF)  {
			res.diff_count = INF;
			return res;
		} */
			res.matched_char = dupl_matched_char;
			res.diff_count = dupl_min_chars_mismatched;
			res.duplicate_line = true;
	}
	else { //if (miss_min_chars_mismatched < dupl_min_chars_mismatched && miss_min_chars_mismatched < reg_min_chars_mismatched) {
		if (miss_min_chars_mismatched == INF)  {
			res.diff_count = INF;
			return res;
		} 
		res.matched_char = miss_matched_char;
		res.diff_count = miss_min_chars_mismatched;
		res.missing_line = true;
	}
	return res;
}

int main() {

	//start_timer();
	//std::ios::sync_with_stdio(false);
	//cin.tie(0);

	ifstream fin("font.in");
	int font_lines;
	fin >> font_lines;
	vector<vector<string>> alphabet(N_CHARS, vector<string>(CHAR_LEN));
	for (int i = 0; i < N_CHARS; ++i) {
		for (int j = 0; j < CHAR_LEN; ++j) {
			fin >> alphabet[i][j];
		}
	}
	fin.close();
	fin.open("charrec.in");
	int N;
	fin >> N;
	vector<string> char_stream(N);
	for (int i = 0; i < N; ++i) {
		fin >> char_stream[i];
	}
	fin.close();

	ofstream fout("charrec.out");
	string res = "";
	int idx = 0;

	int right = min(21, int(char_stream.size()));
	vector<string> curr_char_stream(
		vector<string>(char_stream.begin(), char_stream.begin() + right));
	Match best_match = get_best_match(curr_char_stream, alphabet);
	res += best_match.matched_char;
	idx += 20;
	if (best_match.duplicate_line)
		idx++;
	else if (best_match.missing_line)
		--idx;
	while (idx < N) {
		if (N - idx < 19)
			break;
		best_match.diff_count = INF;
		int i_val = 0;
		for (int i = 0; i <6; ++i) {
			int right = min(idx+i+21, int(char_stream.size()));
			if (right-(idx+i) < 19)
				break;
			vector<string> curr_char_stream(
				vector<string>(char_stream.begin() + idx+i, char_stream.begin() + right));
			Match curr_match = get_best_match(curr_char_stream, alphabet);
			if (curr_match.diff_count < best_match.diff_count) {
				best_match = curr_match;
				i_val = i;
			}
		}
		res += best_match.matched_char;
		idx += 19;
		if (i_val>2)
		idx += i_val-2;
	}
	cerr << "<start> " << res << " <end>" << '\n';
	fout << res.c_str() << '\n';
	fout.close();


	//print_timer();
	return 0;
}