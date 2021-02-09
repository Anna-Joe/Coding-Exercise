#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

int n;
vector<int> pre,in,post,value;
void postOrder(int root,int start,int end)
{
	if (start > end)
		return;
	int i = start;
	while (i < end && in[i] != pre[root])
		i++;
	postOrder(root+1,start,i-1);
	postOrder(root+i-start+1,i+1,end);
	post.push_back(pre[root]);
}
int main()
{
	cin >> n;

	stack<int> tmp;
	int key = 0;
	for(int i = 0; i < 2*n; ++i)
	{
		string s;
		cin >> s;
		if (s.length() == 4)
		{
			int k;
			cin >> k;
			tmp.push(k);
			pre.push_back(k);
		}
		else
		{
			in.push_back(tmp.top());
			tmp.pop();
		}

	}

	postOrder(0, 0, n - 1);

	cout << post[0];
	for (int i = 1; i < n; i++)
		cout << " " << post[i];
	return 0;
}

