#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
char p[10001];
int main()
{
	string s;
	cin >> s;
	scanf("%s",p);
	int ls = s.size();
	//p的长度
	int lp = strlen(p);
	//子串的长度 从p的长度到s的长度
	for (int lsub = lp; lsub < ls; lsub++)
	{
		for (int i = 0; i < ls-lsub+1; i++)
		{
			string sub = s.substr(i, lsub);
			//if (sub == "pabt")
			//	sub = "pabt";
			bool get = false;
			vector<int> gets(lp,9999);
			for (int j = 0; j < lp; j++)
			{
				char letter = p[j];
				if (sub.find(letter) != string::npos)
				{
					int x = sub.find(letter);
					gets[j] = x;
					if (j ==0 ||j > 0 && x > gets[j - 1])
						get = true;
					else
					{
						get = false;
						break;
					}
				}
			}
			if (get && gets[lp-1] != 9999)
			{
				printf("%s", sub.c_str());
				return 0;
			}
		}
	}
	return 0;
}