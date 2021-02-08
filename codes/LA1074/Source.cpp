#pragma warning(disable:4996)
#include <iostream>
#include <algorithm>

using namespace std;

struct node
{
	int pre;
	int addr;
	int data;
	int next;
};

node nodes[100001];
node sortedNodes[100001];
int main()
{
	int s,n,k;
	scanf("%d %d %d", &s, &n,&k);
	for (int i = 0; i < n; i++)
	{
		int addr, data, next;
		scanf("%d %d %d", &addr, &data, &next);
		nodes[addr].addr = addr;
		nodes[addr].data = data;
		nodes[addr].next = next;
		nodes[next].pre = addr;
	}
	int cnt = 2;//有效节点
	int lastPos = s;
	int newS = -1;
	int last = -1;
	for (int i = nodes[s].next; i != -1; i = nodes[i].next)//从第二个元素开始遍历
	{
		node tmp = nodes[i];

		if (cnt <= k)
		{
			tmp.next = lastPos;
			lastPos = tmp.addr;
			sortedNodes[tmp.addr] = tmp;
			if (cnt == k)
				newS = i;
		}
		else if (cnt >= k+1)
		{
			if (cnt == k + 1)
				tmp.next = -1;
			else
				tmp.next = tmp.pre;
			sortedNodes[tmp.addr] = tmp;
		}

		cnt++;

	}
	nodes[s] = nodes[newS].addr;
	sortedNodes[s] = nodes[s];

	
	for (int i = newS; i != -1; i = sortedNodes[i].next)
	{
		printf("%05d %d ", sortedNodes[i].addr, sortedNodes[i].data);
		if (sortedNodes[i].next != -1)
			printf("%05d\n", sortedNodes[i].next);
		else
			printf("-1");
	}

	return 0;
}