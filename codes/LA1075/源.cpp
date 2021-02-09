#pragma warning(disable:4996)

#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

struct node
{
	int id = 0;
	vector<int> grades;
	int total = 0;
	int rank = 0;
	int full = 0;
};

bool cmp(node a, node b)
{
	if (a.total != b.total)
		return a.total > b.total;
	else if (a.full != b.full)
		return a.full > b.full;
	else
		return a.id < b.id;
}

int main()
{
	int n, k, m;
	scanf("%d %d %d", &n, &k, &m);

	vector<int> queGoal(k);
	for (int i = 0; i < k; i++)
	{
		int g = 0;
		scanf("%d ", &g);
		queGoal[i] = g;
	}

	map<int, node> subMap;
	for (int i = 0; i < m; i++)
	{
		int id = 0, qi = 0, qg = 0;
		scanf("%d %d %d", &id, &qi, &qg);

		node& tmp = subMap[id];
		if (tmp.id == 0)
		{
			tmp.id = id;
			tmp.grades.resize(k, -2);
			tmp.grades[qi - 1] = qg;
		}
		else if (qg > tmp.grades[qi - 1])
		{
			tmp.grades[qi - 1] = qg;
		}
	}

	map<int, node>::iterator it;
	vector<node> rankVec;
	for (it = subMap.begin(); it != subMap.end(); it++)
	{
		node tmp = it->second;
		vector<int> grades = tmp.grades;
		int flag = 0;
		for (int i = 0; i < k; i++)
		{
			if (grades[i] >= 0)
			{
				flag = 1;
				tmp.total += grades[i];
				if (grades[i] == queGoal[i])
					tmp.full++;
			}
		}
		if (flag)
			rankVec.push_back(tmp);
	}

	sort(rankVec.begin(), rankVec.end(), cmp);
	int lastRank = 1, lastTotal = 0;
	for (int i = 0; i < rankVec.size(); i++)
	{
		node tmp = rankVec[i];
		int rank = i + 1;
		if (lastRank != 1)
		{
			if (tmp.total == lastTotal)
				rank = lastRank;
		}
		printf("%d %05d %d", rank, tmp.id, tmp.total);
		lastTotal = tmp.total;
		lastRank = rank;
		vector<int> grades = tmp.grades;
		for (int i = 0; i < k; i++)
		{
			if(grades[i] == -1)
				printf(" 0");
			else if (grades[i] == -2)
				printf(" -");
			else
				printf(" %d", grades[i]);
		}
		printf("\n");
	}
	return 0;
}