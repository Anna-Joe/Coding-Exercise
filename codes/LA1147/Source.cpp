#pragma warning(disable:4996)

#include <iostream>
using namespace std;

int a[1005], m, n;
void postOrder(int index)
{
	if (index > n)return;
	else
	{
		postOrder(index * 2);
		postOrder(index * 2 + 1);
		printf("%d%s", a[index],index == 1?"\n":" ");
	}
}
int main()
{
	scanf("%d %d", &m, &n);
	while (m--)
	{
		int minn = 1, maxn = 1;
		for (int i = 1; i <= n; i++)scanf("%d", &a[i]);
		for (int i = 2; i <= n; i++)
		{
			if (a[i] > a[i / 2])maxn = 0;
			if (a[i] < a[i / 2])minn = 0;
		}

		if (maxn)printf("Max Heap\n");
		else if (minn)printf("Min Heap\n");
		else printf("Not Heap\n");
		postOrder(1);
	}
	return 0;
}