# 二叉搜索树

## 1043 Is It a Binary Search Tree (25)

A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
- Both the left and right subtrees must also be binary search trees.

If we swap the left and right subtrees of every node, then the resulting tree is called the **Mirror Image** of a BST.

Now given a sequence of integer keys, you are supposed to tell if it is the preorder traversal sequence of a BST or the mirror image of a BST.

### Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤1000). Then *N* integer keys are given in the next line. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, first print in a line `YES` if the sequence is the preorder traversal sequence of a BST or the mirror image of a BST, or `NO` if not. Then if the answer is `YES`, print in the next line the postorder traversal sequence of that tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.



### Explaining

先序遍历为二叉搜索树*或镜像二叉搜索树*的序列，输出YES以及此树的后序遍历序列，如果不是输出NO

### Thinking

- 1 先序造树 2 判断是否为二叉搜索树 3 输出后序遍历序列
- 12可以放在同一个过程中进行，难点有二：
  - 1 如何判断二叉搜索树
  - 2 如何判断镜像情况
- 根据后序遍历的特点（需要先输出左子树），先在先序序列中搜索到左子树，并且在这个过程中可以筛选掉不利情况（不满足条件的树）

### Code

```c++
#include <iostream>
#include <vector>

using namespace std;
int getPost(int root, int tail, int lastRoot, vector<int>& pre, vector<int>& post)
{
	if (root > tail)
		return 0;
	int i = root;
	//找到从根节点开始 比根小的最后一个节点
	while (i < tail && pre[i + 1] < pre[root])
	{
		if (pre[i + 1] < lastRoot)//应该是用来筛选左子树的
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
		//处理镜像下的BST
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

```



### Summary

- 综合题目描述和输入输出来判断题意
- 虽然是考树的内容，但是数据结构并不局限于树，可以从题目给出的序列入手，没必要死守树的定义
- 镜像树加负号处理 太强了！！



## 1064 Complete Binary Search Tree (30)

A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
- Both the left and right subtrees must also be binary search trees.

A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the bottom level, which is filled from left to right.

Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is required that the tree must also be a CBT. You are supposed to output the level order traversal sequence of this BST.

### Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤1000). Then *N* distinct non-negative integer keys are given in the next line. All the numbers in a line are separated by a space and are no greater than 2000.

### Output Specification:

For each test case, print in one line the level order traversal sequence of the corresponding complete binary search tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

### Sample Input:

```in
10
1 2 3 4 5 6 7 8 9 0
```

### Sample Output:

```out
6 3 8 1 5 7 9 0 2 4
```

### Explaining

已知一序列，求该序列构成的完全二叉搜索树的层次遍历

### Thinking

二叉搜索树的中序遍历是一个有序序列，此题可以转化为 中序遍历转层次遍历

关键是 

- 层次遍历根节点与孩子节点的关系 ，已知根的下标为i的情况下，左孩子为2i+1，右孩子为2i+2（完全二叉树特有的）

- 中序遍历算法

### Code

```c++
#include <iostream>
#include <algorithm>
using namespace std;

int in[1010], level[1010], n, t = 0;

void inOrder(int root)
{
	if (root >= n)
		return;
	inOrder(2 * root + 1 );
	level[root] = in[t++];
	inOrder(2 * root + 2);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &in[i]);

	sort(in, in + n);
	inOrder(1);

	printf("%d", level[0]);
	for(int i = 1; i < n; i++)
		printf(" %d", level[i]);

}
```

### Summary

没搞懂到底是怎么对一个层次序列直接套中序遍历算法就能成的



## 1099 **Build A Binary Search Tree** **(30)**

### Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤100) which is the total number of nodes in the tree. The next *N* lines each contains the left and the right children of a node in the format `left_index right_index`, provided that the nodes are numbered from 0 to *N*−1, and 0 is always the root. If one child is missing, then −1 will represent the NULL child pointer. Finally *N* distinct integer keys are given in the last line.

### Output Specification:

For each test case, print in one line the level order traversal sequence of that tree. All the numbers must be separated by a space, with no extra space at the end of the line.

### Sample Input:

```in
9
1 6
2 3
-1 -1
-1 4
5 -1
-1 -1
7 -1
-1 8
-1 -1
73 45 11 58 82 25 67 38 42
```

### Sample Output:

```out
58 25 82 11 38 67 45 73 42
```

### Code

```c++
#include <iostream>
#include <algorithm>

using namespace std;

int n, cnt, b[100];
struct node
{
	int data, l, r, index, level;
}a[110];

bool cmp(node x, node y)
{
	if (x.level != y.level)
		return x.level < y.level;
	return x.index < y.index;
}
void dfs(int root, int index, int level)
{
	if (a[root].l == -1 && a[root].r == -1)
	{
		a[root] = { b[cnt++],a[root].l,a[root].r,index,level };
	}
	else
	{
		if(a[root].l != -1) dfs(a[root].l, index*2 + 1, level + 1);
		a[root] = { b[cnt++],a[root].l,a[root].r,index,level };
		if (a[root].r != -1) dfs(a[root].r, index * 2 + 2, level + 1);
	}
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i].l >> a[i].r;
	for (int i = 0; i < n; i++)
		cin >> b[i];
	sort(b, b + n);
	dfs(0, 0, 0);
	sort(a, a + n, cmp);
	cout << a[0].data;
	for (int i = 1; i < n; i++)
		cout << " " << a[i].data;

	return 0;
}
```

### Summary

做完树的遍历再做一次二叉树的几个题



# 树的遍历

## 1004 **Counting Leaves** (30)

