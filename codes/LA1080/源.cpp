#pragma warning(disable:4996)

#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
struct stu
{
	int id;
	int ge = 0;
	int gi = 0;
	vector<int> pre;
};

bool cmp(stu a, stu b)
{
	if ((a.ge + a.gi)  != (b.ge + b.gi) )
		return (a.ge + a.gi)  > (b.ge + b.gi) ;
	else
		return a.ge > b.ge;
}

int main()
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	vector<int> sch_lim(m,0);
	for (int i = 0; i < m; i++)
	{
		scanf("%d", &sch_lim[i]);
	}
	vector<stu> stus(n);
	for (int i = 0; i < n; i++)
	{
		stus[i].id = i;
		scanf("%d %d ", &stus[i].ge, &stus[i].gi);
		stus[i].pre.resize(k);
		for (int j = 0; j < k; j++)
		{
			scanf("%d", &stus[i].pre[j]);
		}
	}

	map<int,vector<int> > sch_ind, sch_stu;//每个学校已录取的人数 index

	sort(stus.begin(), stus.end(), cmp);
	for (int i = 0; i < n; i++)
	{
		stu s = stus[i];
		vector<int> p = s.pre;
		for (int j = 0; j < k; j++)
		{
			int sch_id = p[j];
			if (sch_id == 5)
				sch_id;
			vector<int>& adm = sch_ind[sch_id];
			vector<int>& st = sch_stu[sch_id];
			if (adm.size() < sch_lim[sch_id])
			{
				adm.push_back(i);
				st.push_back(s.id);
				break;
			}
			else
			{ 
				int stu_id = adm[adm.size() - 1];
				stu ls = stus[stu_id];
				if ((ls.ge + ls.gi)  == (s.ge + s.gi) 
					&& ls.ge == s.ge)
				{
					adm.push_back(i);
					st.push_back(s.id);
					break;
				}
			}
		}
	}

	for(int i = 0 ; i < m;i++)
	{ 
		vector<int> stu_id_list = sch_stu[i];
		sort(stu_id_list.begin(), stu_id_list.end());
		for (int i = 0; i < stu_id_list.size(); i++)
		{
			if(i != 0)
				printf(" ");
			printf("%d", stu_id_list[i]);
		}
		printf("\n");
	}
	return 0;
}