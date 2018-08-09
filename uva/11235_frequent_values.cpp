#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;


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


const int INF = int(2e9);
const ll INF_LL = LLONG_MAX;
const ll MOD = 1e9 + 7;

struct Node {
	Node() {}
	Node(int _ans,int _lval,int _rval, int _freq,int _lfreq, int _rfreq) 		: ans(_ans), lval(_lval),rval(_rval),
		freq(_freq),Lfreq(_lfreq),Rfreq(_rfreq) {}
	int ans,lval, rval;
	int freq,Lfreq, Rfreq;
};

vector < Node > stree;
vi nums;

Node merge(Node u, Node v) {
	int mid_freq = 0, mid_val = 0;
	if (u.rval == v.lval) {
		mid_freq = u.Rfreq + v.Lfreq;
		mid_val = u.rval;
		if (mid_val == v.rval)
			v.Rfreq = mid_freq;
		if (mid_val == u.lval)
			u.Lfreq = mid_freq;
		if (u.freq >= mid_freq && u.freq >= v.freq)
			return Node(u.ans, u.lval, v.rval, u.freq, u.Lfreq, v.Rfreq);
		else if (v.freq >= mid_freq && v.freq >= u.freq)
			return Node(v.ans, u.lval, v.rval, v.freq, u.Lfreq, v.Rfreq);
		else //(mid_freq >= v.freq && mid_freq >= u.freq) 
			return Node(mid_val, u.lval, v.rval, mid_freq, u.Lfreq, v.Rfreq);
	}
	else if (u.freq > v.freq) {
		return Node(u.ans, u.lval, v.rval, u.freq, u.Lfreq, v.Rfreq);
	}
	else {
		return Node(v.ans, u.lval, v.rval, v.freq, u.Lfreq, v.Rfreq);
	}
}

void build_stree(int u, int tl, int tr) {
	if (tl == tr) {
		stree[u] = Node(nums[tl], nums[tl], nums[tl], 1, 1,1);
	}
	else {
		int tm = (tl + tr) / 2;
		build_stree(2 * u, tl, tm);
		build_stree(2 * u + 1, tm + 1, tr);
		stree[u] = merge(stree[2 * u], stree[2 * u + 1]);
	}
}

Node query(int u, int tl, int tr, int l, int r) {
	if (l > r)
		return Node(0,0,0,0,0,0);
	if (l == tl&&r == tr)
		return stree[u]; 
	int tm = (tl + tr) / 2;
	Node left_res = query(2*u, tl, tm, l, min(r, tm));
	Node right_res = query(2*u+1, tm + 1, tr, max(tm+1,l), r);
	return merge(left_res, right_res);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int N, Q;
	bool first = true;
	//ifstream cin("test.in");
	//ofstream cout("test.out");
	while (cin >> N && N != 0) {
		cin >> Q;
		nums.resize(N);
		stree.clear();
		stree.resize(4 * N);
		for (int i = 0; i < N; ++i)
			cin >> nums[i];
		build_stree(1, 0, N - 1);
		int l, r;
		for (int i = 0; i < Q; ++i) {
			cin >> l >> r;
			cout << query(1, 0, N - 1, l - 1, r - 1).freq << '\n';
		}
	}


	return 0;
}
