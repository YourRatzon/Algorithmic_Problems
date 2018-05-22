#include <iostream>
using namespace std;

int main()
{
	int num, budget, hotels, weeks;
	int price;
	int beds;
	int minCost = INT_MAX;

	while (true)
	{
		cin >> num; cin >> budget; cin >> hotels; cin >> weeks;
		for (int j = 0; j < hotels; ++j)
		{
			cin >> price;
			if (num * price > budget)
			{
				for (int i = 0; i < weeks; ++i)
					cin >> beds;
				continue;
			}
			for (int i = 0; i < weeks; ++i)
			{
				cin >> beds;
				if ((beds >= num) && (num * price < minCost))
					minCost = num * price;
			}
		}
		if (minCost == INT_MAX)
			cout << "stay home\n";
		else cout << minCost << endl;
		
		minCost = INT_MAX;
	}

	cin.get();
	return 0;
}