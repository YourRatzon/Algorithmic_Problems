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
const ll INF_RES = ll(1e18);
const int MAX_X = 1e9 + 1;
const int MAX_Y = 1e9 + 1;
const int MAX_N = 50000;

set<int> x_set, y_set;
vii pts;
vi x_coords, y_coords;
int N;
vi min_y_st, max_y_st; // min_x_st, max_x_st;

int query_min(int l, int r, vi& seg_t) {
	int res = INF;
	l += N, r += N;
	for (; l < r; l /= 2, r /= 2) {
		if (l & 1)
			res = min(res, seg_t[l++]);
		if (r & 1)
			res = min(res, seg_t[--r]);
	}
	return res;
}

int query_max(int l, int r, vi& seg_t) {
	int res = -INF;
	l += N, r += N;
	for (; l < r; l /= 2, r /= 2) {
		if (l & 1)
			res = max(res, seg_t[l++]);
		if (r & 1)
			res = max(res, seg_t[--r]);
	}
	return res;
}


ll get_left_rect_area(int r_idx, int& l_y_min, int& l_y_max) {
	ll min_x = pts[0].first;
	ll max_x = pts[r_idx].first;
	l_y_min = query_min(0, r_idx+1, min_y_st);
	l_y_max = query_max(0, r_idx+1, max_y_st);
	ll min_y = l_y_min;
	ll max_y = l_y_max; 
	
	ll x_len = max_x - min_x;
	ll y_len = max_y - min_y;
	ll area;
	if (x_len <= 0 || y_len <= 0)
		area = 0;
	else
		area = x_len * y_len;
	return area;
}

ll get_right_rect_area(int l_idx, int& r_y_min, int& r_y_max) {
	ll min_x = pts[l_idx].first;
	ll max_x = pts.back().first;
	r_y_min = query_min(l_idx, pts.size(), min_y_st);
	r_y_max = query_max(l_idx, pts.size(), max_y_st);

	ll min_y = r_y_min;
	ll max_y = r_y_max;
	ll x_len = max_x - min_x;
	ll y_len = max_y - min_y;
	ll area;
	if (x_len <= 0 || y_len <= 0)
		area = 0;
	else
		area = x_len * y_len;
	return area;
}

//ll get_top_rect_area(int bottom) {
//	int min_x = MAX_X;
//	int max_x = 0;
//	int min_y = MAX_Y;
//	int max_y = 0;
//	int curr_x, curr_y;
//	for (int i = pts.size()-1; i >=0; --i) {
//		curr_x = pts[i].first, curr_y = pts[i].second;
//		if (curr_y >= bottom) {
//			min_x = min(min_x, curr_x);
//			max_x = max(max_x, curr_x);
//			min_y = min(min_y, curr_y);
//			max_y = max(max_y, curr_y);
//		}
//		else
//			break;
//	}
//
//	int x_len = max_x - min_x;
//	int y_len = max_y - min_y;
//	ll area;
//	if (x_len <= 0 || y_len <= 0)
//		area = 0;
//	else
//		area = ll(x_len) * ll(y_len);
//	return area;
//}

//ll get_bottom_rect_area(int top) {
//	int min_x = MAX_X;
//	int max_x = 0;
//	int min_y = MAX_Y;
//	int max_y = 0;
//	int curr_x, curr_y;
//	for (int i = 0; i < pts.size(); ++i) {
//		curr_x = pts[i].first, curr_y = pts[i].second;
//		if (curr_y <= top) {
//			min_x = min(min_x, curr_x);
//			max_x = max(max_x, curr_x);
//			min_y = min(min_y, curr_y);
//			max_y = max(max_y, curr_y);
//		}
//		else
//			break;
//	}
//
//	int x_len = max_x - min_x;
//	int y_len = max_y - min_y;
//	ll area;
//	if (x_len <= 0 || y_len <= 0)
//		area = 0;
//	else
//		area = ll(x_len) * ll(y_len);
//	return area;
//}

ll get_res_vert(int x_idx) {

	int l_y_min, l_y_max, r_y_min, r_y_max;
	ll left_area = get_left_rect_area(x_idx, l_y_min, l_y_max);
	ll right_area = get_right_rect_area(x_idx + 1, r_y_min, r_y_max);
	ll area = left_area + right_area;


	ll area2 = INF_RES;
	ll left_area2 = INF_RES;
	ll right_area2 = INF_RES;
	int l_y_min2, l_y_max2;
	if (x_idx > 0) {
		int line_min = query_min(x_idx, x_idx+1, min_y_st);
		int line_max = query_max(x_idx, x_idx+1, max_y_st);

		left_area2 = get_left_rect_area(x_idx - 1, l_y_min2, l_y_max2);
		
		if (l_y_max2 <= r_y_max) {
			if (l_y_min2 <= line_min && r_y_max >= line_max &&
				l_y_max2 >= r_y_min) {
				left_area2 += (l_y_max2 - l_y_min2);
				right_area2 = right_area + (r_y_max - r_y_min);
				area2 = left_area2 + right_area2;
			}
		} 
		else { // l_y_max2 > r_y_max
			if (l_y_max2 >= line_max && r_y_min <= line_min &&
				r_y_max >= l_y_min2) {
				left_area2 += (l_y_max2 - l_y_min2);
				right_area2 = right_area + (r_y_max - r_y_min);
				area2 = left_area2 + right_area2;
			}
		}
		

	}

	return min(area,area2);
}

