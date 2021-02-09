#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node
{
	int data;
	vector<int> child;
	int level;
};

vector<node> v;
map<int, int> generationChildren;
int largestG = 0 , largestL = 0;

void dfs(int root, int level)
{
	v[root].level = level;
	generationChildren[level]++;
	if (generationChildren[level] > largestG)
	{
		largestG = generationChildren[level];
		largestL = level;
	}

	if (v[root].child.size() == 0)		
		return;
	else
	{
		for (int i = 0; i < v[root].child.size(); ++i)
			dfs(v[root].child[i], level + 1);
	}

}
int main()
{
	int n, m;
	cin >> n >> m;
	v.resize(n+1);
	for (int i = 0; i < m; i++)
	{
		int id, k;
		cin >> id >> k;
		v[id].child.resize(k);
		for (int j = 0; j < k; j++)
			cin >> v[id].child[j];
	}

	dfs(1, 1);

	cout << largestG << " " << largestL;
	return 0;
}