#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, k, p;
int maxFacSum = -1;
vector<int> ans,tmpAns;
vector<int> factor;

void initFactor()
{
	int index = 1;
	int tmp = 0;
	while (tmp <= n)
	{
		factor.emplace_back(tmp);
		tmp = pow(index, p);
		index++;
	}
}
void dfs(int index,int tmpK,int facSum,int tmpSum)
{
	if (tmpK == k)
	{
		if (tmpSum == n && facSum > maxFacSum)
		{
			maxFacSum = facSum;
			ans = tmpAns;
		}
		return;
	}
	while(index >= 1)
	{
		if (tmpSum + factor[index] <= n)
		{
			tmpAns[tmpK] = index;
			dfs(index, tmpK+1, facSum + index,tmpSum + factor[index]);
		}
		if (index == 1)return;
		index--;
	}

}
int main()
{
	cin >> n >> k >> p;
	tmpAns.resize(n);
	initFactor();
	dfs(factor.size() - 1, 0, 0, 0);

	if (maxFacSum == -1)
		cout << "Impossible";
	else
	{
		printf("%d = %d^%d", n, ans[0], p);
		for(int i = 1 ; i < k;i++)
			printf(" + %d^%d", ans[i], p);
	}
	return 0;
}