
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int n = 0, k = 0;
	cin >> n >> k;
	map<string, vector<int>> stuInfo;

	for (int i = 0; i < k; i++)
	{
		int courseNum = 0;
		int choosenCount = 0;
		cin >> courseNum >> choosenCount;

		for (int j = 0; j < choosenCount; j++)
		{
			string name;
			cin >> name;
			stuInfo[name].push_back(courseNum);
		}
	}

	for (int i = 0; i < n; i++)
	{
		string name;
		cin >> name;
		vector<int> courses = stuInfo[name];
		cout << name << " " << courses.size();
		sort(courses.begin(),courses.end());
		for (vector<int>::iterator iter = courses.begin(); iter != courses.end(); iter++)
		{
			cout << " " << *iter;
		}
		cout << endl;
	}
	return 0;
}