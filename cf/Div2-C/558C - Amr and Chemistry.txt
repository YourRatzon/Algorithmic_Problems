#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

/*
ID: jamerz1
PROG: milk4
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

#define F first
#define S second

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<ull> vull;
typedef vector<ll> vll;


template <class T>
T min_(T a, T b) { return (a < b ? a : b); }
template <class T>
T max_(T a, T b) { return (a > b ? a : b); }

const int INF = INT_MAX;
double EPS = 1e-10;
const int MAX_N = 1e5 + 1;
int MAX_VAL = 0;
int chem_counts[MAX_N];

typedef std::unordered_map<int, int> val_to_dist;
ii main_val_to_dist[MAX_N];


void build_main_branch(int chem) {
    val_to_dist curr_dist;
    queue<int> q;
    q.push(chem);
    curr_dist[chem] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int down = u / 2;
        int up = u * 2;
        if (down > 0 && curr_dist.count(down) == 0) {
            curr_dist[down] = curr_dist[u] + 1;
            q.push(down);
        }
        if (up <= MAX_VAL && curr_dist.count(up) == 0) {
            curr_dist[up] = curr_dist[u] + 1;
            q.push(up);
        }
    }
    for (auto e : curr_dist) {
        main_val_to_dist[e.first] = { 0, 0 };
    }
}

inline void build_branch(int chem) {
    val_to_dist curr_dist;
    queue<int> q;
    q.push(chem);
    curr_dist[chem] = 0;
    if (main_val_to_dist[chem].first != -1)
        main_val_to_dist[chem].second += 1 * chem_counts[chem];

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int down = u / 2;
        int up = u * 2;
        if (down > 0 && curr_dist.count(down) == 0) {
            curr_dist[down] = curr_dist[u] + 1;
            if (main_val_to_dist[down].first != -1) {
                main_val_to_dist[down].first += 
                    chem_counts[chem] * curr_dist[down];
                main_val_to_dist[down].second += chem_counts[chem];
            }
            q.push(down);
        }
        if (up <= MAX_VAL && curr_dist.count(up) == 0) {
            if (main_val_to_dist[up].first == -1)
                continue;
            else {
                curr_dist[up] = curr_dist[u] + 1;
                main_val_to_dist[up].first += 
                    chem_counts[chem] * curr_dist[up];
                main_val_to_dist[up].second += chem_counts[chem];
                q.push(up);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    //ifstream fin("out.out");
    cin >> n;
    int MIN_VAL = INF;
    int x = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        chem_counts[x]++;
        MAX_VAL = max(MAX_VAL, x);
        MIN_VAL = min(MIN_VAL, x);
    }

    for (int i = 0; i <= MAX_VAL; ++i)
        main_val_to_dist[i] = { -1, -1 };
    build_main_branch(MIN_VAL);

    for (int i = 0; i <= MAX_VAL; ++i) {
        if (chem_counts[i] > 0)
            build_branch(i);
    }

    int min_res = INF;
    for (int i = 0; i <= MAX_VAL; ++i)
        if (main_val_to_dist[i].second == n)
            min_res = min(min_res, main_val_to_dist[i].first);

    cout << min_res << '\n';

    return 0;
}