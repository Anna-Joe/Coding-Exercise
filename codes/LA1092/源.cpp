#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	char s1[10000], s2[10000];
	cin.getline(s1, 10000);
	cin.getline(s2, 10000);

	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int flag[10000] = { 0 };
	for (int i = 0; i < len2; i++)
		flag[s2[i]]++;
	int matched = 0, unmatched = 0;
	for (int i = 0; i < len1; i++)
	{
		if (flag[s1[i]])
		{
			matched++;
			flag[s1[i]]--;
		}
		else
			unmatched++;
	}

	if (matched >= len2)
		printf("Yes %d", unmatched);
	else
		printf("No %d", len2 - matched);

	return 0;
}