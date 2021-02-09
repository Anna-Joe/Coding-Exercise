#pragma warning(disable:4996)

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <set>

using namespace std;
int main()
{
	int n = 0;
	scanf("%d\n", &n);

	map<string, set<int>> t_map, a_map, k_map, p_map,y_map;
	for (int i = 0; i < n; i++)
	{
		int id = 0;
		string title, author, keywords, publisher, year;
		scanf("%d\n", &id);
		getline(cin, title);
		getline(cin,author);
		while (cin >> keywords)
		{
			k_map[keywords].insert(id);
			char c = getchar();
			if (c == '\n')break;
		}
		getline(cin,publisher);
		getline(cin, year);

		t_map[title].insert(id);
		a_map[author].insert(id);
		p_map[publisher].insert(id);
		y_map[year].insert(id);
	}

	int m = 0;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int k = 0;
		scanf("%d: ", &k);
		string content;
		getline(cin, content);

		printf("%d: %s\n", k, content.c_str());
		set<int> idV;
		switch (k)
		{
		case 1:
			idV = t_map[content];
			break;
		case 2:
			idV = a_map[content];
			break;
		case 3:
			idV = k_map[content];
			break;
		case 4:
			idV = p_map[content];
			break;
		case 5:
			idV = y_map[content];
			break;
		default:
			break;
		}

		if (idV.empty())
			printf("Not Found\n");
		else
		{
			for (auto it = idV.begin(); it != idV.end(); it++)
				printf("%07d\n", *it);
		}


	}
	return 0;
}