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
}a[1000001];

double ans=0.0,r,p;

void dfs(int root, int depth)
{
	if (a[root].child.size() == 0)//р╤вс╫з╣Ц
	{
		ans += a[root].data * pow(1 + r, depth);
		return;
	}
	else
	{
		for (int i = 0; i < a[root].child.size(); ++i)
			dfs(a[root].child[i], depth+1);
	}
}
int main()
{
	int n;
	scanf("%d %lf %lf", &n, &p, &r);
	//cin >> n >> p >> r;
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
			a[i].data = 0;
		}
		else
			cin >> a[i].data;
	}
	dfs(0, 0);
	printf("%.1f", ans * p);
	return 0;
}

