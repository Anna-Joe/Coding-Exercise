#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main()
{
	vector<long long> numerator, denominator;
	int n = 0;
	scanf_s("%d",&n);

	long long bigDeno = 1;
	for (int i = 0; i < n; i++)
	{

		long long n1, n2;
		scanf_s("%lld/%lld", &n1, &n2);

		numerator.push_back(n1);
		denominator.push_back(n2);
		bigDeno = bigDeno * n2;

	}


	long long sumNum = 0;
	for (int i = 0; i < numerator.size(); i++)
	{
		long long n = numerator[i];
		long long d = denominator[i];
		n = n * bigDeno / d;
		sumNum += n;
	}

	long long integer = 0;//整数部分
	long long newNum = 0;//新分子
	long long newDen = bigDeno;//新分母
	integer = sumNum / bigDeno;
	newNum = sumNum % bigDeno;
	//化简新分子和新分母
	long long tmp = abs(newNum);
	for (long long i = abs(newNum); i >= 2; i--)
	{
		if (tmp / i == 0 || newDen / i == 0)
			break;
		if (tmp % i != 0 || newDen % i != 0)
			continue;
		tmp = tmp / i;
		newDen = newDen / i;
	}
	if (newNum < 0)
		newNum = -tmp;
	else
		newNum = tmp;

	if (integer != 0)
		cout << integer << " ";
	if (newNum != 0)
	{
		if (integer != 0)
			cout << " ";
		cout << newNum << "/" << newDen;
	}
	if (integer == 0 && newNum == 0)
		cout << 0;


	return 0;
}