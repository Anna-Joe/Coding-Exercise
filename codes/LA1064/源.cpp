#pragma warning(disable:4996)

#include <iostream>
#include <algorithm>
using namespace std;

int in[1010], level[1010], n, t = 0;

void inOrder(int root)
{
	if (root >= n)
		return;
	inOrder(2 * root );
	level[root] = in[t++];
	inOrder(2 * root + 1);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &in[i]);

	sort(in, in + n);
	inOrder(1);

	printf("%d", level[0]);
	for(int i = 1; i < n; i++)
		printf(" %d", level[i]);

}