// Google Code Jam - 2009 Qualification Round
// A. Alien Language

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <math.h> 
#include <queue> 
#include <random>
#include <chrono>
#include <stdlib.h>    
#include <time.h> 
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;

vector<string> splitToTokens(string pattern)
{
	vector<string> tokens;
	string token;

	for (int i = 0; i < pattern.length() ; )
	{
		int delimO = pattern.substr(i, pattern.length()).find("(");
		if (delimO == -1)
		{
			for (int j = i; j < pattern.length(); ++j)
				tokens.push_back(pattern.substr(j, 1));
			break;
		}
		for (int j = i; j < delimO + i; ++j)
			tokens.push_back(pattern.substr(j, 1));
		i += delimO + 1;
		if (i == pattern.length()) break;

		int delimC = pattern.substr(i, pattern.length()).find(")");
		token = pattern.substr(i, delimC);
		tokens.push_back(token);
		i += delimC + 1;
	}

	return tokens;
}

int main(int arg, char* argv[])
{
	
	std::ifstream fin("A-small-practice.in");
	std::ofstream fout("output.out");

	int L, D, N, K;
	fin >> L >> D >> N;
	fin.get(); //clear the \n char

	string word;
	vector<string> words;
	for (int i = 0; i < D; ++i)
	{
		getline(fin,word);
		words.push_back(word);
	}

	string pattern;
	vector<string> tokens;
	int count;

	for (int i = 0; i < N; ++i)
	{
		std::getline(fin,pattern);
		tokens = splitToTokens(pattern);
		count = 0;

		for (int j = 0; j < D; ++j)
		{
			int k;
			for (k = 0; k < words[j].length(); ++k)
			{
				if (tokens[k].find(words[j][k]) == -1)
				{
					k = 0;
					break;
				}
			}
			if (k == words[j].length())
				count++;
		}
	
		fout << "Case #" << i+1 << ": " << count <<endl;
	}

	system("pause");

	return 0;
}