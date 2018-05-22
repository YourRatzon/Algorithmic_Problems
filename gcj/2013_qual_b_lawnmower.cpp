
/*
Google Code Jam 2013
Qualification Round - Problem B
Lawnmower
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
using namespace std;

void createLawn(int rows, int cols, int** &lawn)
{
	lawn = new int*[rows];
	for (int j = 0; j < rows; j++)
	{
		lawn[j] = new int[cols];
	}
}
void mowToMax(int** &myLawn, int** lawn, int rows, int cols)
{
	int max = 0;
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (lawn[i][j] > max)
				max = lawn[i][j];
		}
	}
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			myLawn[i][j] = max;
		}
	}
}

int findNewMax(int** lawn, int rows, int cols, int h)
{
	int max = 0, col, row;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (lawn[i][j] > max && lawn[i][j] < h)
			{
				max = lawn[i][j];
			}

		}
	}

	return max;
}

bool allowedCol(int** lawn, int rows, int col, int h)
{
	for (int i = 0; i < rows; i++)
	{
		if (lawn[i][col] > h)
			return false;
	}
	return true;
}
void mowCol(int** &myLawn, int rows, int col, int h)
{
	for (int i = 0; i < rows; i++)
	{
		myLawn[i][col] = h;
	}
}
bool allowedRow(int** lawn, int cols, int row, int h)
{
	for (int i = 0; i < cols; i++)
	{
		if (lawn[row][i] > h)
			return false;
	}
	return true;
}
void mowRow(int** &myLawn, int cols, int row, int h)
{
	for (int i = 0; i < cols; i++)
	{
		myLawn[row][i] = h;
	}
}
bool same(int** mylawn, int**lawn, int rows, int cols)
{
	for (int i = 0; i < rows; i++) 
	{
		for(int j = 0; j < cols; j++) 
		{
			if (mylawn[i][j] != lawn[i][j])
				return false;
		}
	}
	return true;
}
bool possibleLawn(int** &lawn, int rows, int cols)
{
	int ** myLawn = NULL;
	createLawn(rows, cols, myLawn);

	mowToMax(myLawn, lawn, rows, cols);
	int h = 100, newH;

	while (true)
	{
		newH = findNewMax(lawn, rows, cols, h);
		
		if (newH == h)
			break;
		h = newH;
		
		for (int i = 0; i < cols; i++)
		{
			if (allowedCol(lawn, rows, i, h))
				mowCol(myLawn, rows, i, h);

		}

		for (int i = 0; i < rows; i++)
		{
			if (allowedRow(lawn, cols, i, h))
				mowRow(myLawn, cols, i, h);
		}
	}

	bool answer = same(lawn, myLawn, rows, cols);
	for (int i = 0; i < rows; i++)
		delete[] myLawn[i];
	delete[] myLawn;

	return answer;
}



int main()
{
	ifstream fin("B-large-practice.in");
	ofstream fout("output.out");


	int n, rows, cols, h;
	int ** lawn = NULL;
	fin >> n;
	for (int q = 0; q < n; q++)
	{
		lawn = NULL;
		fin >> rows;
		fin >> cols;
		createLawn(rows, cols, lawn);
		for (int i = 0; i < rows; i++)
		{ 
			for (int j = 0; j < cols; j++)
			{
				fin >> h;
				lawn[i][j] = h;
			}
		}

		if (possibleLawn(lawn, rows, cols))
			fout << "Case #" << q + 1 << ": YES"<<endl;
		else if (q == n-1)
			fout << "Case #" << q + 1 << ": NO";
		else
			fout << "Case #" << q + 1 << ": NO"<<endl;

		for (int i = 0; i < rows; i++)
			delete[] lawn[i];
		delete[] lawn;
	}

	

	return 0;
}
