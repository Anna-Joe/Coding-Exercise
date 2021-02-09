#pragma warning(disable:4996)

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	map<int, vector<string> > courseStuMap;
	int n = 0, k = 0;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		string name;
		cin >> name;
		int total = 0;
		cin >> total;
		for (int j = 0; j < total; j++)
		{
			int course = 0;
			cin >> course;
			courseStuMap[course].push_back(name);
		}
	}
	for (int cNo = 1; cNo <=k; cNo++)
	{
		vector<string> stuList = courseStuMap[cNo];
		sort(stuList.begin(), stuList.end());
		int cnt = stuList.size();
		printf("%d %d\n", cNo, cnt);
		for (int i = 0; i < cnt; i++)
			printf("%s\n", stuList[i].c_str());
	}
	return 0;
}