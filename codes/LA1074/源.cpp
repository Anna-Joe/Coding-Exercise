#pragma warning(disable:4996)
#include <iostream>
using namespace std;

int main()
{
	int first, k, n, sum = 0;
	cin >> first >> n >> k;
	int tmp, data[100005], next[100005], list[100005], result[100005];
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		cin >> data[tmp] >> next[tmp];
	}
	while (first != -1)
	{
		list[sum++] = first;
		first = next[first];
	}
	for (int i = 0; i < n; i++)
	{
		result[i] = list[i];
	}
	for (int i = 0; i < sum - sum % k; i++)
	{
		result[i] = list[i / k * k + k - 1 - i % k];
	}
	return 0;
}