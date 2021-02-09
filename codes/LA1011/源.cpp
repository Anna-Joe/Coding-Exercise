#include <iostream>
#include <array>
#include <string>
using namespace std;

int main()
{
	array<array<double, 3>, 3> gameRate;
	double maxRates = 1.0;
	string rsl = "WTL";
	for (int i = 0; i < 3; i++)
	{
		int maxIndex = 0;
		for (int j = 0; j < 3; j++)
		{
			cin >> gameRate[i][j];
			if (gameRate[i][j] > gameRate[i][maxIndex])
			{
				maxIndex = j;
			}
		}
		if (i != 0)
			cout << " ";
		cout << rsl[maxIndex];
		maxRates = maxRates * gameRate[i][maxIndex];
	}
	printf(" %.2f", (maxRates * 0.65 - 1) * 2);

	return 0;
}