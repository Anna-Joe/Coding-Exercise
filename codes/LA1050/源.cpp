#include <iostream>
#include <cstring>

using namespace std;

char s1[100000], s2[100000];
int main()
{
	cin.getline(s1, 100000);
	cin.getline(s2, 100000);
	int len1 = strlen(s1);
	int len2 = strlen(s2);

	bool flag[100000] = { false };
	for (int i = 0; i < len2; i++)
	{
		flag[s2[i]] = true;
	}

	for (int i = 0; i < len1; i++)
	{
		if (!flag[s1[i]])
			printf("%c", s1[i]);
	}

	return 0;
}
