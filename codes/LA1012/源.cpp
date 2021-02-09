#pragma warning(disable:4996)

#include <cstdio>
#include <algorithm>

using namespace std;
struct stu
{
	int id, best;
	int score[4], rank[4];
};
stu stuReport[2005];
int exist[1000000];
int flag = -1;

bool cmp(stu a, stu b)
{
	return a.score[flag] > b.score[flag];
}


int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d %d", &stuReport[i].id, &stuReport[i].score[1], &stuReport[i].score[2], &stuReport[i].score[3]);
		stuReport[i].score[0] = (stuReport[i].score[1] + stuReport[i].score[2] + stuReport[i].score[3]) / 3.0 + 0.5;
	}

	for (flag = 0; flag <= 3; flag++)
	{
		sort(stuReport, stuReport + n, cmp);
		stuReport[0].rank[flag] = 1;
		for (int i = 1; i < n; i++)
		{
			stuReport[i].rank[flag] = i + 1;
			if (stuReport[i].score[flag] == stuReport[i - 1].score[flag])//如果是分数相同 排名也相同
			{
				stuReport[i].rank[flag] = stuReport[i - 1].rank[flag];
			}
		}
	}

	//获取最佳排名
	for (int i = 0; i < n; i++)
	{
		exist[stuReport[i].id] = i + 1;
		int best = stuReport[i].rank[0];
		for (flag = 1; flag <= 3; flag++)
		{
			if (stuReport[i].rank[flag] < best)
			{
				stuReport[i].best = flag;
				best = stuReport[i].rank[flag];
			}
		}
	}

	char t[5] = { 'A','C','M','E' };
	for (int i = 0; i < m; i++)
	{
		int id = 0;
		scanf("%d", &id);
		int index = exist[id];
		if (index)
		{
			int best = stuReport[index-1].best;
			int rank = stuReport[index-1].rank[best];
			printf("%d %c\n", rank, t[best]);
		}
		else
			printf("N/A\n");
	}

	return 0;
}