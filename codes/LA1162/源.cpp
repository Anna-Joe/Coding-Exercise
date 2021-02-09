#pragma warning(disable:4996)
#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	long t1 = GetTickCount64();
	int k = 0;
	cin >> k;
	int i = 2;
	int max = 0;

	int fNm2 = 1;
	int fNm1 = 2;
	int fN = 0;
	while (k > fN)
	{
		fN = fNm2 + fNm1;
		fNm2 = fNm1;
		fNm1 = fN;
	}
	int d1 = fNm1 - k;
	int d2 = k - fNm2;
	if (d1 < d2)
		cout << k + d1;
	else
		cout << k - d2;

	long t2 = GetTickCount64();

	cout << "程序执行时间：" << (t2 - t1)/1000 << endl;
	return 0;
}