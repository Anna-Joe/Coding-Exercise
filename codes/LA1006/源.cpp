#pragma warning(disable:4996)

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string earliest_time, earliest_id, latest_time, latest_id;
	earliest_time = "24:59:59";
	latest_time = "00:00:00";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string id, s_time, e_time;
		cin >> id >> s_time >> e_time;
		if (s_time > e_time)
			continue;
		if (s_time < earliest_time)
		{
			earliest_time = s_time;
			earliest_id = id;
		}
		if (e_time > latest_time)
		{
			latest_time = e_time;
			latest_id = id;
		}
	}

	cout << earliest_id << " " << latest_id;

	return 0;

}