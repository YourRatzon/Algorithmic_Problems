
/*
Google Code Jam
Qualification Round 2013

Problem A: Tic-Tac-Toe-Tomek
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

class Player
{
public:
	int maxR, maxC, maxD1, maxD2;
	Player() : maxR(0), maxC(0), maxD1(0), maxD2(0) {};
};

class TicTac
{
public:
	char Board[4][4];
	Player pX, pO;
	bool end;
	
	bool checkP(Player p, char ch)
	{
		char row, col, d1, d2;
		end = true;
		int i, j;

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				row = Board[i][j];
				col = Board[j][i];
				
				if (row == '.')
					end = false;

				if (row == ch || row == 'T')
					p.maxR++;
				else
					p.maxR = 0;

				if (col == ch || col == 'T')
					p.maxC++;
				else
					p.maxC = 0;
			}

			if (p.maxC == 4 || p.maxR == 4)
				return 1;
			else
			{ p.maxC = 0; p.maxR = 0; }


			d1 = Board[i][i];
			d2 = Board[i][3-i];
			if (d1 == ch || d1 == 'T')
				p.maxD1++;
			else
				p.maxD1 = 0;
			if (d2 == ch || d2 == 'T')
				p.maxD2++;
			else
				p.maxD2 = 0;
		}
		
		if (p.maxD1 == 4 || p.maxD2 == 4)
			return 1;
		else
			return false;
	}
};


int main()
{
	ifstream fin("A-large-practice.in");
	ofstream fout("output.out");

	int x;
	fin >> x;
	fin.get();
	string line;
	int n = 1;

	TicTac TTT;
	Player pX, pO;
	bool win;

	while (n <= x)
	{
		fout <<"Case #" <<n++<<": ";

		for (int i = 0; i < 4; i ++)
		{
			getline(fin, line);
			for (int j = 0; j < 4; j++)
				TTT.Board[i][j] = line[j];
		}
		getline(fin, line); // gets rid of the space


		win = TTT.checkP(pX, 'X');
		if (win)
		{
			fout<<"X won";
			fout<<endl;
			continue;
		}

		win = TTT.checkP(pO, 'O');
		if (win)
		{
			fout<<"O won";
			fout<<endl;
			continue;
		}
		
		else if (!TTT.end)
		{
			fout<<"Game has not completed";
			fout<<endl;
			continue;
		}

		else
		{
			fout<<"Draw";
			fout<<endl;
			continue;
		}
		

		
	}
	return 0;
}