A family hierarchy is usually presented by a pedigree tree. Your job is to count those family members who have no child.

### Input Specification:

Each input file contains one test case. Each case starts with a line containing 0<*N*<100, the number of nodes in a tree, and *M* (<*N*), the number of non-leaf nodes. Then *M* lines follow, each in the format:

```
ID K ID[1] ID[2] ... ID[K]
```

where `ID` is a two-digit number representing a given non-leaf node, `K` is the number of its children, followed by a sequence of two-digit `ID`'s of its children. For the sake of simplicity, let us fix the root ID to be `01`.

The input ends with *N* being 0. That case must NOT be processed.

### Output Specification:

For each test case, you are supposed to count those family members who have no child **for every seniority level** starting from the root. The numbers must be printed in a line, separated by a space, and there must be no extra space at the end of each line.

The sample case represents a tree with only 2 nodes, where `01` is the root and `02` is its only child. Hence on the root `01` level, there is `0` leaf node; and on the next level, there is `1` leaf node. Then we should output `0 1` in a line.

### Sample Input:

```in
2 1
01 1 02
```

### Sample Output:

```out
0 1
```



### Explaining

输入一棵树的节点总数n，非叶子节点数m

输入节点编号，这个节点的孩子节点总数，孩子节点列表

输出这棵树每层的叶子节点数

### Thinking

- 使用深度优先遍历节点，记录每次遍历的终点即该层的叶子节点数
- 使用向量数组存储节点的孩子节点列表

### Code

```c++
#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> v[101];
int level[101],maxDepth = -1;
void dfs(int index, int depth)
{
	if (v[index].size() == 0)//没有孩子节点的节点认为是叶子节点
	{
		level[depth]++;
		maxDepth = max(maxDepth, depth);
		return;
	}
	else//遍历这个节点所有的孩子
	{
		for (int i = 0; i < v[index].size(); i++)
		{
			dfs(v[index][i], depth+1);
		}
	}
}

int main()
{
	int m, n;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int k,node;
		scanf("%d %d", &node, &k);
		for (int j = 0; j < k; j++)
		{
			int connect;
			scanf("%d", &connect);
			v[node].emplace_back(connect);
		}
	}

	dfs(1, 0);

	printf("%d", level[0]);
	for (int i = 1; i <= maxDepth; i++)
	{
		printf(" %d", level[i]);
	}
	return 0;
}
```

### Summary

- 深度优先遍历的大致思路就是 找到叶子节点（递归出口），遍历所有孩子节点
- 这题可能是深度优先的最简单应用吧



## **1020** **Tree Traversals** (25)

Suppose that all the keys in a binary tree are distinct positive integers. Given the postorder and inorder traversal sequences, you are supposed to output the level order traversal sequence of the corresponding binary tree.

### Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤30), the total number of nodes in the binary tree. The second line gives the postorder sequence and the third line gives the inorder sequence. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, print in one line the level order traversal sequence of the corresponding binary tree. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

### Sample Input:

```in
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7
```

### Sample Output:

```out
4 1 6 3 5 7 2
```

### Explaining

给出二叉树的先序遍历和中序遍历，要求输出层次遍历

### Thinking

后序遍历一定以根节点结尾（先序遍历一定以根节点开头）

在中序序列中找到根节点的位置，以此为分界点，左边是左子树序列，右边是右子树序列

根节点同时也是层次遍历的第一个节点

层次遍历根节点与孩子节点的关系 ，已知根的下标为i的情况下，左孩子为2i+1，右孩子为2i+2

- 根据后序序列和中序序列的关系，通过先序构造法造出二叉树
- 中间穿插记录层次遍历的下标以此来完成层次遍历序列

### Code

```c++
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

vector<int> post, in;
map<int, int> level;

/*!
 * \brief preOrder
 * \param root: index of post[]
 * \param start:start of child tree, index of in[]
 * \param end:end of the child tree, index of in[]
 * \param index:index of level[]
 */
void pre(int root, int start, int end, int index)
{
	if (start > end)
		return;
	int i = start;
    
    //find the root's position in in[]
	while (i < end && in[i] != post[root])
		i++;
	level[index] = post[root];
   
    //root of left tree,from pos,to pos,index of level
	pre(root - (end - i + 1), start, i - 1, 2 * index + 1);
   
    //root of right tree,from pos,to pos,index of level
	pre(root - 1, i + 1, end, 2 * index + 2);
	
    //attention:"2*index+1 or 2" because of the ralationship between root and children
}
int main()
{
	int n = 0;
	cin >> n;

	post.resize(n);
	in.resize(n);

	for (int i = 0; i < n; ++i)
		cin >> post[i];
	for (int i = 0; i < n; ++i)
		cin >> in[i];

	pre(n - 1, 0, n - 1, 0);
	auto it = level.begin();
	printf("%d", it->second);
	while (++it != level.end())
		printf(" %d", it->second);

	return 0;
}
```

### Summary

在构造二叉树的过程中记录层序序列的序号是一种很重要的算法思想，在树的相关题目里已经是第三次用到了，谨记根节点与孩子节点的关系。

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
using namespace std;

struct node
{
	int data;
	vector<int> child;
}a[101];

stack<int> tmpPath;




int main()
{
	int n, m, w;
	cin >> n >> m >> w;
	for (int i = 0; i < n; i++)
		cin >> a[i].data;
	for (int i = 0; i < m; i++)
	{
		int id, k;
		cin >> id >> k;
		for (int j = 0; j < k; j++)
		{
			int ch;
			cin >> ch;
			a[id].child.emplace_back(ch);
		}
	}



	return 0;

}