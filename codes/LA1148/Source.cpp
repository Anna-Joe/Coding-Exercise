#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//两个数组分别控制 某人的身份 和 叙述的真假
//数组V控制 叙述的真假 （符号标识好坏，数字标识成员编号）
//数组a控制 成员的身份 （1标识好人，-1标识坏人）
int main()
{
	int n;//成员人数
	cin >> n;
	vector<int> v(n+1);

	for (int i = 1; i < n+1; i++)
	{
		cin >> v[i];
	}
	for (int i = 1; i < n+1; i++)
	{
		for (int j = i + 1; j < n+1; j++)
		{
			vector<int> a(n + 1, 1);//初始化n个1 默认都是好人
			vector<int> liar;//谎话成员

			a[i] = a[j] = -1;//ij标识狼人
			for (int k = 1; k < n+1; k++)
				if (v[k] * a[abs(v[k])] < 0)liar.push_back(k);
			if (liar.size() == 2 && (a[liar[0]] + a[liar[1]] == 0))//当说谎成员为两人，并且一好一坏时 输出
			{
				cout << i << " " << j;
				return 0;
			}
		}
	}
	cout << "No Solution";
	return 0;
}