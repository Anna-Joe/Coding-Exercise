#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node 
{
	int data;
	int lchild = -1;
	int rchild = -1;
	bool isChild = false;
	int levelIndex;
};

vector<node> tree;
vector<int> in, le;

int root = 0,ii = 0;

int n;

bool cmp(node& x, node& y)
{
	return x.levelIndex < y.levelIndex;
}

void inOrder(int i,int index)
{
	if (tree[i].lchild != -1)
		inOrder(tree[i].lchild,2 * index + 1);
	
	in[ii++] =  tree[i].data;
	tree[i].levelIndex = index;

	if (tree[i].rchild != -1)
		inOrder(tree[i].rchild, 2 * index + 2);
}
int main()
{
	cin >> n;
	tree.resize(n);
	in.resize(n);

	for (int i = 0; i < n; i++)
	{
		char l, r;
		cin >> l >> r;
		if (l != '-')
		{
			tree[i].rchild = l - '0';
			tree[l - '0'].isChild = true;
		}
		if (r != '-')
		{
			tree[i].lchild = r - '0';
			tree[r - '0'].isChild = true;
		}
		tree[i].data = i;
	}

	//找出根节点
	for (int i = 0; i < n; i++)
	{
		if (tree[i].isChild == false)
		{
			root = i;
			break;
		}
	}

	inOrder(root,0);

	sort(tree.begin(), tree.end(), cmp);

	cout << tree[0].data;
	for (int i = 1; i < n; ++i)
		cout << " " << tree[i].data;
	cout << endl;
	cout << in[0];
	for (int i = 1; i < n; ++i)
		cout << " " << in[i];

	return 0;
}