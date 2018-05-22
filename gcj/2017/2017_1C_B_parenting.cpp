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
const int MAXN = 1440;

int get_sz(ii lhs) {
	int ldiff;
	if (lhs.second>=lhs.first)
		ldiff = lhs.second - lhs.first;
	else
		ldiff = 1440 - lhs.first + lhs.second;
	return ldiff+1;
}

bool mysort(ii lhs, ii rhs) {
	int ldiff, rdiff;
	if (lhs.second>=lhs.first)
		ldiff = lhs.second - lhs.first;
	else 
		ldiff = 1440 - lhs.first + lhs.second;
	
	if (rhs.second >= rhs.first)
		rdiff = rhs.second - rhs.first;
	else
		rdiff = 1440 - rhs.first + rhs.second;

	return ldiff < rdiff;
}
int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	ifstream fin("b.in");
	ofstream fout("b.out");
	int T,Ac,Aj;
	int special = 424234;
	fin >> T;
	int s, e;
	for (int t = 0; t < T; ++t) {
		vc sched(MAXN, '.');
		set<ii> setJJinters, setCCinters, setJCinters, setCJinters;

		fin >> Ac >> Aj;
		int first_min=1440;
		int Cneed = 720, Jneed = 720;
		for (int i = 0; i < Ac; ++i) {
			fin >> s >> e;
			for (int j = s; j < e; ++j)
				sched[j] = 'J';
			Jneed -= (e - s);
			first_min = min(first_min, s);
		}
		for (int i = 0; i < Aj; ++i) {
			fin >> s >> e;
			for (int j = s; j < e; ++j)
				sched[j] = 'C';
			Cneed -= (e - s);
			first_min = min(first_min, s);
		}

		char L,R;
		int idx = first_min;
		int start, end;
		vc sched2(sched.begin(), sched.end());
		sched2.insert(sched2.end(), sched.begin(), sched.end());
		while (idx < sched2.size()) {
			while (idx < sched2.size() && sched2[idx] != '.')
				++idx;

			L = sched2[idx - 1];
			start = idx;

			while (idx < sched2.size() && sched2[idx] == '.')
				++idx;

			if (idx == sched2.size())
				break;

			R = sched2[idx];
			end = idx-1;

			if (start >= 1440) {
				start -= 1440;
			}
			if (end >= 1440) {
				end -= 1440;
			}

			if (L == 'J' && R == 'J')
				setJJinters.insert({ start, end });
			else if (L == 'C' && R == 'C')
				setCCinters.insert({ start, end });
			else if (L == 'J')
				setJCinters.insert({ start, end });
			else
				setCJinters.insert({ start, end });

		}

		vii JJinters(setJJinters.begin(), setJJinters.end());
		vii CCinters(setCCinters.begin(), setCCinters.end());
		vii JCinters(setJCinters.begin(), setJCinters.end());
		vii CJinters(setCJinters.begin(), setCJinters.end());

		sort(JJinters.begin(), JJinters.end(), mysort);
		sort(CCinters.begin(), CCinters.end(), mysort);
		sort(JCinters.begin(), JCinters.end(), mysort);
		sort(CJinters.begin(), CJinters.end(), mysort);

		for (int i = 0; i < JJinters.size() && Jneed > 0; ++i) {
			int sz = get_sz(JJinters[i]);
			for (int j = JJinters[i].first, k = 0; k < sz&& Jneed > 0; j = (j + 1) % 1440,++k, --Jneed) {
				sched[j] = 'J';
			}
		}
		for (int i = 0; i < CCinters.size() && Cneed > 0; ++i) {
			int sz = get_sz(CCinters[i]);
	
			for (int j = CCinters[i].first, k = 0;k < sz && Cneed > 0; j = (j + 1) % 1440, ++k, --Cneed) {
				sched[j] = 'C';
			}
		}
		for (int i = 0; i < JCinters.size() && Jneed > 0; ++i) {
			int sz = get_sz(JCinters[i]);

			for (int j = JCinters[i].first, k = 0; k < sz&& Jneed > 0; j = (j + 1) % 1440, ++k, --Jneed) {
				sched[j] = 'J';
			}
		}
		for (int i = 0; i < CJinters.size() && Cneed > 0; ++i) {
			int sz = get_sz(CJinters[i]);

			for (int j = CJinters[i].first, k = 0; k < sz && Cneed > 0; j = (j + 1) % 1440, ++k, --Cneed) {
				sched[j] = 'C';
			}
		}
		int res = 0;
		for (int i = 0; i < sched.size(); ++i) {
			if (sched[i] == '.') {
				if (Cneed) {
					sched[i] = 'C';
					--Cneed;
				}
				else if (Jneed) {
					sched[i] = 'J';
					--Jneed;
				}
			}
		}
		for (int i = 0; i < sched.size() - 1; ++i) {
			if (sched[i] != sched[i + 1])
				++res;
		}
		if (sched[0] != sched.back())
			++res;
		fout << "Case #" << t + 1 << ": " << res << '\n';
	}
	
	return 0;
}