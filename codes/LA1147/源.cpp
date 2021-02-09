#pragma warning(disable:4996)
#include <iostream>
#include <vector>
using namespace std;
struct tree
{
	tree* lchild = NULL;
	tree* rchild = NULL;
	int data;
};
tree* bt = new tree;
void isMaxHeap(vector<int>& t, int n)
{
	bool isMax = true;
	for (int i = 3; i < n; i++)
	{
		if (2 * i < n)
		{
			if (t[i] < t[2 * i])
			{
				isMax = false;
				break;
			}
		}
		else
			break;
		if (2 * i + 1 < n)
		{
			if (t[i] < t[2 * i + 1])
			{
				isMax = false;
				break;
			}
		}
		else
			break;

	}
	if (isMax)
		printf("Max Heap\n");
	else
		printf("Not Heap\n");
}

void isMinHeap(vector<int>& t, int n)
{
	bool isMin = true;
	for (int i = 3; i < n; i++)
	{
		if (2 * i < n)
		{
			if (t[i] > t[2 * i])
			{
				isMin = false;
				break;
			}
		}
		else
			break;
		if (2 * i + 1 < n)
		{
			if (t[i] > t[2 * i + 1])
			{
				isMin = false;
				break;
			}
		}
		else
			break;
	}
	if (isMin)
		printf("Min Heap\n");
	else
		printf("Not Heap\n");
}
int main() 
{
	int c = 0,n = 0;
	cin >> c >> n;
	for (int line = 0; line < c; line++)
	{
		vector<int> t(n+1);
		for (int i = 1; i <= n; i++)
			cin >> t[i];

		bt->data = t[1];
		bt->lchild = new tree;
		bt->lchild->data = t[2];

		if (t[1] > t[2])//按照大根堆比较
			isMaxHeap(t, n);
		else
			isMinHeap(t, n);

	}
	return 0;
}