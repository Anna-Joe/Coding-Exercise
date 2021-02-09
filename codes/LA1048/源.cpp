#pragma warning(disable:4996)

#include <iostream>
int a[1001];

using namespace std;

int main()
{
	int n, m, tmp;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tmp);
		a[tmp]++;//a是一个哈希集合
	}

	for (int i = 0; i < 1001; i++)
	{
		if (a[i])
		{
			a[i]--;
			if (m > i && a[m - i])
			{
				if(i < m-i)
					printf("%d %d", i, m - i);
				else
					printf("%d %d", m-i, i);

				return 0;
			}
			a[i]++;
		}
	}

	printf("No Solution");
	return 0;
}