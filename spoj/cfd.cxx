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
# define M_PI		3.14159265358979323846
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


# define M_PI		3.14159265358979323846
const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;
const int MAX_N = 2 * 1e5 + 1;

bitset<10000010> primeBS;
vi primes;
ll sieve_sz;

void sieve(ll max)
{
	sieve_sz = max + 1;
	primeBS.set();
	primeBS[0] = primeBS[1] = false;
	for (ll i = 2; i <= sieve_sz; ++i)
	{
		if (primeBS[i])
		{
			for (long long j = i * i; j <= sieve_sz; j += i)
				primeBS[j] = false;
			primes.push_back(i);
		}
	}
}


bool is_prime(ll N) {
	if (N <= sieve_sz)
		return primeBS[N];
	for (int i = 0; i < primes.size(); ++i)
		if (N % primes[i] == 0)
			return false;
	return true;
}

ll get_lower_prime(ll N) {
	if (is_prime(N)) 
		return N;
	N -= 2;
	while (!is_prime(N))
		--N;
	return N;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ll N;
	cin >> N;
	sieve(min(N, ll(1e7)));
	ll res = 0;
	ll curr = N;
	while (N > 1) {
		ll next_lower = get_lower_prime(N);
		cout << "next-lower: "<<next_lower << '\n';
		++res;
		N -= next_lower;
	}
	cout << res << '\n';
	return 0;
}