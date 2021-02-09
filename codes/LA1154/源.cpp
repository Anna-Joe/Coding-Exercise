#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <set>
using namespace std;
struct edge
{
	int v1;
	int v2;
};

int main()
{
	int n =0, m=0;
	scanf("%d %d",&n,&m);
	vector<edge> v(m);

	for (int i = 0; i < m; i++)
		scanf("%d %d", &v[i].v1, &v[i].v2);
	int k = 0;
	cin >> k;
	for (int i = 0; i < k; k++)
	{
		vector<int> color(n);
		set<int> colorType;
		for (int j = 0; j < n; j++)
		{
			cin >> color[j];
			colorType.insert(color[j]);
		}
		bool flag = false;
		for (int j = 0; j < m; j++)
		{
			if (color[v[j].v1] == color[v[j].v2])
			{
				flag = true;
				break;
			}
		}
		if (flag)
			printf("No\n");
		else
			printf("%d-color\n", colorType.size());
	}
	return 0;
}