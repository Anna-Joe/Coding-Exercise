#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
using namespace std;

struct node
{
	int data;
	vector<int> child;
}a[101];

vector<int> tmpPath;
int sum = 0,l = 0,L = 0;
int n, m, w;

bool cmp(int x, int y)
{
	return a[x].data > a[y].data;
}
void dfs(int root)
{
	tmpPath.emplace_back(a[root].data);
	sum += tmpPath[l++];
	if (a[root].child.size() == 0)
	{
		if (sum == w)
		{
			cout << tmpPath[0];
			for (int i = 1; i < l; i++)
				cout << " " << tmpPath[i];
			cout << endl;
		}
		sum -= tmpPath[--l];
		tmpPath.pop_back();
		return;
	}
	else
	{
		for (int i = 0; i < a[root].child.size(); i++)
			dfs(a[root].child[i]);
		sum -= tmpPath[--l];
		tmpPath.pop_back();
	}
}

int main()
{
	cin >> n >> m >> w;
	for (int i = 0; i < n; i++)
		cin >> a[i].data;
	for (int i = 0; i < m; i++)
	{
		int id, k;
		cin >> id >> k;
		for (int j = 0; j < k; j++)
		{
			int ch;
			cin >> ch;
			a[id].child.emplace_back(ch);
		}
		sort(a[id].child.begin(), a[id].child.end(), cmp);
	}

	dfs(0);

	return 0;

}