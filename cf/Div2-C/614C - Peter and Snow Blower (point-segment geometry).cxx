#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

/*
ID: jamerz1
PROG: tour
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

struct Point
{
	double x, y;

	Point() : x(), y() {}
	Point(double _x, double _y) : x(_x), y(_y) {}

	void scan()
	{
		scanf("%lf%lf", &x, &y);
	}

	Point operator + (const Point &a) const
	{
		return Point(x + a.x, y + a.y);
	}
	Point operator - (const Point &a) const
	{
		return Point(x - a.x, y - a.y);
	}
	Point operator * (const double &k) const
	{
		return Point(x * k, y * k);
	}
	Point operator / (const double &k) const
	{
		return Point(x / k, y / k);
	}
	double operator % (const Point &a) const
	{
		return x * a.x + y * a.y;
	}
	double operator * (const Point &a) const
	{
		return x * a.y - y * a.x;
	}
	double sqrLen() const
	{
		return *this % *this;
	}
	double len() const
	{
		return sqrt(sqrLen());
	}
	double distTo(const Point &a) const
	{
		return (*this - a).len();
	}

	Point norm() const
	{
		return *this / len();
	}
};

struct vec {
	vec(double _x, double _y) : x(_x), y(_y) {}
	double x, y;
};

vec toVec(Point a, Point b) {
	return vec(b.x - a.x, b.y - a.y);
}

double points_dist_sq(Point a, Point b) {
	double delta_x = a.x - b.x;
	double delta_y = a.y - b.y;
	return delta_x*delta_x + delta_y*delta_y;
}

vec scale(vec P1P2, double u){

	P1P2.x *= u;
	P1P2.y *= u;
	return P1P2;
}

Point translate(Point O, vec V){
	return{ O.x + V.x, O.y + V.y };
}

double dist_to_line(Point O, Point p1, Point p2) {
	vec P1P2 = toVec(p1,p2);
	vec P1O = toVec(p1, O);
	double u = (P1P2.x*P1O.x + P1P2.y*P1O.y) / (P1P2.x*P1P2.x + P1P2.y*P1P2.y);
	P1P2 = scale(P1P2, u);
	Point C = translate(p1, P1P2);
	return points_dist_sq(O, C);
}
double dist_to_nearest_pt_on_segment(Point O, Point p1, Point p2) {
	vec P1P2 = toVec(p1, p2);
	vec P1O = toVec(p1, O);
	double u = (P1P2.x*P1O.x + P1P2.y*P1O.y) / (P1P2.x*P1P2.x + P1P2.y*P1P2.y);
	if (u < 0.0) { // O is closer to p1
		return points_dist_sq(O, p1);
	}
	else if (u > 1.0) { // O is closer to p2
		return points_dist_sq(O, p2);
	}
	else
		return dist_to_line(O, p1, p2);
}

int main() {

	start_timer();
	std::ios::sync_with_stdio(false);
	cin.tie(0);

	int N;
	cin >> N;
	Point O;
	cin >> O.x >> O.y;
	vector<Point> points(N+1);
	for (int i = 0; i < N; ++i) {
		cin >> points[i].x;
		cin >> points[i].y;
	}
	points[N] = points[0];
	double max_rad_sq = 0;
	double min_rad_sq = 1e100;
	for (int i = 0; i < N; ++i){
		double curr_dist_sq = points_dist_sq(O, points[i]);
		max_rad_sq = max(max_rad_sq, curr_dist_sq);
		double nearest_pt_on_segment = dist_to_nearest_pt_on_segment(O, points[i], points[i + 1]);
		min_rad_sq = min(min_rad_sq, nearest_pt_on_segment);
	}

	cout << std::fixed;
	cout << std::setprecision(15);
	cout << M_PI*max_rad_sq - M_PI*min_rad_sq <<'\n';

	//print_timer();
	return 0;
}