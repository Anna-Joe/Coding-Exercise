#pragma warning(disable:4996)

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
struct stu
{
	string patNo;
	string level;
	int site;
	int date;
	int no;
	int score;
};
struct siteCnt
{
	int no;
	int cnt = 0;
};
stu records[10007];
bool cmp1(stu a, stu b)
{
	if (a.score != b.score)
		return a.score > b.score;
	else
		return a.patNo < b.patNo;
}

bool cmp2(siteCnt a, siteCnt b)
{
	if (a.cnt != b.cnt)
		return a.cnt > b.cnt;
	else
		return a.no < b.no;
}

int main()
{
	map<string, vector<stu> >levelMap;
	map<int, vector<stu> > siteMap;
	map<int, vector<stu> > dateMap;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		string patNum;
		int score;
		cin >> patNum >> score;
		//scanf("%s %d", &patNum, score);
		records[i].patNo = patNum;
		records[i].level = patNum.substr(0, 1);
		records[i].site = stoi(patNum.substr(1, 3));
		records[i].date = stoi(patNum.substr(4, 6));
		records[i].no = stoi(patNum.substr(10, 3));
		records[i].score = score;

		levelMap[records[i].level].push_back(records[i]);
		siteMap[records[i].site].push_back(records[i]);
		dateMap[records[i].date].push_back(records[i]);

	}

	for (int i = 1; i <= m; i++)
	{
		int type;
		cin >> type;
		switch (type)
		{
		case 1:
		{
			string level;
			cin >> level;

			printf("Case %d: %d %s\n",i, type, level.c_str());

			vector<stu> result = levelMap[level];
			if (result.empty())
			{
				cout << "NA\n";
			}
			else
			{
				sort(result.begin(), result.end(), cmp1);
				for (auto it = result.begin(); it != result.end();it++)
				{
					stu tmp = *it;
					printf("%s %d\n", tmp.patNo.c_str(), tmp.score);
				}
			}
			break;
		}
		case 2:
		{
			int site;
			cin >> site;

			printf("Case %d: %d %d\n", i, type, site);

			vector<stu> result = siteMap[site];
			if (result.empty())
			{
				cout << "NA\n";
			}
			else
			{
				int sum = 0;
				for (auto it = result.begin(); it != result.end(); it++)
				{
					stu tmp = *it;
					sum += tmp.score;
				}
				printf("%d %d\n", result.size(), sum);
			}

			break;
		}
		case 3:
		{
			int date;
			cin >> date;

			printf("Case %d: %d %d\n", i, type, date);

			vector<stu> result = dateMap[date];
			bool isOut[1000] = { false };
			if (result.empty())
			{
				cout << "NA\n";
			}
			else
			{
				map<int,int> sites;
				vector<siteCnt> siteV;
				for (auto it = result.begin(); it != result.end(); it++)
				{
					stu tmp = *it;
					sites[tmp.site]++;
				}
				for(auto it = sites.begin();it != sites.end();it++)
				{
					siteCnt t;
					t.no = it->first;
					t.cnt = it->second;
					siteV.push_back(t);
				}
				sort(siteV.begin(), siteV.end(), cmp2);
				for (auto it = siteV.begin(); it != siteV.end(); it++)
				{
					siteCnt tmp = *it;
					printf("%d %d\n", tmp.no, tmp.cnt);
				}


			}

			break;
		}
		default: break;
		}
	}
	return 0;
}