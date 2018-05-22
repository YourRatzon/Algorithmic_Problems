#define _CRT_SECURE_NO_WARNINGS

// C++11
#include <tuple>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <array>



// C++03
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h> 
#include <iomanip>
#include <queue> 
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

const int SIZE = 31664;
vector<int> primeVec;
bitset<SIZE + 1> primeBS;
map<int, int> primeMAP;

void sieve(long long max)
{
	primeBS.set();
	primeBS[0] = primeBS[1] = 0;
	// once i > sqrt(max), the loop will be skipped, and i will just be added
	// as prime if primes[i].
	for (long long i = 2; i <= max; ++i)
	{
		if (primeBS[i])
		{
			for (long long j = i * i; j <= max; j += i)
				primeBS[j] = false;
			primeVec.push_back(i);
		}
	}
}

int main()
{

	sieve(SIZE);
	int t;
	int m, n;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i)
	{
		scanf("%d%d", &m, &n);
		for (int j = m; j <= n; ++j)
		{
			if (j <= SIZE)
			{
				if (primeBS[j])
					printf("%d\n", j);
			}
			else
			{
				int k;
				if (primeMAP[j] == 1)
					printf("%d\n", j);
				else if (primeMAP[j] != 2)
				{
					for (k = 0; k < primeVec.size(); ++k)
					{
						if (primeVec[k] * primeVec[k] > j)
						{
							k = primeVec.size();
							break;
						}
						if (j % primeVec[k] == 0)
						{
							primeMAP[j] = 2;
							break;
						}
					}
					if (k > 0 && k == primeVec.size())
					{
						primeMAP[j] = 1;
						printf("%d\n", j);
					}
				}
			}
		}
		printf("\n");
	}
	return 0;
}