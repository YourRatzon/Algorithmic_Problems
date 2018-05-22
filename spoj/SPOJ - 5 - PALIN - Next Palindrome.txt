// C++03
#include <cstring>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
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

#include <iostream>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;


const int MAX = 1000005;

bool all9s(char* K, int currSize)
{
	for (int i = 0; i < currSize; ++i)
	{
		if (K[i] != '9')
			return false;
	}
	string result(currSize + 1, '0');
	result[0] = '1';
	result[currSize] = '1';
	cout << result << '\n';
	return true;
}

int main()
{
	srand(time(NULL));

	int T;

	char K[MAX];
	gets(K);
	T = atoi(K);

	for (int i = 0; i < T; ++i)
	{

		gets(K);

		int index = 0;
		for (index = 0; K[index] != '\0'; ++index);
		int currSize = index;

		if (currSize == 1 && K[0] < '9')
		{
			K[0]++;
			printf("%s\n", K);
			continue;
		}

		if (all9s(K, currSize)) continue;

		int L = currSize / 2 - 1;
		int R = (currSize % 2 == 0 ? currSize / 2 : currSize / 2 + 1);
		int bigger = false;

		for (; L >= 0; L--, R++)
		{
			if (K[L] == K[R]) continue;
			else if (!bigger && K[L] < K[R])
			{
				L = currSize / 2 - 1;
				R = (currSize % 2 == 0 ? currSize / 2 : currSize / 2 + 1);
				if (L + 2 == R && K[L + 1] < '9')
				{
					K[L + 1] ++;
					bigger = true;
					K[R] = K[L];
				}
				else if (L + 2 == R && K[L + 1] == '9')
				{
					K[L + 1] = '0';
					while (K[L] == '9' && K[R] == '9')
					{
						K[L] = '0';
						K[R] = '0';
						L--; R++;
					}
					K[L]++; K[R] = K[L];
					bigger = true;
				}
				else if (L + 1 == R)
				{
					while (K[L] == '9' && K[R] == '9')
					{
						K[L] = '0';
						K[R] = '0';
						L--; R++;
					}
					K[L]++; K[R] = K[L];
					bigger = true;
					L--; R++;
					if (L >= 0 && R < currSize)
						K[R] = K[L];
				}
			}
			else
			{
				K[R] = K[L];
				bigger = true;
			}
		}

		if (!bigger)
		{
			if (currSize % 2 == 1)
			{
				L = currSize / 2;
				if (K[L] < '9') K[L] ++;
				else
				{
					L = currSize / 2 - 1;
					R = currSize / 2 + 1;
					K[currSize / 2] = '0';
					while (K[L] == '9' && K[R] == '9')
					{
						K[L] = '0';
						K[R] = '0';
						L--; R++;
					}
					K[L]++; K[R] = K[L];
				}
			}
			else
			{
				L = currSize / 2 - 1;
				R = currSize / 2;
				while (K[L] == '9' && K[R] == '9')
				{
					K[L] = '0';
					K[R] = '0';
					L--; R++;
				}
				K[L]++; K[R] = K[L];
			}
		}
		printf("%s\n", K);
	}

	return 0;
}

