
/*
Google Code Jam 2013
Qualification Round - Problem C - Large input 1
Fair and Square
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <list>
#include <iterator> 
#include <cctype>
#include <istream>
#include <ctime>
#include <algorithm>  
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

bool palindrome(string str)
{
	for (int i = 0, j = str.length() - 1; i < j; i++, j--)
	{
		if (str[i] == str[j])
			continue;
		else
			return false;
	}
	return true;
}

vector<unsigned long long> makePals()
{
	vector<unsigned long long> pals;
	unsigned long long prod;
	int counter = 1;

	for (unsigned long long i = 1; (i * i) <= 1e14; i++)
	//for (unsigned long long i = 1; (i * i) <= 1000; i++)
	{
		prod = i*i;
		if (palindrome(to_string(prod)) && palindrome(to_string(i)))
		{
			pals.push_back(prod);
			cout<<counter++<<": "<<prod<<endl;
		}
	}
	return pals;
}

int main()
{
	ifstream fin("C-large-practice-1.in");
	ofstream fout("output.out");
	if (!fin || !fout) perror("couldn't open one of the files: ");
	unsigned long long total = 0;
	unsigned long long n, from, to;
	fin >> n;
	vector<unsigned long long> pals;
	vector<unsigned long long>::iterator it;
	pals = makePals();


	for (unsigned long long i = 0; i < n; i++)
	{
		fin >> from;
		fin >> to;
		
		for (it = pals.begin(); it != pals.end(); it++)
		{
			if ((*it) < from)
				continue;
			if ((*it) > to)
				break;
			else
				total++;
		}

		fout << "Case #" << i + 1 <<": "<< total << endl;
		total = 0;
	}

	fin.close();
	fout.close();
	return 0;
}
