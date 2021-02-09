#pragma warning(disable:4996)

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

struct record
{
	char name[10];
	int age;
	int worths;
};
bool cmp(record a, record b)
{
	if (a.worths != b.worths)
		return a.worths > b.worths;
	else if (a.age != b.age)
		return a.age < b.age;
	else
		return (strcmp(a.name, b.name) < 0);
}

int main()
{
	int n = 0, k = 0;
	scanf("%d %d", &n, &k);
	vector<record> rt(n), r;
	for (int i = 0; i < n; i++)
	{
		scanf("%s %d %d", rt[i].name, &rt[i].age, &rt[i].worths);
	}
	sort(rt.begin(), rt.end(), cmp);
	//vector<int> book(205, 0);
	//for (int i = 0; i < n; i++) {
	//	if (book[rt[i].age] < 100) {
	//		r.push_back(rt[i]);
	//		book[rt[i].age]++;
	//	}
	//}
	for (int i = 0; i < k; i++)
	{
		int limit = 0;
		int min = 0, max = 0;
		cin >> limit >> min >> max;
		vector<record> fit;
		printf("Case #%d:\n", i+1);
		int cnt = 0;
		for (int j = 0; j < rt.size(); j++)
		{
			if (rt[j].age >= min && rt[j].age <= max)
			{
				printf("%s %d %d\n",rt[j].name, rt[j].age, rt[j].worths);
				cnt++;
			}
				//fit.emplace_back(rt[j]);
			if (cnt == limit)
				break;
		}
		if (cnt == 0)
		{
			printf("None\n");
		}
		//if (fit.empty())
		//{
		//	cout << "None" << endl;
		//}
		//else
		//{
		//	for (int j = 0; j < limit && j < fit.size(); j++)
		//	{
		//		printf("%s %d %d\n", fit[j].name, fit[j].age, fit[j].worths);
		//	}

		//}
	}

	return 0;
}