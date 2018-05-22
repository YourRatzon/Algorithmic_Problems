
/*
Google Code Jam
Qualification Round Africa 2010

Problem B: Reverse Words
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	ifstream fin("B-large-practice.in");
	ofstream fout("output.out");

	int x;
	fin >> x;
	fin.get();
	string line;
	int n = 1;
	char ch;

	while (getline(fin, line))
	{
		fout <<"Case #" <<n++<<": ";
		for (int i = 0, j = line.length() - 1; i < j; i++, j--)
		{
			ch = line[i];
			line[i] = line[j];
			line[j] = ch;
		}
		int k = 0, i = 0, space = 0;
		while (space < line.length()) 
		{
			if (space + 1 == line.length() || line[space + 1] == ' ')
			{
				for (k = space; i < k; i++, k--)
				{
					ch = line[i];
					line[i] = line[k];
					line[k] = ch;
				}
				i = space + 2;
			}
			space++;
		}
		
		fout<<line<<endl;
		//fout.clear();
		i++;
	}
	return 0;
}
