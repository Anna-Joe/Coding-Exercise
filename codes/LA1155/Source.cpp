#pragma warning(disable:4996)
#include <iostream>
#include <vector>

using namespace std;
vector<int> v;
int  a[1009], n, isMin = 1, isMax = 1;

void dfs(int index)
{
	if (index * 2 > n)
	{
		if (index <= n)
		{
			for (int i = 0; i < v.size(); i++)
			{
				printf("%d%s", v[i], i != v.size() - 1 ? " ": "\n");
			}
		}
	}
	else
	{
		v.push_back(a[index * 2 + 1]);//先遍历右孩子
		dfs(index * 2 + 1);
		v.pop_back();

		v.push_back(a[index * 2]);//再遍历左孩子
		dfs(index * 2);
		v.pop_back();
	}

}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	v.push_back(a[1]);//遍历根节点
	dfs(1);

	for (int i = 2; i <= n; i++)
	{
		if (a[i / 2] > a[i]) isMin = 0;//孩子节点大于根节点
		if (a[i / 2] < a[i])isMax = 0;//根节点大于孩子节点
	}
	if (isMin == 1)
		printf("Min Heap");
	else
		printf("%s", isMax == 1 ? "Max Heap" : "Not Heap");

	return 0;
}