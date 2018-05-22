#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

const int NUM_CHARS = 26 * 2 + 2; // 54
const int SPACE_IDX = 26 * 2;
const int UNDER_IDX = 26 * 2 + 1;
int tran[257];

void fill_tran() {
	for (int i = 0; i < 26; ++i)
		tran['a' + i] = i;
	for (int i = 0; i < 26; ++i)
		tran['A' + i] = 26 + i;
	tran[' '] = SPACE_IDX;
	tran['_'] = UNDER_IDX;
}

struct TrieNode {
	TrieNode(char _let) : letter(_let), count(1), edges(NUM_CHARS, nullptr) {}
	char letter;
	int count;
	vector<TrieNode*> edges;
};

struct Topic {
	Topic();
	Topic(string _name) : topic_name(_name), children({}), visited(false) {
		prefix_trie = new TrieNode('!');
	}
	string topic_name;
	vector < Topic* > children;
	TrieNode* prefix_trie;
	bool visited;

	void add_string_to_trie(const string& to_add) {
		TrieNode* curr = prefix_trie;
		for (int i = 0; i < to_add.size(); ++i) {
			if (curr->edges[tran[to_add[i]]] == nullptr)
				curr->edges[tran[to_add[i]]] = new TrieNode(to_add[i]);
			else
				curr->edges[tran[to_add[i]]]->count++;
			curr = curr->edges[tran[to_add[i]]];
		}
	}

	void add_trie(TrieNode* my_curr, TrieNode* his_curr) {
		//TrieNode* his_root = his_curr;
		for (TrieNode* edge : his_curr->edges) {
			if (edge == nullptr)
				continue;
			int add_idx = tran[edge->letter];
			if (my_curr->edges[add_idx] == nullptr) {
				my_curr->edges[add_idx] = edge;
			}
			else {
				my_curr->edges[add_idx]->count += edge->count;
				add_trie(my_curr->edges[add_idx], edge);
			}
		}
		//free_trie_memory(his_root);
	}

	int get_count(const string& query) {
		TrieNode* curr = prefix_trie;
		for (int i = 0; i < query.size(); ++i) {
			curr = curr->edges[tran[query[i]]];
			if (curr == nullptr)
				return 0;
		}
		return curr->count;
	}
};

struct Query {
	Query(int _id, string _query) : id(_id), query_str(_query) {}
	int id;
	string query_str;
};

const int MAX_LEN = 5e6 + 5;
char topic_tree_str[MAX_LEN];
int tree_idx;
int tree_len;

int parse_next_topic() {
	int end_idx = tree_idx;
	while (end_idx < tree_len && topic_tree_str[end_idx] != ' ')
		++end_idx;
	return end_idx;
}

Topic * tree_root = nullptr;


void build_tree(Topic*& curr) {
	stack<Topic*> st;
	int end_idx = 0;
	while (tree_idx < tree_len) {
		if (topic_tree_str[tree_idx] == '(') {
			tree_idx += 2;
			end_idx = parse_next_topic();
			curr = new Topic(
				string(topic_tree_str + tree_idx, topic_tree_str + end_idx));
			st.push(curr);
			if (end_idx + 1 >= tree_len)
				return;
			tree_idx = end_idx + 1;
		}
		else {
			if (!st.empty()) {
				Topic* top = st.top();
				st.pop();
				if (!st.empty())
					st.top()->children.push_back(top);
			}
			if (tree_idx < tree_len && topic_tree_str[tree_idx] == ')') {
				if (tree_idx + 1 == tree_len)
					return;
				else
					tree_idx += 2;
			}
			else {
				end_idx = parse_next_topic();
				curr = new Topic(
					string(topic_tree_str + tree_idx, topic_tree_str + end_idx));
				if (tree_root == nullptr)
					tree_root = curr;
				st.push(curr);
				if (end_idx + 1 >= tree_len)
					return;
				tree_idx = end_idx + 1;
			}
		}

	}
}

void fill_topic_tree_tries(Topic* curr,
	unordered_map<string, vector<string>>& topic_to_questions) {

	queue<Topic*> q;
	q.push(curr);
	while (!q.empty()) {
		curr = q.front();
		q.pop();
		if (topic_to_questions.count(curr->topic_name) != 0) {
			for (string & q : topic_to_questions[curr->topic_name])
				curr->add_string_to_trie(q);
		}
		for (Topic* child : curr->children)
			q.push(child);
	}
}

void answer_queries(Topic* curr,
	unordered_map<string, vector<Query>>& topic_to_queries,
	vector<int>& query_id_to_count) {
	stack<Topic*> st;
	st.push(curr);
	while (!st.empty()) {
		curr = st.top();
		if (curr->visited) {
			for (Topic* child : curr->children)
				curr->add_trie(curr->prefix_trie, child->prefix_trie);

			for (Query &query : topic_to_queries[curr->topic_name]) {
				query_id_to_count[query.id] += 
					curr->get_count(query.query_str);
			}
			st.pop();
		}
		else {
			curr->visited = true;
			for (Topic* child : curr->children)
				st.push(child);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	fill_tran();
	int N, M, K;
	cin >> N, cin.get();
	cin.getline(topic_tree_str, MAX_LEN);
	tree_idx = 0;
	tree_len = strlen(topic_tree_str);
	Topic * curr = nullptr;
	build_tree(curr);
	unordered_map<string, vector<string>> topic_to_questions;
	cin >> M, cin.get();
	string topic_name, question;
	for (int i = 0; i < M; ++i) {
		getline(cin, topic_name, ':');
		cin.get();
		getline(cin, question);
		topic_to_questions[topic_name].push_back(question);
	}
	fill_topic_tree_tries(tree_root, topic_to_questions);
	topic_to_questions.clear();


	cin >> K, cin.get();
	unordered_map<string, vector<Query>> topic_to_queries;
	vector<int> query_id_to_count(K);
	string query;
	for (int i = 0; i < K; ++i) {
		getline(cin, topic_name, ' ');
		getline(cin, query);
		topic_to_queries[topic_name].push_back(Query(i, query));
	}

	answer_queries(tree_root, topic_to_queries, query_id_to_count);
	for (int i = 0; i < K; ++i)
		cout << query_id_to_count[i] << '\n';
	return 0;
}
