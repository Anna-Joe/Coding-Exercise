#include <iostream>
#include <vector>

using namespace std;
int getPost(int root, int tail, int lastRoot, vector<int>& pre, vector<int>& post)
{
	if (root > tail)
		return 0;
	int i = root;
	//�ҵ��Ӹ��ڵ㿪ʼ �ȸ�С�����һ���ڵ�
	while (i < tail && pre[i + 1] < pre[root])
	{
		if (pre[i + 1] < lastRoot)//Ӧ��������ɸѡ��������
			return 0;
		++i;
	}
	if (i < tail && pre[i + 1] == pre[root])
		++i;
	if (i < tail && pre[i + 1] < pre[root])
		return 0;

	getPost(root + 1, i, -99999, pre, post);
	getPost(i + 1, tail, pre[root], pre, post);
	post.emplace_back(pre[root]);
	return 1;
}
int main()
{
	int n = 0;
	cin >> n;
	vector<int> pre, post;
	pre.resize(n);
	for (int i = 0; i < n; ++i)
		cin >> pre[i];

	if (n == 1)
		cout << ("YES\n") << pre[0];
	else if (n > 1)
	{
		//�������µ�BST
		if (pre[0] < pre[1])
		{
			for (int i = 0; i < n; ++i)
				pre[i] = -pre[i];
		}
		getPost(0, n - 1, -99999, pre, post);
		if (post.size() == n)
		{
			cout << "YES\n" << abs(post[0]);
			for (int i = 1; i < n; ++i)
				cout << " " << abs(post[i]);
		}
		else
			cout << "NO\n";
	}
	return 0;
}
