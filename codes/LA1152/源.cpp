#pragma warning(disable:4996)
#include <iostream>
#include <string>
using namespace std;

bool isPrim(int n)
{
	for (int i = 2; i < sqrt(n); i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}
int main()
{
	int n, k;
	cin >> n >> k;
	string number;
	cin >> number;

	for (int i = 0; i < n - k + 1; i++)
	{
		string sub = number.substr(i, k);
		int subNum = stoi(sub);
		if (isPrim(subNum))
		{
			cout << sub << endl;
			return 0;
		}
	}
	cout << 404;
	return 0;
}