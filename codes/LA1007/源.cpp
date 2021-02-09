#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> orgVector(n);
	int maxSum = 0, tmpSum = 0;
	int leftIndex = 0 , rightIndex = 0;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		orgVector[i] = a;
		tmpSum += a;
		if (tmpSum < 0)
		{
			tmpSum = 0;
			leftIndex = i + 1;
		}
		else if (tmpSum > maxSum)
		{
			maxSum = tmpSum;
			rightIndex = i;
		}
	}

	cout << maxSum << " " << orgVector[leftIndex] << " " << orgVector[rightIndex];
}