#pragma warning(disable:4996)
#include <iostream>
#include <map>
#include <cstring>
#include <vector>

using namespace std;

struct word {
	char key;
	int next;
	bool flag = false;//ÊÇ·ñ±éÀú¹ı
};

word words[100001];
int main() {

	int start1, start2, k;
	scanf("%d %d %d", &start1, &start2, &k);
	for (int i = 0; i < k; i++)
	{
		int head, tail;
		char letter;
		scanf("%d %c %d", &head, &letter, &tail);
		words[head].key = letter;
		words[head].next = tail;
	}

	for (int i = start1; i != -1; i = words[i].next)
		words[i].flag = true;
	for (int i = start2; i != -1; i = words[i].next)
	{
		if (words[i].flag)
		{
			printf("%05d", i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}