#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

struct node
{
	int pos;
	int data;
	int next = -1;
	int index = 200000;
};
bool cmp(node& a,node& b)
{
	return a.index < b.index;
}
node list[100000];
bool exist[100000] = { false };

int main()
{
	int s, n;
	scanf("%d %d", &s, &n);

	for (int i = 0; i < n; i++)
	{
		int pos, data, next;
		scanf("%d %d %d",&pos,&data,&next);
		list[pos].pos = pos;
		list[pos].data = data;
		list[pos].next = next;
	}
	int cnt1 = 0,cnt2 = 0;
	for (int i = s; i != -1; i = list[i].next)
	{
		if (!exist[abs(list[i].data)])
		{
			exist[abs(list[i].data)] = true;
			list[i].index = cnt1++;
		}
		else
		{
			list[i].index = 100000 + cnt2;
			cnt2++;
		}
	}
	sort(list, list+ 100000, cmp);
	int cnt = cnt1 + cnt2;
	for (int i = 0; i < cnt;i++)
	{
		if (i != cnt1-1 && i != cnt-1)
			printf("%05d %d %05d\n", list[i].pos, list[i].data, list[i + 1].pos);
		else
			printf("%05d %d -1\n", list[i].pos, list[i].data);
	}
	return 0;
}