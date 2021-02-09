#pragma warning(disable:4996)
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


void adjust(int b[], int low, int high)
{
	int i = low, j = i * 2;//i的左孩子节点序号为i*2
	while (j <= high)
	{
		if (j + 1 <= high && b[j] < b[j + 1]) j++;
		if (b[i] >= b[j])break;
		swap(b[i], b[j]);
		i = j;
		j = i * 2;
	}
}

void heapSort(int a[], int n)
{
	int i = n;
	while (i > 2 && a[i] >= a[1])
		i--;

	swap(a[1], a[i]);

	adjust(a, 1, i - 1);
}


int main()
{
	int n = 0;
	cin >> n;
	int v1[101], v2[101];
	for (int i = 1; i <= n; i++)
		cin >> v1[i];
	for (int i = 1; i <= n; i++)
		cin >> v2[i];

	int k = 2;
	while (k <= n && v2[k] >= v2[k - 1])
		k++;

	bool isH = false;
	for (int i = k; i <= n; i++)
	{
		if (v1[i] != v2[i])
		{
			cout << "Heap Sort" << endl;
			isH = true;
			break;
		}
	}
	if (!isH)
	{
		cout << "Insertion Sort" << endl;
		sort(v2, v2 + k + 1);
		cout << v2[1];
		for (int i = 2; i <= n; i++)
			cout << " " << v2[i];
	}
	else
	{
		heapSort(v2, n);
		cout << v2[1];
		for (int i = 2; i <= n; i++)
			cout << " " << v2[i];
	}
	return 0;
}
