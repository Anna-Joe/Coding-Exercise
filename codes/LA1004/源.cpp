#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> v[101];
int level[101],maxDepth = -1;
void dfs(int index, int depth)
{
	if (v[index].size() == 0)//没有孩子节点的节点认为是叶子节点
	{
		level[depth]++;
		maxDepth = max(maxDepth, depth);
		return;
	}
	else//遍历这个节点所有的孩子
	{
		for (int i = 0; i < v[index].size(); i++)
		{
			dfs(v[index][i], depth+1);
		}
	}
}

int main()
{
	int m, n;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int k,node;
		scanf("%d %d", &node, &k);
		for (int j = 0; j < k; j++)
		{
			int connect;
			scanf("%d", &connect);
			v[node].emplace_back(connect);
		}
	}

	dfs(1, 0);

	printf("%d", level[0]);
	for (int i = 1; i <= maxDepth; i++)
	{
		printf(" %d", level[i]);
	}
	return 0;
}