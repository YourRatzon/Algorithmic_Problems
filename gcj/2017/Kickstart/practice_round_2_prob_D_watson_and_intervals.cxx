//#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

/*
ID: jamerz1
PROG: hidden
LANG: C++11
*/

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

double EPS_ = 1e-16;
bool eq_(const double& lhs, const double &rhs) {
	return (fabs(lhs - rhs) < EPS_);
}

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned int uint;
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

struct Event {
	Event(ll t, int i, bool s) : time(t), id(i), start(s) {}
	ll time;
	int id;
	bool start;

	bool operator <(const Event& rhs) {
		return this->time < rhs.time;
	}
};

int main()  {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	ifstream fin("a.in");
	ofstream fout("a2.out");
	int T;
	fin >> T;
	for (int t = 0; t < T; ++t) {
		vll X, Y;
		vllll LR;
		map<int, ll> active_events;
		vector<Event> times;
		vll covered;

		ll N, L1, R1, A, B, C1, C2, M;
		fin >> N >> L1 >> R1 >> A >> B >> C1 >> C2 >> M;
		X.resize(N), Y.resize(N), LR.resize(N);
		covered.assign(N, 0);
		X[0] = L1, Y[0] = R1, LR[0].first = L1, LR[0].second = R1;
		for (int i = 1; i < N; ++i) {
			X[i] = (A*X[i - 1] + B*Y[i - 1] + C1) % M;
			Y[i] = (A*Y[i - 1] + B*X[i - 1] + C2) % M;
			LR[i].first = min(X[i], Y[i]);
			LR[i].second = max(X[i], Y[i]);
		}
		for (int i = 0; i < N; ++i) {
			times.push_back(Event(LR[i].first,  i, true));
			times.push_back(Event(LR[i].second, i, false));
		}
		sort(LR.begin(), LR.end());

		sort(times.begin(), times.end());

		ll total_covered = 0;
		ll max_covered = 0;

		active_events[times[0].id] = times[0].time;
		ll last_time = times[0].time;
		ll first_start = times[0].time;
		bool last_start = true;
		for (int i = 1; i < times.size(); ++i) {
			if (active_events.size() == 1) {
				ll diff = times[i].time - last_time;
				if (times[i].start != last_start) {
					if (last_start)
						diff++;
					else
						diff--;
				}
				int last_id = active_events.begin()->first;
				covered[last_id] += diff;
				max_covered = max(max_covered, covered[last_id]);

				if (!times[i].start) {
					total_covered +=
						(times[i].time - first_start + 1);
				}
			}
			if (!times[i].start) {
				active_events.erase(times[i].id);
				last_time = times[i].time;
				last_start = false;
			}
			else {
				if (active_events.empty()) {
					first_start = times[i].time;
					last_time = times[i].time;
					last_start = true;
				}
				active_events[times[i].id] = times[i].time;
			}
		}
		fout << "Case #" << t + 1 << ": " << total_covered-max_covered << '\n';
	}
	return 0;
}