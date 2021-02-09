#pragma warning(disable:4996)

#include <iostream>

using namespace std;

int main()
{
	int k1 = 0, s1 = 0, g1 = 0;
	int k2 = 0, s2 = 0, g2 = 0;
	scanf("%d.%d.%d %d.%d.%d", &g1, &s1, &k1, &g2, &s2, &k2);

	int dg = 0, ds = 0;//½øÎ»
	int kr = 0, sr = 0, gr = 0;

	kr = k1 + k2;
	if (kr >= 29)
	{
		kr -= 29;
		ds++;
	}
	sr = ds + s1 + s2;
	if (sr >= 17)
	{
		sr -= 17;
		dg++;
	}
	gr = g1 + g2 + dg;

	printf("%d.%d.%d", gr, sr, kr);


	return 0;
}