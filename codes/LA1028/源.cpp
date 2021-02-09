#pragma warning(disable:4996)

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;
struct record
{
	int no;
	string name;
	int grade;
};

bool cmp_no(record a, record b)
{
	return a.no < b.no;
}

bool cmp_name(record a, record b)
{
	if(a.name != b.name)
		return a.name < b.name;
	else
		return a.no < b.no;
}

bool cmp_grade(record a, record b)
{
	if(a.grade != b.grade)
		return a.grade < b.grade;
	else
		return a.no < b.no;
}

int main()
{
	record recs[100005];
	int n, c;
	cin >> n >> c;
	for (int i = 0; i < n; i++)
	{
		cin >> recs[i].no >> recs[i].name >> recs[i].grade;
	}

	switch (c) 
	{
	case 1:
		sort(recs, recs + n, cmp_no);
		break;
	case 2:
		sort(recs, recs + n, cmp_name);
		break;
	case 3:
		sort(recs, recs + n, cmp_grade);
		break;
	}

	for (int i = 0; i < n; i++)
	{
		printf("%06d %s %d\n", recs[i].no, recs[i].name.c_str(), recs[i].grade);
	}
	return 0;
}