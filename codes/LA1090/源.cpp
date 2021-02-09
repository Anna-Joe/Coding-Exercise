#pragma warning(disable:4996)


#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct node
{
	int data;
	vector<int> child;
};

vector<node> v;
double maxP = 0;
int maxCount = 0;

int n;
double r;
double p;

vector<double> pList;
void dfs(int root, int depth)
{
	if (v[root].child.size() == 0)
	{
		double price = p * pow(1 + r / 100, depth);
		v[root].data = price;
		pList.emplace_back(price);
		if (price > maxP)
			maxP = price;
		return;
	}
	else
	{
		for (int i = 0; i < v[root].child.size(); ++i)
			dfs(v[root].child[i], depth + 1);
	}
}
int main()
{
	cin >> n >> p >> r;
	v.resize(n);
	int root = 0;
	for (int i = 0; i < n; ++i)
	{
		int k;
		cin >> k;
		if (k != -1)
			v[k].child.emplace_back(i);
		else
			root = i;
	}
	dfs(root, 0);

	for (int i = 0; i < pList.size(); i++)
	{
		if (pList[i] == maxP)
			maxCount++;
	}
	printf("%.2f %d", maxP, maxCount);
	return 0;
}