//ll get_res_hori(int y_idx) {
//
//	ll bottom1_area = get_bottom_rect_area(y_mid - 1);
//	ll top1_area = get_top_rect_area(y_mid);
//	ll bottom2_area = get_bottom_rect_area(y_mid);
//	ll top2_area = get_top_rect_area(y_mid + 1);
//	ll bottom3_area = get_bottom_rect_area(y_mid);
//	ll top3_area = get_top_rect_area(y_mid);
//
//	ll area1 = bottom1_area + top1_area;
//	ll area2 = bottom2_area + top2_area;
//	ll area3 = bottom3_area + top3_area;
//
//
//	return min(area3,min(area1, area2));
//}

ll best_vert_split() {
	sort(pts.begin(), pts.end()); // sort by increasing x
	ll min_res = INF_RES;
	ll curr_res = 0;
	for (int i = 0; i < pts.size() - 1; ++i) {
		curr_res = get_res_vert(i);
		min_res = min(curr_res, min_res);
	}
	return min_res;
}

//ll best_hori_split() {
//	sort(pts.begin(), pts.end(), [](ii a, ii b) // sort by increasing y
//	{ return make_pair(a.second, a.first) < make_pair(b.second, b.first); }
//	);
//	ll min_res = INF_RES;
//	ll curr_res = 0;
//	for (int i = 0; i < pts.size() - 1; ++i) {
//		curr_res = get_res_hori(i);
//		min_res = min(curr_res, min_res);
//	}
//	return min_res;
//}


void build_seg_trees() {
	sort(pts.begin(), pts.end()); // sort by increasing x
	min_y_st.resize(N * 2);
	max_y_st.resize(N * 2);
	for (int i = 0; i < N; ++i) {
		min_y_st[N + i] = pts[i].second;
		max_y_st[N + i] = pts[i].second;
	}
	for (int i = N - 1; i > 0; --i) {
		min_y_st[i] = min(min_y_st[i * 2], min_y_st[i * 2 + 1]);
		max_y_st[i] = max(max_y_st[i * 2], max_y_st[i * 2 + 1]);
	}

	//sort(pts.begin(), pts.end(), [](ii a, ii b) // sort by increasing y
	//{ return make_pair(a.second, a.first) < make_pair(b.second, b.first); }
	//);
	//min_x_st.resize(N * 2);
	//max_x_st.resize(N * 2);
	//for (int i = 0; i < N; ++i) {
	//	min_x_st[N + i] = pts[i].first;
	//	max_x_st[N + i] = pts[i].first;
	//}
	//for (int i = N - 1; i >= 0; --i) {
	//	min_x_st[i] = min(min_x_st[i * 2], min_x_st[i * 2 + 1]);
	//	max_x_st[i] = max(max_x_st[i * 2], max_x_st[i * 2 + 1]);
	//}
}

int main() {
	/*ios_base::sync_with_stdio(false);
	cin.tie(0);*/
	//start_timer();

	ifstream fin("split.in");
	ofstream fout("split.out");
	fin >> N;
	pts.resize(N);
	int x, y;
	int min_x = MAX_X,max_x = 0,min_y = MAX_Y, max_y = 0;
	for (int i = 0; i < N; ++i) {
		fin >> x >> y;
		pts[i] = { x, y };
		x_set.insert(x);
		y_set.insert(y);

		min_x = min(min_x, x);
		max_x = max(max_x, x);
		min_y = min(min_y, y);
		max_y = max(max_y, y);
	}
	fin.close();

	for (int x : x_set)
		x_coords.push_back(x);
	for (int y : y_set)
		y_coords.push_back(y);

	ll one_block_area = (max_x - min_x)*(max_y - min_y);
	ll two_block_area;
	ll area_diff;
	if (x_coords.size() == 1 || y_coords.size() == 1) // area == 0 in all cases
		area_diff = 0;
	else {
		build_seg_trees();
		ll best_vert_res = best_vert_split();

		for (int i = 0; i < N; ++i)
			swap(pts[i].first, pts[i].second);

		build_seg_trees();

		ll best_hori_res = best_vert_split();

		two_block_area = min(best_vert_res, best_hori_res);
		area_diff = one_block_area - two_block_area;
	}
	fout << area_diff << '\n';
	fout.close();

	//print_timer();
	return 0;
}