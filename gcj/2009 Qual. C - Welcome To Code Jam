// Code Jam - 2009 Qualification
// C. Welcome To Code Jam


#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <math.h> 
#include <iomanip>
#include <queue> 
#include <random>
#include <chrono>
#include <stdlib.h>    
#include <time.h> 
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <cstdio>
#include <ctime>
#include <list>
#include <set>
#include <tuple>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;


string getNumberOfSubstrings(string text)
{
	if (text.size() == 0)
		return "0000";
	string toFind = "welcome to code jam";
	vector < vector<unsigned long long> > DP(text.length());

	DP[0].resize(toFind.length());
	DP[0][0] = (text[0] == toFind[0]);
	for (int j = 1; j < toFind.length(); ++j)
		DP[0][j] = 0;

	for (int i = 1; i < text.length(); ++i)
	{
		DP[i].resize(toFind.length());
		DP[i][0] = DP[i - 1][0] + (text[i] == toFind[0]);
	}

	for (int i = 1; i < text.length(); ++i)
	{
		for (int j = 1; j < toFind.length(); ++j)
		{
			if (text[i] != toFind[j])
				DP[i][j] = DP[i - 1][j];
			else
				DP[i][j] = (DP[i - 1][j] + DP[i - 1][j - 1]) % 10000;
		}
	}
	return std::to_string(DP[text.size() - 1][toFind.size() - 1] );
}

int main()
{
	std::ifstream fin("C-large-practice.in");
	std::ofstream fout("output.out");
	int N;
	fin >> N;
	fin.get();
	string text;
	string resultStr;

	for (int i = 0; i < N; ++i)
	{
		getline(fin, text);
		resultStr = getNumberOfSubstrings(text);
		while (resultStr.length() < 4)
			resultStr.insert(0, "0");
		fout << "Case #" << i + 1 << ": " << resultStr << endl;			
	}


	system("pause");
	return 0;
}
