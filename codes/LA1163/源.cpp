#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>
using namespace std;

struct file
{
	string parent = "-1";
	string name = "-1";
};
int main()
{
	map<string, file> fileMap;//文件的名称映射
	int n = 0;
	scanf("%d\n",&n);

	string s;
	getline(cin, s);
	file first;
	first.name = s;
	fileMap[first.name] = first;
	string lastName = first.name;
	int lastD = 0;
	for (int i = 1; i < n; i++)
	{
		string s;
		getline(cin,s);

		file tmp;
		int thisD = 0;
		if (s.find(' ') != string::npos)
		{
			int index = s.find_last_of(' ') + 1;
			tmp.name = s.substr(index);
			thisD = s.find_last_of(' ') - s.find_first_of(' ');
			if (thisD > lastD)
			{
				tmp.parent = lastName;
				file pf = fileMap[lastName];
			}
			else
			{
				string tmpLast = lastName;
				for (int j = 0; j < lastD - thisD; j++)
				{
					string pn = fileMap[tmpLast].parent;
					file pf = fileMap[pn];
					tmpLast = pf.name;
				}
				tmp.parent = fileMap[tmpLast].parent;
			}
		}
		else
			tmp.name = s;
		fileMap[tmp.name] = tmp;
		lastName = tmp.name;
		lastD = thisD;
	}

	int k = 0;
	cin >> k;
	for (int i = 0; i < k; i++)
	{
		string fn;
		cin >> fn;
		file ff = fileMap[fn];

		if (ff.name == "-1")
			printf("Error: %s is not found.\n", fn.c_str());
		else
		{
			string path = fn;
			file tmp;
			tmp.parent = ff.parent;
			tmp.name = ff.name;
			while (tmp.parent != "-1")
			{
				string newpath = tmp.parent + "->" + path;
				path = newpath;
				ff = fileMap[tmp.parent];
				tmp.parent = ff.parent;
				tmp.name = ff.name;
			}
			printf("%s->%s\n",first.name.c_str(), path.c_str());
		}
	}
	return 0;
}