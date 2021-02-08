#pragma warning(disable:4996)

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct stu
{
	string name;
	string id;
	int grade;
};

bool cmp(stu a, stu b)
{
	if (a.grade != b.grade)
		return a.grade > b.grade;
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	vector<stu> stuRecs(n);
	vector<stu> sortedRecs;
	for(int i = 0; i < n; i++)
	{ 
		cin >> stuRecs[i].name >> stuRecs[i].id >> stuRecs[i].grade;
	}

	int low = 0, high = 0;
	scanf("%d %d", &low,&high);


	for (int i = 0; i < n; i++)
	{
		stu tmp = stuRecs[i];
		if (tmp.grade <= high && tmp.grade >= low)
		{
			sortedRecs.push_back(tmp);
		}
	}

	if (sortedRecs.empty())
	{
		printf("NONE");
	}
	else
	{
		sort(sortedRecs.begin(), sortedRecs.end(), cmp);
		for (int i = 0; i < sortedRecs.size(); i++)
		{
			printf("%s %s\n", sortedRecs[i].name.c_str(), sortedRecs[i].id.c_str());
		}
	}

	return 0;
}