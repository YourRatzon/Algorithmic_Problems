

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

int N;
vi nums;

//int solve(list<int>::iterator L, list<int>::iterator R) {
//	for (int num = 1; num < 58; ++num) {
//		auto it = L;
//		while (it != R) {
//			if (nums.size() == 1)
//				return nums.front();
//
//			int num_count = 0;
//			if (*it == num) {
//				auto save_it = it;
//				while (it != R && *it == num) {
//					++it;
//					++num_count;
//				}
//				if (it == R && *it == num)
//					++num_count;
//				// remove the nums before recursive calls
//				if (save_it == L) {
//					nums.erase(save_it, it);
//					if (nums.empty()) {
//						nums = list<int>(num_count / 2, num + 1);
//						return solve(nums.begin(), prev(nums.end()));
//					}
//					else
//						nums.insert(it, num_count / 2, num + 1);
//					return solve(prev(it, num_count / 2), R);
//				}
//				else {
//					nums.erase(save_it, it);
//					nums.insert(it, num_count / 2, num + 1);
//				}
//				if (num_count % 2 == 1) {
//					int left_res = solve(L, prev(it));
//
//					nums.insert(it, num_count / 2, num + 1);
//					int right_res = solve(prev(it,num_count/2), R);
//
//					return max(left_res, right_res);
//				}
//			}
//			else {
//				++it;
//			}
//		}
//	}
//	int res = 0;
//	for (auto it = L; L != next(R); ++L)
//		res = max(res, *it);
//	return res;
//}

int solve(vi nums) {
	for (int num = 1; num < 58; ++num) {
		int idx = 0;
		while (idx < nums.size()) {
			if (nums.size() == 1)
				return nums[0];
			int num_count = 0;
			if (nums[idx] == num) {
				int save_idx = idx;
				while (idx < nums.size() && nums[idx] == num) {
					++idx;
					++num_count;
				}
				// remove the nums before recursive calls

				
				for (int i = save_idx; i < save_idx + num_count / 2; ++i)
					nums[i] = num + 1;
				nums.erase(nums.begin() + save_idx + num_count / 2, nums.begin() + idx);

				idx = save_idx + num_count / 2;

				if (num_count % 2 == 1) {
					int left_res = solve(vi(nums.begin(), nums.begin() + idx));
					int right_res = solve(vi(nums.begin() + save_idx, nums.end()));
					return max(left_res, right_res);
				}
			}
			else {
				++idx;
			}
		}
	}
	int res = 0;
	for (int x : nums)
		res = max(res, x);
	return res;
}
int main() {
	/*ios_base::sync_with_stdio(false);
	cin.tie(0);*/
	//start_timer();

	ifstream fin("262144.in");
	fin >> N;
	int x;
	for (int i = 0; i < N; ++i) {
		fin >> x;
		nums.push_back(x);
	}
	fin.close();

	int res = solve(nums);
	ofstream fout("262144.out");
	fout << res << '\n';
	fout.close();

	//print_timer();
	return 0;
}