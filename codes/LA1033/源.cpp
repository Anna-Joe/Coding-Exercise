#pragma warning(disable:4996)
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct station
{
	double price;
	int distance;
};
bool cmp(station a, station b)
{
	return a.distance < b.distance;
}

station s[500];
int main()
{
	int c = 0, tDis = 0, pDis = 0, sCnt = 0;
	cin >> c >> tDis >> pDis >> sCnt;
	for (int i = 0; i < sCnt; i++)
	{
		scanf("%lf %d\n", &s[i].price, &s[i].distance);
	}
	sort(s, s + sCnt,cmp);

	int cDis = 0;
	int maxC = c * pDis;
	int k = 1;
	double tCost = 0;
	while (cDis < tDis)
	{
		vector<station> nearS;
		while (s[k].distance <= cDis + maxC)
		{
			nearS.push_back(s[k]);
			k++;
		}
		if (nearS.size() == 0)
			break;
		
		double minCost = nearS[1].price * (nearS[1].distance - cDis);
		int minIndex = 1;
		for (int i = 2; i < nearS.size(); i++)
		{
			double cost = nearS[i].price * (nearS[i].distance - cDis);
			if (cost < minCost)
			{
				minCost = cost;
				minIndex = i;
			}
		}

		k = minIndex;
		cDis += nearS[k].distance;
		tCost += minCost;
	}

	if (cDis < tDis)
	{
		printf("The maximum travel distance = %.2lf\n", double(cDis));
		return 0;
	}
	else
	{
		printf("%.2lf\n", tCost);
		return 0;
	}
}