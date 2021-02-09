#pragma warning(disable:4996)

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct gradeRec
{
	string no;
	int local;
	int score;
	int l_rank;
	int t_rank;
};
gradeRec gradeRecs[30005];

bool cmp(gradeRec a, gradeRec b)
{
	if (a.score != b.score)
		return a.score > b.score;
	else
		return a.no < b.no;
}

int main()
{
	int n = 0;//local num
	scanf("%d", &n);

	int index = 0;
	for (int i = 1; i <= n; i++)
	{
		int k = 0;
		scanf("%d", &k);
		gradeRec localRecs[305];
		for (int j = 0; j < k; j++)
		{
			cin >> localRecs[j].no >> localRecs[j].score;
			localRecs[j].local = i;
		}

		sort(localRecs,localRecs+k, cmp);
		localRecs[0].l_rank = 1;
		gradeRecs[index++] = localRecs[0];
		for (int j = 1; j < k; j++)
		{
			localRecs[j].l_rank = j + 1;

			if (localRecs[j].score == localRecs[j - 1].score)
				localRecs[j].l_rank = localRecs[j - 1].l_rank;

			gradeRecs[index++] = localRecs[j];
		}

	}

	sort(gradeRecs, gradeRecs+ index, cmp);
	gradeRecs[0].t_rank = 1;
	for (int i = 1; i < index; i++)
	{
		gradeRecs[i].t_rank = i + 1;

		if (gradeRecs[i].score == gradeRecs[i - 1].score)
			gradeRecs[i].t_rank = gradeRecs[i - 1].t_rank;
	}

	printf("%d\n", index);
	for (int i = 0; i < index; i++)
	{
		cout << gradeRecs[i].no << " " 
			 << gradeRecs[i].t_rank << " "
			 << gradeRecs[i].local << " "
			 << gradeRecs[i].l_rank << endl;
	}
	return 0;
}