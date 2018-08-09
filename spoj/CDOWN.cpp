
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

int N, D, m;
int id_counter = 0;
vector<vi> adjlist;
vb is_root;
unordered_map<string,int> name_to_id;
unordered_map<int,string> id_to_name;
vector<vi> desc_counts;

void clear() {
	id_counter = 0;
	adjlist.clear();
	name_to_id.clear();
	id_to_name.clear();
	is_root.clear();
	desc_counts.clear();
}


int add_name(string name) {
	int id;
	auto it = name_to_id.find(name);
	if (it == name_to_id.end()) {
		id = id_counter++;
		name_to_id[name] = id;
		id_to_name[id] = name;
	}
	else {
		id = it->second;
	}
	return id;
}


void build_tree() {
	string name;
	cin >> N >> D;
	for (int i = 0; i < N; ++i) {
		cin>>name;
		int parent_id = add_name(name);
		while (parent_id >= adjlist.size())
			adjlist.push_back({});
		cin>>m;
		for (int j = 0; j < m; ++j) {
			cin>>name;
			int child_id = add_name(name);
            while (child_id >= adjlist.size())
                adjlist.push_back({});
			adjlist[parent_id].push_back(child_id);
		}
	}
}

int find_root() {
	is_root.assign(id_counter, true);
	for (int i = 0; i < adjlist.size(); ++i) {
		for (int j = 0; j < adjlist[i].size(); ++j) {
			int v = adjlist[i][j];
			is_root[v] = false;
		}
	}
	int root_id = 0;
	for (int i = 0; i < is_root.size(); ++i) {
		if (is_root[i]) {
			root_id = i;
			break;
		}
	}
	return root_id;
}

void set_dest_counts(int u) {
	for (int i = 0; i < adjlist[u].size();++i) {
		int v = adjlist[u][i];
		set_dest_counts(v);
	}

	desc_counts[u].push_back(0);
	int id = 0;
	desc_counts[u][id] += adjlist[u].size();
	id++;
	while (id < id_counter && desc_counts[u][id-1] > 0) {
		desc_counts[u].push_back(0);
		for (int i = 0; i < adjlist[u].size();++i) {
		    int v = adjlist[u][i];
		    if (desc_counts[v].size() > id-1)
		        desc_counts[u][id] += desc_counts[v][id-1];
		}
		++id;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin>>T;

	for (int t = 1; t<=T; ++t) {
		clear();
		build_tree();
		int root_id = find_root();
		desc_counts.assign(id_counter, vi());
		set_dest_counts(root_id);
		vi res(id_counter,0);
		for (int u = 0; u < id_counter; ++u) {
			if (desc_counts[u].size() > D-1)
				res[u] = desc_counts[u][D-1];
		}
		vi idxs(res.size());
		iota(idxs.begin(),idxs.end(),0);
		sort(idxs.begin(),idxs.end(),
				 [&res](int i,int j){return res[i]>res[j];});
		cout<<"Tree "<<t<<":\n";
		int id = 0;
		int res_count = 0;
		while (res_count < 3 && id < idxs.size()) {
            int curr_res = res[idxs[id]];
            if (curr_res == 0)
                break;

			vector<string> res_names;
			res_names.push_back(id_to_name[idxs[id]]);
			++id;
			while (id < idxs.size() && res[idxs[id]] == curr_res) {
				res_names.push_back(id_to_name[idxs[id]]);
				++id;
			}
			sort(res_names.begin(),res_names.end());
			for (string& name : res_names) {
				cout<<name <<' '<<curr_res<<'\n';
			}
			res_count += res_names.size();
		}
		if (t!=T)
		    cout<<'\n';
	}

  return 0;
}
