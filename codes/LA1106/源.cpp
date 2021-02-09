#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct node
{
	double data;
	vector<int> child;
	double price;
}a[1000001];

double r, p;
double lowestP = -1.0;
void dfs(int root, int depth)
{
	if (a[root].child.size() == 0)//р╤вс╫з╣Ц
	{
		a[root].price = a[root].data * pow(1 + r, depth);
		if (lowestP == -1.0 || a[root].price < lowestP)
			lowestP = a[root].price;
		return;
	}
	else
	{
		for (int i = 0; i < a[root].child.size(); ++i)
			dfs(a[root].child[i], depth + 1);
	}
}
int main()
{
	int n;
	scanf("%d %lf %lf", &n, &p, &r);
	r = r / 100;
	for (int i = 0; i < n; i++)
	{
		int k;
		cin >> k;
		if (k != 0)
		{
			a[i].child.resize(k);
			for (int j = 0; j < k; j++)
				cin >> a[i].child[j];
		}
		a[i].data = p;
	}
	dfs(0, 0);

	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (lowestP == a[i].price)
			count++;
	}

	printf("%.4f %d", lowestP,count);
	return 0;
}

