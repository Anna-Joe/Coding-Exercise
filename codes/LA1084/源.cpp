#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main()
{
	char s1[10000], s2[10000];
	cin.getline(s1, 10000);
	cin.getline(s2, 10000);

	int len1 = strlen(s1);
	int len2 = strlen(s2);

	bool flag[10000] = { false };
	for (int i = 0; i < len2; i++)
	{
		flag[s2[i]] = true;
	}

	bool printed[10000] = { false };
	for (int i = 0; i < len1; i++)
	{
		if (flag[tolower(s1[i])] || flag[s1[i]])
			continue;
		if (!printed[toupper(s1[i])])
		{
			printf("%c", toupper(s1[i]));
			printed[toupper(s1[i])] = true;
		}
	}
	return 0;
}