#pragma warning(disable:4996)

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct record
{
	int id;
	int virtue;
	int talent;
	record()
	{
		id = 0;
		virtue = 0;
		talent = 0;
	}
};

bool cmp(record a, record b)
{
	if (a.virtue + a.talent != b.virtue + b.talent)
		return (a.virtue + a.talent) > (b.virtue + b.talent);
	else if (a.virtue != b.virtue)
		return a.virtue > b.virtue;
	else
		return a.id < b.id;
}

int main()
{
	int n, l, h;
	scanf("%d %d %d", &n, &l, &h);
	vector<record> r(n),r1,r2,r3,r4;

	for (int i = 0; i < n; i++)
	{
		record tmp;
		scanf("%d %d %d", &tmp.id, &tmp.virtue, &tmp.talent);
		if (tmp.virtue < l || tmp.talent < l)
			continue;
		else if (tmp.virtue >= h && tmp.talent >= h)
			r1.push_back(tmp);
		else if (tmp.virtue >= h && tmp.talent < h)
			r2.push_back(tmp);
		else if (tmp.virtue < h && tmp.talent < h && tmp.virtue >= tmp.talent)
			r3.push_back(tmp);
		else
			r4.push_back(tmp);

	}

	sort(r1.begin(), r1.end(), cmp);
	sort(r2.begin(), r2.end(), cmp);
	sort(r3.begin(), r3.end(), cmp);
	sort(r4.begin(), r4.end(), cmp);

	printf("%d\n", r1.size() + r2.size() + r3.size() + r4.size());
	for (auto &it : r1)
		printf("%08d %d %d\n", it.id, it.virtue, it.talent);
	for (auto &it : r2)
		printf("%08d %d %d\n", it.id, it.virtue, it.talent);
	for (auto &it : r3)
		printf("%08d %d %d\n", it.id, it.virtue, it.talent);
	for (auto &it : r4)
		printf("%08d %d %d\n", it.id, it.virtue, it.talent);
	return 0;
}