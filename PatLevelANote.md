[TOC]



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



## 1053 Path of Equal Weight (30)

Given a non-empty tree with root *R*, and with weight *W**i* assigned to each tree node *T**i*. The **weight of a path from R to L** is defined to be the sum of the weights of all the nodes along the path from *R* to any leaf node *L*.

Now given any weighted tree, you are supposed to find all the paths with their weights equal to a given number. For example, let's consider the tree showed in the following figure: for each node, the upper number is the node ID which is a two-digit number, and the lower number is the weight of that node. Suppose that the given number is 24, then there exists 4 different paths which have the same given weight: {10 5 2 7}, {10 4 10}, {10 3 3 6 2} and {10 3 3 6 2}, which correspond to the red edges in the figure.

![img](https://images.ptausercontent.com/212)

### Input Specification:

Each input file contains one test case. Each case starts with a line containing 0<*N*≤100, the number of nodes in a tree, *M* (<*N*), the number of non-leaf nodes, and 0<*S*<230, the given weight number. The next line contains *N* positive numbers where *W**i* (<1000) corresponds to the tree node *T**i*. Then *M* lines follow, each in the format:

```
ID K ID[1] ID[2] ... ID[K]
```

where `ID` is a two-digit number representing a given non-leaf node, `K` is the number of its children, followed by a sequence of two-digit `ID`'s of its children. For the sake of simplicity, let us fix the root ID to be `00`.

### Output Specification:

For each test case, print all the paths with weight S in **non-increasing** order. Each path occupies a line with printed weights from the root to the leaf in order. All the numbers must be separated by a space with no extra space at the end of the line.

Note: sequence {*A*1,*A*2,⋯,*A**n*} is said to be **greater than** sequence {*B*1,*B*2,⋯,*B**m*} if there exists 1≤*k*<*m**i**n*{*n*,*m*} such that *A**i*=*B**i* for *i*=1,⋯,*k*, and *A**k*+1>*B**k*+1.

### Sample Input:

```in
20 9 24
10 2 4 3 5 10 2 18 9 7 2 2 1 3 12 1 8 6 2 2
00 4 01 02 03 04
02 1 05
04 2 06 07
03 3 11 12 13
06 1 09
07 2 08 10
16 1 15
13 3 14 16 17
17 2 18 19
```

### Sample Output:

```out
10 5 2 7
10 4 10
10 3 3 6 2
10 3 3 6 2
```

### Explaining

给出一棵带权树的非叶子节点序列，输出满足目标权值的路径（分支）

### Thinking

- dfs建树，准备一个数组存储路径，满足目标权值的时候输出，大于或小于目标返回，并清空路径数组

- 一大于就返回清空，是不对的，应该回溯，并且在路径权值的基础上减去当前节点值

- 这里忽略了输出的时候，需要排序，按权值大的序列优先输出。借鉴liuchuo的代码，将权值的排序写在，读取节点孩子的时候，这样遍历的时候会优先遍历权值大的节点。

### Code

```c++
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

vector<int> tmpPath;
int sum = 0,l = 0,L = 0;
int n, m, w;

bool cmp(int x, int y)
{
	return a[x].data > a[y].data;
}
void dfs(int root)
{
	tmpPath.emplace_back(a[root].data);
	sum += tmpPath[l++];
	if (a[root].child.size() == 0)
	{
		if (sum == w)
		{
			cout << tmpPath[0];
			for (int i = 1; i < l; i++)
				cout << " " << tmpPath[i];
			cout << endl;
		}
		sum -= tmpPath[--l];
		tmpPath.pop_back();
		return;
	}
	else
	{
		for (int i = 0; i < a[root].child.size(); i++)
			dfs(a[root].child[i]);
		sum -= tmpPath[--l];
		tmpPath.pop_back();
	}
}

int main()
{
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
		sort(a[id].child.begin(), a[id].child.end(), cmp);
	}

	dfs(0);

	return 0;

}
```

### Summary

对于见过的算法，基本可以运用了。算法还是一个需要积累的过程。



## 1079 **Total Sales of Supply Chain** (25)

A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- everyone involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price *P* and sell or distribute them in a price that is *r*% higher than *P*. Only the retailers will face the customers. It is assumed that each member in the supply chain has exactly one supplier except the root supplier, and there is no supply cycle.

Now given a supply chain, you are supposed to tell the total sales from all the retailers.

### Input Specification:

Each input file contains one test case. For each case, the first line contains three positive numbers: *N* (≤105), the total number of the members in the supply chain (and hence their ID's are numbered from 0 to *N*−1, and the root supplier's ID is 0); *P*, the unit price given by the root supplier; and *r*, the percentage rate of price increment for each distributor or retailer. Then *N* lines follow, each describes a distributor or retailer in the following format:

*K**i* ID[1] ID[2] ... ID[*K**i*]

where in the *i*-th line, *K**i* is the total number of distributors or retailers who receive products from supplier *i*, and is then followed by the ID's of these distributors or retailers. *K**j* being 0 means that the *j*-th member is a retailer, then instead the total amount of the product will be given after *K**j*. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, print in one line the total sales we can expect from all the retailers, accurate up to 1 decimal place. It is guaranteed that the number will not exceed 1010.

### Sample Input:

```in
10 1.80 1.00
3 2 3 5
1 9
1 4
1 7
0 7
2 6 1
1 8
0 9
0 4
0 3
```

### Sample Output:

```out
42.4
```

### Explaining

在供应商，经销商和零售商构成的供应链中，供应商可以看成叶子节点，供应量看成叶子节点的权重，供应链的长度看成根到叶的路径长度。由此来求，零售商的最后零售额=供应量（叶子节点权重）×（1+利润率/100）^供应链长（叶子节点深度）×价格

### Thinking

bfs建树（就是在输入数据的同时记录孩子节点），dfs求权重和节点深度

### Code

```c++
#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct node
{
	double data;
	vector<int> child;
}a[1000001];

double ans=0.0,r,p;

void dfs(int root, int depth)
{
	if (a[root].child.size() == 0)//叶子节点
	{
		ans += a[root].data * pow(1 + r, depth);
		return;
	}
	else
	{
		for (int i = 0; i < a[root].child.size(); ++i)
			dfs(a[root].child[i], depth+1);
	}
}
int main()
{
	int n;
	scanf("%d %lf %lf", &n, &p, &r);
	//cin >> n >> p >> r;
	r = r / 100;
	for (int i = 0; i < n; i++)
	{
		int k;
		cin >> k;
		if (k != 0)
		{
			a[i].child.resize(k);
			for (int j = 0; j < k; j++)
				cin >> a[i].child[j];
			a[i].data = 0;
		}
		else
			cin >> a[i].data;
	}
	dfs(0, 0);
	printf("%.1f", ans * p);
	return 0;
}

```

### Summary

- 注意几个要点，p、r都是小数，所以data最好也用小数存储，r是百分号的情况，计算时应/100



## 1086 **Tree Traversals Again** (25)

An inorder binary tree traversal can be implemented in a non-recursive way with a stack. For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. Your task is to give the postorder traversal sequence of this tree.

![img](https://images.ptausercontent.com/30)
Figure 1

### Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to *N*). Then 2*N* lines follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.

### Output Specification:

For each test case, print the postorder traversal sequence of the corresponding tree in one line. A solution is guaranteed to exist. All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

### Sample Input:

```in
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
```

### Sample Output:

```out
3 4 2 6 5 1
```

### Explaining

通过push、pop的过程构造树，然后输出树的后序序列

### Thinking

push的过程可以得到先序序列，pop的过程可以得到中序序列，

转换为一道已知先序和中序求后序序列的题

### Code

```c++
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
```



### Summary

- cin>>string可以直接获取一个字符串，字符串和数字 的组合可以使用scanf也可以使用cin



## 1090 Highest Price in Supply Chain (25)

A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- everyone involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price *P* and sell or distribute them in a price that is *r*% higher than *P*. It is assumed that each member in the supply chain has exactly one supplier except the root supplier, and there is no supply cycle.

Now given a supply chain, you are supposed to tell the highest price we can expect from some retailers.

### Input Specification:

Each input file contains one test case. For each case, The first line contains three positive numbers: *N* (≤105), the total number of the members in the supply chain (and hence they are numbered from 0 to *N*−1); *P*, the price given by the root supplier; and *r*, the percentage rate of price increment for each distributor or retailer. Then the next line contains *N* numbers, each number Si is the index of the supplier for the *i*-th member. S*root* for the root supplier is defined to be −1. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, print in one line the highest price we can expect from some retailers, accurate up to 2 decimal places, and the number of retailers that sell at the highest price. There must be one space between the two numbers. It is guaranteed that the price will not exceed 1010.

### Sample Input:

```in
9 1.80 1.00
1 5 4 4 -1 4 5 3 6
```

### Sample Output:

```out
1.85 2
```

### Explaining

给出供应链和供应价格，根节点应该就是最后的零售商，每个节点的数字表示这个节点的供应商（其实也就是父节点），要求最高零售价和卖出这个零售价的零售商个数

### Thinking

其实就是根据给出的信息求树的层次遍历，求出最高的权值和最深的深度的节点数

### Code

```c++
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct node
{
	int data;
	vector<int> child;
};

vector<node> v;
double maxP = 0;
int maxCount = 0;

int n;
double r;
double p;

vector<double> pList;
void dfs(int root, int depth)
{
	if (v[root].child.size() == 0)
	{
		double price = p * pow(1 + r / 100, depth);
		v[root].data = price;
		pList.emplace_back(price);
		if (price > maxP)
			maxP = price;
		return;
	}
	else
	{
		for (int i = 0; i < v[root].child.size(); ++i)
			dfs(v[root].child[i], depth + 1);
	}
}
int main()
{
	cin >> n >> p >> r;
	v.resize(n);
	int root = 0;
	for (int i = 0; i < n; ++i)
	{
		int k;
		cin >> k;
		if (k != -1)
			v[k].child.emplace_back(i);
		else
			root = i;
	}
	dfs(root, 0);

	for (int i = 0; i < pList.size(); i++)
	{
		if (pList[i] == maxP)
			maxCount++;
	}
	printf("%.2f %d", maxP, maxCount);
	return 0;
}
```



## 1094 The Largest Generation (25)

A family hierarchy is usually presented by a pedigree tree where all the nodes on the same level belong to the same generation. Your task is to find the generation with the largest population.

### Input Specification:

Each input file contains one test case. Each case starts with two positive integers *N* (<100) which is the total number of family members in the tree (and hence assume that all the members are numbered from 01 to *N*), and *M* (<*N*) which is the number of family members who have children. Then *M* lines follow, each contains the information of a family member in the following format:

```
ID K ID[1] ID[2] ... ID[K]
```

where `ID` is a two-digit number representing a family member, `K` (>0) is the number of his/her children, followed by a sequence of two-digit `ID`'s of his/her children. For the sake of simplicity, let us fix the root `ID` to be `01`. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, print in one line the largest population number and the level of the corresponding generation. It is assumed that such a generation is unique, and the root level is defined to be 1.

### Sample Input:

```in
23 13
21 1 23
01 4 03 02 04 05
03 3 06 07 08
06 2 12 13
13 1 21
08 2 15 16
02 2 09 10
11 2 19 20
17 1 22
05 1 11
07 1 14
09 1 17
10 1 18
```

### Sample Output:

```out
9 4
```

### Explaining

根据给出的数据建立一棵树，输出节点数最多的一层：节点数，层数

### Thinking

bfs建树，dfs获取层数和节点数（记录最大的）

### Code

```c++
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node
{
	int data;
	vector<int> child;
	int level;
};

vector<node> v;
map<int, int> generationChildren;
int largestG = 0 , largestL = 0;

void dfs(int root, int level)
{
	v[root].level = level;
	generationChildren[level]++;
	if (generationChildren[level] > largestG)
	{
		largestG = generationChildren[level];
		largestL = level;
	}

	if (v[root].child.size() == 0)		
		return;
	else
	{
		for (int i = 0; i < v[root].child.size(); ++i)
			dfs(v[root].child[i], level + 1);
	}

}
int main()
{
	int n, m;
	cin >> n >> m;
	v.resize(n+1);
	for (int i = 0; i < m; i++)
	{
		int id, k;
		cin >> id >> k;
		v[id].child.resize(k);
		for (int j = 0; j < k; j++)
			cin >> v[id].child[j];
	}

	dfs(1, 1);

	cout << largestG << " " << largestL;
	return 0;
}
```



## 1102 Invert a Binary Tree (25)

The following is from Max Howell @twitter:

```repl
Google: 90% of our engineers use the software you wrote (Homebrew), but you can't invert a binary tree on a whiteboard so fuck off.
```

Now it's your turn to prove that YOU CAN invert a binary tree!

### Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤10) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to *N*−1. Then *N* lines follow, each corresponds to a node from 0 to *N*−1, and gives the indices of the left and right children of the node. If the child does not exist, a `-` will be put at the position. Any pair of children are separated by a space.

### Output Specification:

For each test case, print in the first line the level-order, and then in the second line the in-order traversal sequences of the inverted tree. There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.

### Sample Input:

```in
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
```

### Sample Output:

```out
3 7 2 6 4 0 5 1
6 5 7 4 3 2 0 1
```

### Explaining

给出一颗二叉树的模型，要求输出反转以后的层序和中序

### Thinking

广度优先反转左右子树建立树，直接对此树进行层序和中序遍

### Code

```c++
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
```



## 1106 Lowest Price in Supply Chain (25)

A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- everyone involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price *P* and sell or distribute them in a price that is *r*% higher than *P*. Only the retailers will face the customers. It is assumed that each member in the supply chain has exactly one supplier except the root supplier, and there is no supply cycle.

Now given a supply chain, you are supposed to tell the lowest price a customer can expect from some retailers.

### Input Specification:

Each input file contains one test case. For each case, The first line contains three positive numbers: *N* (≤105), the total number of the members in the supply chain (and hence their ID's are numbered from 0 to *N*−1, and the root supplier's ID is 0); *P*, the price given by the root supplier; and *r*, the percentage rate of price increment for each distributor or retailer. Then *N* lines follow, each describes a distributor or retailer in the following format:

*K**i* ID[1] ID[2] ... ID[*K**i*]

where in the *i*-th line, *K**i* is the total number of distributors or retailers who receive products from supplier *i*, and is then followed by the ID's of these distributors or retailers. *K**j* being 0 means that the *j*-th member is a retailer. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, print in one line the lowest price we can expect from some retailers, accurate up to 4 decimal places, and the number of retailers that sell at the lowest price. There must be one space between the two numbers. It is guaranteed that the all the prices will not exceed 1010.

### Sample Input:

```in
10 1.80 1.00
3 2 3 5
1 9
1 4
1 7
0
2 6 1
1 8
0
0
0
```

### Sample Output:

```out
1.8362 2
```

### Code

```c++
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct node
{
	double data;
	vector<int> child;
	double price;
}a[1000001];

double r, p;
double lowestP = -1.0;
void dfs(int root, int depth)
{
	if (a[root].child.size() == 0)//叶子节点
	{
		a[root].price = a[root].data * pow(1 + r, depth);
		if (lowestP == -1.0 || a[root].price < lowestP)
			lowestP = a[root].price;
		return;
	}
	else
	{
		for (int i = 0; i < a[root].child.size(); ++i)
			dfs(a[root].child[i], depth + 1);
	}
}
int main()
{
	int n;
	scanf("%d %lf %lf", &n, &p, &r);
	r = r / 100;
	for (int i = 0; i < n; i++)
	{
		int k;
		cin >> k;
		if (k != 0)
		{
			a[i].child.resize(k);
			for (int j = 0; j < k; j++)
				cin >> a[i].child[j];
		}
		a[i].data = p;
	}
	dfs(0, 0);

	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (lowestP == a[i].price)
			count++;
	}

	printf("%.4f %d", lowestP,count);
	return 0;
}


```



## 1115 Counting Nodes in a BST (30)

A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than or equal to the node's key.
- The right subtree of a node contains only nodes with keys greater than the node's key.
- Both the left and right subtrees must also be binary search trees.

Insert a sequence of numbers into an initially empty binary search tree. Then you are supposed to count the total number of nodes in the lowest 2 levels of the resulting tree.

### Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤1000) which is the size of the input sequence. Then given in the next line are the *N* integers in [−1000,1000] which are supposed to be inserted into an initially empty binary search tree.

### Output Specification:

For each case, print in one line the numbers of nodes in the lowest 2 levels of the resulting tree in the format:

```
n1 + n2 = n
```

where `n1` is the number of nodes in the lowest level, `n2` is that of the level above, and `n` is the sum.

### Sample Input:

```in
9
25 30 42 16 20 20 35 -5 28
```

### Sample Output:

```out
2 + 4 = 6
```





## 1119 Pre- and Post-order Traversals (30)

Suppose that all the keys in a binary tree are distinct positive integers. A unique binary tree can be determined by a given pair of postorder and inorder traversal sequences, or preorder and inorder traversal sequences. However, if only the postorder and preorder traversal sequences are given, the corresponding tree may no longer be unique.

Now given a pair of postorder and preorder traversal sequences, you are supposed to output the corresponding inorder traversal sequence of the tree. If the tree is not unique, simply output any one of them.

### Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (≤ 30), the total number of nodes in the binary tree. The second line gives the preorder sequence and the third line gives the postorder sequence. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, first printf in a line `Yes` if the tree is unique, or `No` if not. Then print in the next line the inorder traversal sequence of the corresponding binary tree. If the solution is not unique, any answer would do. It is guaranteed that at least one solution exists. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

### Sample Input 1:

```in
7
1 2 3 4 6 7 5
2 6 7 4 5 3 1
```

### Sample Output 1:

```out
Yes
2 1 6 4 7 3 5
```

### Sample Input 2:

```in
4
1 2 3 4
2 4 3 1
```

### Sample Output 2:

```out
No
2 1 3 4
```

### Explaining

仅给出后序和先序序列的情况下，树的结构可能不唯一，如果唯一输出YES，并且输出中序序列，如果不唯一输出NO，也输出中序序列；

### Thinking

- 先序和后序的对应关系
  - 先序的根和后序的根相等时，先序的左孩子序列号对应的是后序的右孩子序列号
- 如何判断是否唯一
  - 如果根节点离左孩子的距离大于1，则有唯一解，并且遍历根左边的子树；
  - 否则 有多解

### Code

```c++
#include <iostream>
#include <vector>
using namespace std;
vector<int> in, pre, post;
bool unique = true;
void getIn(int preLeft, int preRight, int postLeft, int postRight) 
{
	if (preLeft == preRight) 
	{
		in.push_back(pre[preLeft]);
		return;
	}
	if (pre[preLeft] == post[postRight]) 
	{//先序的左孩子 是 后序的右孩子 的时候
		int i = preLeft + 1;

		//找到后序的根节点在先序的位置
		while (i <= preRight && pre[i] != post[postRight - 1]) 
			i++;

		//如果根节点离左孩子的距离大于1 则有唯一解
		if (i - preLeft > 1)//遍历根左边的子树
			getIn(preLeft + 1, i - 1, postLeft, postLeft + (i - preLeft - 1) - 1);
		else//否则 有多解
			unique = false;
		in.push_back(post[postRight]);
		
		//遍历根右边的子树
		getIn(i, preRight, postLeft + (i - preLeft - 1), postRight - 1);
	}
}
int main() {
	int n;
	scanf("%d", &n);
	pre.resize(n), post.resize(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &pre[i]);
	for (int i = 0; i < n; i++)
		scanf("%d", &post[i]);
	getIn(0, n - 1, 0, n - 1);
	printf("%s\n%d", unique == true ? "Yes" : "No", in[0]);
	for (int i = 1; i < in.size(); i++)
		printf(" %d", in[i]);
	printf("\n");
	return 0;
}
```



# 深度优先搜索

## 1103 Integer Factorization (30)

The *K*−*P* factorization of a positive integer *N* is to write *N* as the sum of the *P*-th power of *K* positive integers. You are supposed to write a program to find the *K*−*P* factorization of *N* for any positive integers *N*, *K* and *P*.

### Input Specification:

Each input file contains one test case which gives in a line the three positive integers *N* (≤400), *K* (≤*N*) and *P* (1<*P*≤7). The numbers in a line are separated by a space.

### Output Specification:

For each case, if the solution exists, output in the format:

```
N = n[1]^P + ... n[K]^P
```

where `n[i]` (`i` = 1, ..., `K`) is the `i`-th factor. All the factors must be printed in non-increasing order.

Note: the solution may not be unique. For example, the 5-2 factorization of 169 has 9 solutions, such as 122+42+22+22+12, or 112+62+22+22+22, or more. You must output the one with the maximum sum of the factors. If there is a tie, the largest factor sequence must be chosen -- sequence { *a*1,*a*2,⋯,*a**K* } is said to be **larger** than { *b*1,*b*2,⋯,*b**K* } if there exists 1≤*L*≤*K* such that *a**i*=*b**i* for *i*<*L* and *a**L*>*b**L*.

If there is no solution, simple output `Impossible`.

### Sample Input 1:

```in
169 5 2
```

### Sample Output 1:

```out
169 = 6^2 + 6^2 + 6^2 + 6^2 + 5^2
```

### Sample Input 2:

```in
169 167 3
```

### Sample Output 2:

```out
Impossible
```

### Explaining

要求输出，满足K个数的P次方相加为N，最大的序列{nK}，如果不存在输出Impossible

### Thinking

- 取所有p次方小于N的数，作为备用序列
- 从序列最大的数开始遍历，如果当前总和小于N则继续深度搜索，直到当前总和等于N或者备用序列被遍历完
- 如果当前搜索次数已满足k，则判断总和与N的大小，相同则输出序列，不同则返回Impossible

### Code

```c++
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, k, p;
int maxFacSum = -1;
vector<int> ans,tmpAns;
vector<int> factor;

void initFactor()
{
	int index = 1;
	int tmp = 0;
	while (tmp <= n)
	{
		factor.emplace_back(tmp);
		tmp = pow(index, p);
		index++;
	}
}
void dfs(int index,int tmpK,int facSum,int tmpSum)
{
	if (tmpK == k)
	{
		if (tmpSum == n && facSum > maxFacSum)
		{
			maxFacSum = facSum;
			ans = tmpAns;
		}
		return;
	}
	while(index >= 1)
	{
		if (tmpSum + factor[index] <= n)
		{
			tmpAns[tmpK] = index;
			dfs(index, tmpK+1, facSum + index,tmpSum + factor[index]);
		}
		if (index == 1)return;
		index--;
	}

}
int main()
{
	cin >> n >> k >> p;
	tmpAns.resize(n);
	initFactor();
	dfs(factor.size() - 1, 0, 0, 0);

	if (maxFacSum == -1)
		cout << "Impossible";
	else
	{
		printf("%d = %d^%d", n, ans[0], p);
		for(int i = 1 ; i < k;i++)
			printf(" + %d^%d", ans[i], p);
	}
	return 0;
}
```



# 广度优先搜索

## 1091 Acute Stroke (30)

One important factor to identify acute stroke (急性脑卒中) is the volume of the stroke core. Given the results of image analysis in which the core regions are identified in each MRI slice, your job is to calculate the volume of the stroke core.

### Input Specification:

Each input file contains one test case. For each case, the first line contains 4 positive integers: *M*, *N*, *L* and *T*, where *M* and *N* are the sizes of each slice (i.e. pixels of a slice are in an *M*×*N* matrix, and the maximum resolution is 1286 by 128); *L* (≤60) is the number of slices of a brain; and *T* is the integer threshold（整数阈值） (i.e. if the volume（体积） of a connected core is less than *T*, then that core must not be counted).

Then *L* slices are given. Each slice is represented by an *M*×*N* matrix of 0's and 1's, where 1 represents a pixel （像素）of stroke, and 0 means normal. Since the thickness of a slice is a constant, we only have to count the number of 1's to obtain the volume. However, there might be several separated core regions in a brain, and only those with their volumes no less than *T* are counted. Two pixels are **connected** and hence belong to the same region if they share a common side, as shown by Figure 1 where all the 6 red pixels are connected to the blue one.

![figstroke.jpg](https://images.ptausercontent.com/f85c00cc-62ce-41ff-8dd0-d1c288d87409.jpg)

Figure 1

### Output Specification:

For each case, output in a line the total volume of the stroke core.

### Sample Input:

```in
3 4 5 2
1 1 1 1
1 1 1 1
1 1 1 1
0 0 1 1
0 0 1 1
0 0 1 1
1 0 1 1
0 1 0 0
0 0 0 0
1 0 1 1
0 0 0 0
0 0 0 0
0 0 0 1
0 0 0 1
1 0 0 0
```

### Sample Output:

```out
26
```

### Explaining

在M×N×L的三维模型中找到连续的方块面积大于T的方块总数，连续方块被认为是同一方块的上下左右前后方块

### Thinking

使用队列存储一个方块的相邻方块，一边记录方块数量，大于T的数量计入总面积

### Code

```c++
#include <iostream>
#include <queue>

using namespace std;

//节点结构 默认构造函数新建方便
struct node
{
	int x, y, z;

	node() {}
	node(int x, int y, int z) :
		x(x), y(y), z(z) {}
};

//原始矩阵 访问矩阵
int m, n, l,t;
int a[60][1286][128];
bool v[60][1286][128];

//三个坐标的变化数组 分别对应一个节点的上下左右前后节点
int dx[6] = { 1,0,0,-1,0,0 };
int dy[6] = { 0,1,0,0,-1,0 };
int dz[6] = { 0,0,1,0,0,-1 };

bool jude(int x, int y, int z)
{
	if (x < 0 || x >= l || y < 0 || y >= m || z < 0 || z >= n)
		return false;
	if (a[x][y][z] == 0 || v[x][y][z] == true)
		return false;

	return true;
}

int bfs(int x, int y, int z)
{
	int cnt = 0;
	node brain(x, y, z);
	queue<node> q;
	q.push(brain);
	v[x][y][z] = true;
	while (!q.empty())
	{
		node tmp = q.front();
		q.pop();
		cnt++;
		for (int i = 0; i < 6; i++)
		{
			int nx = tmp.x + dx[i];
			int ny = tmp.y + dy[i];
			int nz = tmp.z + dz[i];
			if (!jude(nx, ny ,nz))
				continue;
			node newN(nx, ny, nz);
			q.push(newN);
			v[nx][ny][nz] = true;
		}
	}
	if (cnt >= t)
		return cnt;
	else
		return 0;
}

int main()
{
	cin >> m >> n >> l >> t;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < n; k++)
				cin >> a[i][j][k];

	int ans = 0;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < n; k++)
				if (a[i][j][k] == 1 && v[i][j][k] == false)
					ans += bfs(i, j, k);

	cout << ans;
	return 0;

}
```



# 最短路径

## 1003 Emergency (25)

As an emergency rescue team leader of a city, you are given a special map of your country. The map shows several scattered cities connected by some roads. Amount of rescue teams in each city and the length of each road between any pair of cities are marked on the map. When there is an emergency call to you from some other city, your job is to lead your men to the place as quickly as possible, and at the mean time, call up as many hands on the way as possible.

### Input Specification:

Each input file contains one test case. For each test case, the first line contains 4 positive integers: *N* (≤500) - the number of cities (and the cities are numbered from 0 to *N*−1), *M* - the number of roads, *C*1 and *C*2 - the cities that you are currently in and that you must save, respectively. The next line contains *N* integers, where the *i*-th integer is the number of rescue teams in the *i*-th city. Then *M* lines follow, each describes a road with three integers *c*1, *c*2 and *L*, which are the pair of cities connected by a road and the length of that road, respectively. It is guaranteed that there exists at least one path from *C*1 to *C*2.

### Output Specification:

For each test case, print in one line two numbers: the number of different shortest paths between *C*1 and *C*2, and the maximum amount of rescue teams you can possibly gather. All the numbers in a line must be separated by exactly one space, and there is no extra space allowed at the end of a line.

### Sample Input:

```in
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1
```

### Sample Output:

```out
2 4
```

### Explaining

n是城市的数量（节点数），m是路径数（分支数），c1是当前的城市，c2是必须拯救的城市，

第二行是每个城市的救援队

第三行开始m行是每两个城市之间的路径数

要求输出救援的最短路径，以及接触最多的救援队个数

### Thinking

遍历一个有权图，获取给出两个节点的最短路径，和最大权值

按顺序存储一个图，每个节点都有权值和可联通的节点

从c1开始深度遍历，直到可联通节点全部遍历完或者遇到c2结束

### Code

```c++
//全错的代码
#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct city
{
	int team;
	map<int,int> path;
};

vector<city> c;

int n, m, c1, c2;
int maxTeamCount = 0, shortestLength = 9999;
void dfs(int index,int tmpL, int tmpC)
{
	if(c[index].path.size() == 0 )
		return;
	if (index == c2)
	{
		if (tmpL < shortestLength)
			shortestLength = tmpL;
		if (tmpC > maxTeamCount)
			maxTeamCount = tmpC;
		return;
	}

	map<int, int>::iterator i;
	for (i = c[index].path.begin(); i != c[index].path.end(); i++)
	{
		int id = i->first;
		int pa = i->second;
		dfs(id, tmpL + pa, tmpC + c[index].team);
	}

}

int main()
{
	cin >> n >> m >> c1 >> c2;
	c.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> c[i].team;
	}
	for (int j = 0; j < m; j++)
	{
		int a, b, l;
		cin >> a >> b >> l;
		c[a].path.emplace(b, l);
	}
	dfs(c1, 0, c[c1].team);

	cout << shortestLength << " " << maxTeamCount;

	return 0;
}
```

### Thinking 2

使用dijkstra算法求最短路径以及最短路径花费

### Code 2

```c++
#pragma warning(disable:4996)

#include <iostream>
#include <algorithm>
using namespace std;

int in[1010], level[1010], n, t = 0;

void inOrder(int root)
{
	if (root >= n)
		return;
	inOrder(2 * root );
	level[root] = in[t++];
	inOrder(2 * root + 1);
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



# 哈希、散列

## 1048 Find Coins (25分)

Eva loves to collect coins from all over the universe, including some other planets like Mars. One day she visited a universal shopping mall which could accept all kinds of coins as payments. However, there was a special requirement of the payment: for each bill, she could only use exactly two coins to pay the exact amount. Since she has as many as 105 coins with her, she definitely needs your help. You are supposed to tell her, for any given amount of money, whether or not she can find two coins to pay for it.

### Input Specification:

Each input file contains one test case. For each case, the first line contains 2 positive numbers: *N* (≤105, the total number of coins) and *M* (≤103, the amount of money Eva has to pay). The second line contains *N* face values of the coins, which are all positive numbers no more than 500. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, print in one line the two face values *V*1 and *V*2 (separated by a space) such that *V*1+*V*2=*M* and *V*1≤*V*2. If such a solution is not unique, output the one with the smallest *V*1. If there is no solution, output `No Solution` instead.

### Sample Input 1:

```in
8 15
1 2 8 7 2 4 11 15
```

### Sample Output 1:

```out
4 11
```

### Sample Input 2:

```in
7 14
1 8 7 2 4 11 15
```

### Sample Output 2:

```out
No Solution
```

### Explaining

在一个序列中求和为目标值的两个数

### Thinking

学习非暴力解法，使用哈希集合解决。

c++哈希集合构建思想：序列值作为下标，数组元素表示该数据是否存在

求和思想：当前值未到目标值，且与目标值的差值在序列中

### Code

```C++
#include <iostream>
int a[1001];

using namespace std;

int main()
{
	int n, m, tmp;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tmp);
		a[tmp]++;//a是一个哈希集合
	}

	for (int i = 0; i < 1001; i++)
	{
		if (a[i])
		{
			a[i]--;
			if (m > i && a[m - i])//i未到目标值，且与目标值的差值在序列中
			{
				if(i < m-i)
					printf("%d %d", i, m - i);
				else
					printf("%d %d", m-i, i);
				return 0;
			}
			a[i]++;
		}
	}

	printf("No Solution");
	return 0;
}
```



## 1050 String Subtraction (20分)

Given two strings *S*1 and *S*2, *S*=*S*1−*S*2 is defined to be the remaining string after taking all the characters in *S*2 from *S*1. Your task is simply to calculate *S*1−*S*2 for any given strings. However, it might not be that simple to do it **fast**.

### Input Specification:

Each input file contains one test case. Each case consists of two lines which gives *S*1 and *S*2, respectively. The string lengths of both strings are no more than 104. It is guaranteed that all the characters are visible ASCII codes and white space, and a new line character signals the end of a string.

### Output Specification:

For each test case, print *S*1−*S*2 in one line.

### Sample Input:

```in
They are students.
aeiou
```

### Sample Output:

```out
Thy r stdnts.
```

### Explaining

从字符串1中剔除字符串2，输出结果

### Thinking

我的：字符串1存在一个数组里s1，字符串2存在一个数组里s2，遍历s1，每个元素分别与s2中的元素相减

遍历s1输出所有非零的元素值。

柳婼：分别存储两个字符串，然后使用布尔型数组记录s2，遍历s1的所有元素，布尔型数组里false的全部输出

### Code

```c++
#include <iostream>
#include <cstring>

using namespace std;

char s1[100000], s2[100000];
int main()
{
	cin.getline(s1, 100000);
	cin.getline(s2, 100000);
	int len1 = strlen(s1);
	int len2 = strlen(s2);

	bool flag[100000] = { false };
	for (int i = 0; i < len2; i++)
	{
		flag[s2[i]] = true;
	}

	for (int i = 0; i < len1; i++)
	{
		if (!flag[s1[i]])
			printf("%c", s1[i]);
	}

	return 0;
}

```



## 1092 To Buy or Not to Buy (20分)

Eva would like to make a string of beads with her favorite colors so she went to a small shop to buy some beads. There were many colorful strings of beads. However the owner of the shop would only sell the strings in whole pieces. Hence Eva must check whether a string in the shop contains all the beads she needs. She now comes to you for help: if the answer is `Yes`, please tell her the number of extra beads she has to buy; or if the answer is `No`, please tell her the number of beads missing from the string.

For the sake of simplicity, let's use the characters in the ranges [0-9], [a-z], and [A-Z] to represent the colors. For example, the 3rd string in Figure 1 is the one that Eva would like to make. Then the 1st string is okay since it contains all the necessary beads with 8 extra ones; yet the 2nd one is not since there is no black bead and one less red bead.

![figbuy.jpg](https://images.ptausercontent.com/b7e2ffa6-8819-436d-ad79-a41263abe914.jpg)

Figure 1

### Input Specification:

Each input file contains one test case. Each case gives in two lines the strings of no more than 1000 beads which belong to the shop owner and Eva, respectively.

### Output Specification:

For each test case, print your answer in one line. If the answer is `Yes`, then also output the number of extra beads Eva has to buy; or if the answer is `No`, then also output the number of beads missing from the string. There must be exactly 1 space between the answer and the number.

### Sample Input 1:

```in
ppRYYGrrYBR2258
YrR8RrY
```

### Sample Output 1:

```out
Yes 8
```

### Sample Input 2:

```in
ppRYYGrrYB225
YrR8RrY
```

### Sample Output 2:

```out
No 2
```

### Explaining

匹配两个字符串的相同序列，所给s全部含有目标串的话，输出yes和除匹配上的字符之外的字符个数

所给s不能全部包含的话，输出no和匹配不上的字符个数

### Thinking

跟上面那题差不多。也是准备两个字符串数组，一个布尔型数组，两个int值来记录字符个数；

布尔型数组用来匹配所给串和目标串，一个int记录匹配上的字符，一个int记录未匹配的字符。

如果匹配上的字符数大于等于目标串字符数，则输出yes和未匹配的字符数；

如果匹配上的字符小于目标串字符数，则输出no和（目标串字符数-匹配上字符数）。



注意：目标串可能有元素重复情况，不能用布尔型存储，改为用整型数组存储。匹配的时候可以减去整型数组元素值；

### Code

```c++
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	char s1[10000], s2[10000];
	cin.getline(s1, 10000);
	cin.getline(s2, 10000);

	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int flag[10000] = { 0 };
	for (int i = 0; i < len2; i++)
		flag[s2[i]]++;
	int matched = 0, unmatched = 0;
	for (int i = 0; i < len1; i++)
	{
		if (flag[s1[i]])
		{
			matched++;
			flag[s1[i]]--;
		}
		else
			unmatched++;
	}

	if (matched >= len2)
		printf("Yes %d", unmatched);
	else
		printf("No %d", len2 - matched);

	return 0;
}
```



## 1084 Broken Keyboard (20分)

On a broken keyboard, some of the keys are worn out. So when you type some sentences, the characters corresponding to those keys will not appear on screen.

Now given a string that you are supposed to type, and the string that you actually type out, please list those keys which are for sure worn out.

### Input Specification:

Each input file contains one test case. For each case, the 1st line contains the original string, and the 2nd line contains the typed-out string. Each string contains no more than 80 characters which are either English letters [A-Z] (case insensitive), digital numbers [0-9], or `_` (representing the space). It is guaranteed that both strings are non-empty.

### Output Specification:

For each test case, print in one line the keys that are worn out, in the order of being detected. The English letters must be capitalized. Each worn out key must be printed once only. It is guaranteed that there is at least one worn out key.

### Sample Input:

```in
7_This_is_a_test
_hs_s_a_es
```

### Sample Output:

```out
7TI
```

### Explaining

输出s1里出现但是s2里未出现的字符

### Thinking1

两个字符串数组，一个布尔型数组

遍历s1，输出s2flag为false的值

注意大小写转化

### Code1

```c++
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main()
{
	char s1[10000], s2[10000];
	cin.getline(s1, 10000);
	cin.getline(s2, 10000);

	int len1 = strlen(s1);
	int len2 = strlen(s2);

	bool flag[10000] = { false };
	for (int i = 0; i < len2; i++)
	{
		flag[s2[i]] = true;
	}

	bool printed[10000] = { false };
	for (int i = 0; i < len1; i++)
	{
		if (flag[tolower(s1[i])] || flag[s1[i]])
			continue;
		if (!printed[toupper(s1[i])])
		{
			printf("%c", toupper(s1[i]));
			printed[toupper(s1[i])] = true;
		}
	}
	return 0;
}
```

### Thinking2

使用find函数，和string::npos 查找字符串里的某个字符

判断条件在s1中却不在s2中，并且不在结果字符串中

### Code2

```c++
#include <iostream>
#include <cctype>
using namespace std;
int main() {
    string s1, s2, ans;
    cin >> s1 >> s2;
    for (int i = 0; i < s1.length(); i++)
        if (s2.find(s1[i]) == string::npos && ans.find(toupper(s1[i])) == string::npos)
            ans += toupper(s1[i]);
    cout << ans;
    return 0;
}
```





# 排序算法

## 1012 The Best Rank (25分)

To evaluate the performance of our first year CS majored students, we consider their grades of three courses only: `C` - C Programming Language, `M` - Mathematics (Calculus or Linear Algrbra), and `E` - English. At the mean time, we encourage students by emphasizing on their best ranks -- that is, among the four ranks with respect to the three courses and the average grade, we print the best rank for each student.

For example, The grades of `C`, `M`, `E` and `A` - Average of 4 students are given as the following:

```
StudentID  C  M  E  A
310101     98 85 88 90
310102     70 95 88 84
310103     82 87 94 88
310104     91 91 91 91
```

Then the best ranks for all the students are No.1 since the 1st one has done the best in C Programming Language, while the 2nd one in Mathematics, the 3rd one in English, and the last one in average.

### Input Specification:

Each input file contains one test case. Each case starts with a line containing 2 numbers *N* and *M* (≤2000), which are the total number of students, and the number of students who would check their ranks, respectively. Then *N* lines follow, each contains a student ID which is a string of 6 digits, followed by the three integer grades (in the range of [0, 100]) of that student in the order of `C`, `M` and `E`. Then there are *M* lines, each containing a student ID.

### Output Specification:

For each of the *M* students, print in one line the best rank for him/her, and the symbol of the corresponding rank, separated by a space.

The priorities of the ranking methods are ordered as `A` > `C` > `M` > `E`. Hence if there are two or more ways for a student to obtain the same best rank, output the one with the highest priority.

If a student is not on the grading list, simply output `N/A`.

### Sample Input:

```in
5 6
310101 98 85 88
310102 70 95 88
310103 82 87 94
310104 91 91 91
310105 85 90 90
310101
310102
310103
310104
310105
999999
```

### Sample Output:

```out
1 C
1 M
1 E
1 A
3 A
N/A
```

### Explaining

对每个学生的三门成绩和平均分分别排序，输出所给序号最佳的成绩排序，如果所给序号不在成绩单上，输出N/A

### Thinking

对学生创建一个结构体，结构体里存储学号、各科成绩、各科排名、最佳排名。

难点在于对各科成绩排名并获取到各科排名。

使用sort函数+自定义cmp，分别对分数数组排序，并记录此时的rank数组。二次遍历取到最佳的rank值，最后输出查询结果。

### Code

```c++

#include <cstdio>
#include <algorithm>

using namespace std;
struct stu
{
    int id,best;
    int score[4],rank[4];
};
stu stuReport[2005];
int exist[1000000];
int flag = -1;

bool cmp(stu a, stu b)
{
    return a.score[flag]>b.score[flag];
}


int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d %d %d",&stuReport[i].id,&stuReport[i].score[1],&stuReport[i].score[2],&stuReport[i].score[3]);
        stuReport[i].score[0] = (stuReport[i].score[1]+stuReport[i].score[2]+stuReport[i].score[3])/3.0 + 0.5;
    }

    for(flag = 0; flag <=3; flag++)
    {
        sort(stuReport, stuReport+n, cmp);
        stuReport[0].rank[flag] = 1;
        for(int i = 1; i < n; i++)
        {
            stuReport[i].rank[flag] = i+1;
            if(stuReport[i].score[flag] == stuReport[i-1].score[flag])//如果是分数相同 排名也相同
            {
                stuReport[i].rank[flag] = stuReport[i-1].rank[flag];
            }
        }
    }
    
    //获取最佳排名
    for(int i = 0; i < n; i++)
    {
        exist[stuReport[i].id] = i+1;
        int best = stuReport[i].rank[0];
        for(flag = 1; flag <= 3; flag ++)
        {
            if(stuReport[i].rank[flag] < best)
            {
                stuReport[i].best = flag;
                best = stuReport[i].rank[flag];
            }
        }
    }
    
    char t[5] = {'A','C','M','E'};
    for(int i = 0 ; i < m; i++)
    {
        int id = 0;
        scanf("%d", &id);
        int index = exist[id];
        if(index)
        {
            int best = stuReport[index-1].best;
            int rank = stuReport[index-1].rank[best];
            printf("%d %c\n",rank,t[best]);
        }
        else
            printf("N/A\n");
    }

    return 0;
}
```



## 1016 Phone Bills (25分)

A long-distance telephone company charges its customers by the following rules:

Making a long-distance call costs a certain amount per minute, depending on the time of day when the call is made. When a customer starts connecting a long-distance call, the time will be recorded, and so will be the time when the customer hangs up the phone. Every calendar month, a bill is sent to the customer for each minute called (at a rate determined by the time of day). Your job is to prepare the bills for each month, given a set of phone call records.

### Input Specification:

Each input file contains one test case. Each case has two parts: the rate structure, and the phone call records.

The rate structure consists of a line with 24 non-negative integers denoting the toll (cents/minute) from 00:00 - 01:00, the toll from 01:00 - 02:00, and so on for each hour in the day.

The next line contains a positive number *N* (≤1000), followed by *N* lines of records. Each phone call record consists of the name of the customer (string of up to 20 characters without space), the time and date (`MM:dd:HH:mm`), and the word `on-line` or `off-line`.

For each test case, all dates will be within a single month. Each `on-line` record is paired with the chronologically next record for the same customer provided it is an `off-line` record. Any `on-line` records that are not paired with an `off-line` record are ignored, as are `off-line` records not paired with an `on-line` record. It is guaranteed that at least one call is well paired in the input. You may assume that no two records for the same customer have the same time. Times are recorded using a 24-hour clock.

### Output Specification:

For each test case, you must print a phone bill for each customer.

Bills must be printed in alphabetical order of customers' names. For each customer, first print in a line the name of the customer and the month of the bill in the format shown by the sample. Then for each time period of a call, print in one line the beginning and ending time and date (`dd:HH:mm`), the lasting time (in minute) and the charge of the call. The calls must be listed in chronological order. Finally, print the total charge for the month in the format shown by the sample.

### Sample Input:

```in
10 10 10 10 10 10 20 20 20 15 15 15 15 15 15 15 20 30 20 15 15 10 10 10
10
CYLL 01:01:06:01 on-line
CYLL 01:28:16:05 off-line
CYJJ 01:01:07:00 off-line
CYLL 01:01:08:03 off-line
CYJJ 01:01:05:59 on-line
aaa 01:01:01:03 on-line
aaa 01:02:00:01 on-line
CYLL 01:28:15:41 on-line
aaa 01:05:02:24 on-line
aaa 01:04:23:59 off-line
```

### Sample Output:

```out
CYJJ 01
01:05:59 01:07:00 61 $12.10
Total amount: $12.10
CYLL 01
01:06:01 01:08:03 122 $24.40
28:15:41 28:16:05 24 $3.85
Total amount: $28.25
aaa 01
02:00:01 04:23:59 4318 $638.80
Total amount: $638.80
```

### Explanning



### Thinking



### Code





## 1025 PAT Ranking (25分)

Programming Ability Test (PAT) is organized by the College of Computer Science and Technology of Zhejiang University. Each test is supposed to run simultaneously in several places, and the ranklists will be merged immediately after the test. Now it is your job to write a program to correctly merge all the ranklists and generate the final rank.

### Input Specification:

Each input file contains one test case. For each case, the first line contains a positive number *N* (≤100), the number of test locations. Then *N* ranklists follow, each starts with a line containing a positive integer *K* (≤300), the number of testees, and then *K* lines containing the registration number (a 13-digit number) and the total score of each testee. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, first print in one line the total number of testees. Then print the final ranklist in the following format:

```
registration_number final_rank location_number local_rank
```

The locations are numbered from 1 to *N*. The output must be sorted in nondecreasing order of the final ranks. The testees with the same score must have the same rank, and the output must be sorted in nondecreasing order of their registration numbers.

### Sample Input:

```in
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85
```

### Sample Output:

```out
9
1234567890005 1 1 1
1234567890014 1 2 1
1234567890001 3 1 2
1234567890003 3 1 2
1234567890004 5 1 4
1234567890012 5 2 2
1234567890002 7 1 5
1234567890013 8 2 3
1234567890011 9 2 4
```

### Explanning

第一行给出考场总数（例子为2），下一行给出1号考场的考生数，以及每个考生的考号和分数。接着给出2号考场的考生数，和2号考场每个考生的考号和分数。

要求输出考生总数，考号，考生总排名，考生的考场号，考生在该考场的排名

### Thinking

就是首先对两个序列组间排序，然后两个序列共同排序



注意两个要点：

- 对于排序，相同分数取相同排名。下一排名仍从当前序号开始，直接使用循环变量作为排名序号
- 对于学号的排序（相同分数，学号小的先输出），可以使用string类型，也可以使用longlongint，输出的时候注意限定字符宽度为13

### Code

```C++
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
```



## 1028 List Sorting (25分)

Excel can sort records according to any column. Now you are supposed to imitate this function.

### Input Specification:

Each input file contains one test case. For each case, the first line contains two integers *N* (≤10^5) and *C*, where *N* is the number of records and *C* is the column that you are supposed to sort the records with. Then *N* lines follow, each contains a record of a student. A student's record consists of his or her distinct ID (a 6-digit number), name (a string with no more than 8 characters without space), and grade (an integer between 0 and 100, inclusive).

### Output Specification:

For each test case, output the sorting result in *N* lines. That is, if *C* = 1 then the records must be sorted in increasing order according to ID's; if *C* = 2 then the records must be sorted in non-decreasing order according to names; and if *C* = 3 then the records must be sorted in non-decreasing order according to grades. If there are several students who have the same name or grade, they must be sorted according to their ID's in increasing order.

### Sample Input 1:

```in
3 1
000007 James 85
000010 Amy 90
000001 Zoe 60
```

### Sample Output 1:

```out
000001 Zoe 60
000007 James 85
000010 Amy 90
```

### Sample Input 2:

```in
4 2
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 98
```

### Sample Output 2:

```out
000010 Amy 90
000002 James 98
000007 James 85
000001 Zoe 60
```

### Sample Input 3:

```in
4 3
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 90
```

### Sample Output 3:

```out
000001 Zoe 60
000007 James 85
000002 James 90
000010 Amy 90
```

### Explanning

给出排序的记录数以及排序的列号，对给出的成绩内容进行排序

### Thinking

先存储结构体，学号和成绩使用整型，人名使用string类型。

根据给出的C，调用不同的比较函数；

### Code

```C++
#pragma warning(disable:4996)

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;
struct record
{
	int no;
	string name;
	int grade;
};

bool cmp_no(record a, record b)
{
	return a.no < b.no;
}

bool cmp_name(record a, record b)
{
	if(a.name != b.name)
		return a.name < b.name;
	else
		return a.no < b.no;
}

bool cmp_grade(record a, record b)
{
	if(a.grade != b.grade)
		return a.grade < b.grade;
	else
		return a.no < b.no;
}

int main()
{
	record recs[100005];
	int n, c;
	cin >> n >> c;
	for (int i = 0; i < n; i++)
	{
		cin >> recs[i].no >> recs[i].name >> recs[i].grade;
	}

	switch (c) 
	{
	case 1:
		sort(recs, recs + n, cmp_no);
		break;
	case 2:
		sort(recs, recs + n, cmp_name);
		break;
	case 3:
		sort(recs, recs + n, cmp_grade);
		break;
	}

	for (int i = 0; i < n; i++)
	{
		printf("%06d %s %d\n", recs[i].no, recs[i].name.c_str(), recs[i].grade);
	}
	return 0;
}
```





## 1055 The World's Richest (25分)

Forbes magazine publishes every year its list of billionaires based on the annual ranking of the world's wealthiest people. Now you are supposed to simulate this job, but concentrate only on the people in a certain range of ages. That is, given the net worths of *N* people, you must find the *M* richest people in a given range of their ages.

### Input Specification:

Each input file contains one test case. For each case, the first line contains 2 positive integers: *N* (≤10^5) - the total number of people, and *K* (≤10^3) - the number of queries. Then *N* lines follow, each contains the name (string of no more than 8 characters without space), age (integer in (0, 200]), and the net worth (integer in [−10^6,10^6]) of a person. Finally there are *K* lines of queries, each contains three positive integers: *M* (≤100) - the maximum number of outputs, and [`Amin`, `Amax`] which are the range of ages. All the numbers in a line are separated by a space.

### Output Specification:

For each query, first print in a line `Case #X:` where `X` is the query number starting from 1. Then output the *M* richest people with their ages in the range [`Amin`, `Amax`]. Each person's information occupies a line, in the format

```
Name Age Net_Worth
```

The outputs must be in non-increasing order of the net worths. In case there are equal worths, it must be in non-decreasing order of the ages. If both worths and ages are the same, then the output must be in non-decreasing alphabetical order of the names. It is guaranteed that there is no two persons share all the same of the three pieces of information. In case no one is found, output `None`.

### Sample Input:

```in
12 4
Zoe_Bill 35 2333
Bob_Volk 24 5888
Anny_Cin 95 999999
Williams 30 -22
Cindy 76 76000
Alice 18 88888
Joe_Mike 32 3222
Michael 5 300000
Rosemary 40 5888
Dobby 24 5888
Billy 24 5888
Nobody 5 0
4 15 45
4 30 35
4 5 95
1 45 50
```

### Sample Output:

```out
Case #1:
Alice 18 88888
Billy 24 5888
Bob_Volk 24 5888
Dobby 24 5888
Case #2:
Joe_Mike 32 3222
Zoe_Bill 35 2333
Williams 30 -22
Case #3:
Anny_Cin 95 999999
Michael 5 300000
Alice 18 88888
Cindy 76 76000
Case #4:
None
```

### Explanning

给出候选人总数，和评选的挡位数。候选人信息包括名字，年龄和财富值。评选挡位包括，最大获奖人数和年龄限制。

输出每个挡位底下的获奖人。没有输出None

### Thinking

要写一个使用年龄上下限排序的函数，先使用上下限挑选出符合年龄限制的数据，然后对这些记录的财富排序。

财富值大的排在前面；

财富值相同，年龄小的排在前面

财富值年龄都相同，名字小的排在前面

### Code1

有一个测试点未通过，好像是超时，应该是算法不够精简

```c++
#pragma warning(disable:4996)

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct record
{
	string name;
	int age;
	int worths;
};
bool cmp(record a, record b)
{
	if (a.worths != b.worths)
		return a.worths > b.worths;
	else if (a.age != b.age)
		return a.age < b.age;
	else
		return a.name < b.name;
}

void sortByAgeRange(int low, int high, vector<record>& r,vector<record>& fit)
{
	for (int i = 0; i < r.size(); i++)
	{
		if (r[i].age >= low && r[i].age <= high)
		{
			fit.emplace_back(r[i]);
		}
	}
	if(!fit.empty())
		sort(fit.begin(), fit.end(), cmp);
}


int main()
{
	int n = 0, k = 0;
	scanf("%d %d", &n, &k);
	vector<record> r(n);
	for (int i = 0; i < n; i++)
	{
		cin >> r[i].name >> r[i].age >> r[i].worths;
	}

	for (int i = 0; i < k; i++)
	{
		int limit = 0;
		int min = 0, max = 0;
		cin >> limit >> min >> max;
		vector<record> fit;
		int fitCnt = 0;
		sortByAgeRange(min, max, r, fit);
		cout << "Case #" << i + 1 << ":" << endl;
		if (fit.empty())
		{
			cout << "None" << endl;
		}
		else
		{
			for (int j =0;j<limit && j < fit.size();j++)
			{
				printf("%s %d %d\n", fit[j].name.c_str(), fit[j].age, fit[j].worths);
			}

		}
	}

	return 0;
}
```

### Code2

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

struct record
{
	char name[10];
	int age;
	int worths;
};
bool cmp(record a, record b)
{
	if (a.worths != b.worths)
		return a.worths > b.worths;
	else if (a.age != b.age)
		return a.age < b.age;
	else
		return (strcmp(a.name, b.name) < 0);
}

int main()
{
	int n = 0, k = 0;
	scanf("%d %d", &n, &k);
	vector<record> rt(n),r;
	for (int i = 0; i < n; i++)
	{
		scanf("%s %d %d", rt[i].name, &rt[i].age, &rt[i].worths);
	}
	sort(rt.begin(), rt.end(), cmp);
	vector<int> book(205, 0);
	for (int i = 0; i < n; i++) {
		if (book[rt[i].age] < 100) {
			r.push_back(rt[i]);
			book[rt[i].age]++;
		}
	}
	for (int i = 0; i < k; i++)
	{
		int limit = 0;
		int min = 0, max = 0;
		cin >> limit >> min >> max;
		vector<record> fit;
		for (int j = 0; j < r.size(); j++)
		{
			if (r[j].age >= min && r[j].age <= max)
				fit.emplace_back(r[j]);
		}
		cout << "Case #" << i + 1 << ":" << endl;
		if (fit.empty())
		{
			cout << "None" << endl;
		}
		else
		{
			for (int j =0;j<limit && j < fit.size();j++)
			{
				printf("%s %d %d\n", fit[j].name, fit[j].age, fit[j].worths);
			}

		}
	}

	return 0;
}
```





## 1062 Talent and Virtue (25分)

About 900 years ago, a Chinese philosopher Sima Guang wrote a history book in which he talked about people's talent and virtue. According to his theory, a man being outstanding in both talent and virtue must be a "sage（圣人）"; being less excellent but with one's virtue outweighs talent can be called a "nobleman（君子）"; being good in neither is a "fool man（愚人）"; yet a fool man is better than a "small man（小人）" who prefers talent than virtue.

Now given the grades of talent and virtue of a group of people, you are supposed to rank them according to Sima Guang's theory.

### Input Specification:

Each input file contains one test case. Each case first gives 3 positive integers in a line: *N* (≤10^5), the total number of people to be ranked; *L* (≥60), the lower bound of the qualified grades -- that is, only the ones whose grades of talent and virtue are both not below this line will be ranked; and *H* (<100), the higher line of qualification -- that is, those with both grades not below this line are considered as the "sages", and will be ranked in non-increasing order according to their total grades. Those with talent grades below *H* but virtue grades not are cosidered as the "noblemen", and are also ranked in non-increasing order according to their total grades, but they are listed after the "sages". Those with both grades below *H*, but with virtue not lower than talent are considered as the "fool men". They are ranked in the same way but after the "noblemen". The rest of people whose grades both pass the *L* line are ranked after the "fool men".

Then *N* lines follow, each gives the information of a person in the format:

```
ID_Number Virtue_Grade Talent_Grade
```

where `ID_Number` is an 8-digit number, and both grades are integers in [0, 100]. All the numbers are separated by a space.

### Output Specification:

The first line of output must give *M* (≤*N*), the total number of people that are actually ranked. Then *M* lines follow, each gives the information of a person in the same format as the input, according to the ranking rules. If there is a tie of the total grade, they must be ranked with respect to their virtue grades in non-increasing order. If there is still a tie, then output in increasing order of their ID's.

### Sample Input:

```in
14 60 80
10000001 64 90
10000002 90 60
10000011 85 80
10000003 85 80
10000004 80 85
10000005 82 77
10000006 83 76
10000007 90 78
10000008 75 79
10000009 59 90
10000010 88 45
10000012 80 100
10000013 90 99
10000014 66 60
```

### Sample Output:

```out
12
10000013 90 99
10000012 80 100
10000003 85 80
10000011 85 80
10000004 80 85
10000007 90 78
10000006 83 76
10000005 82 77
10000002 90 60
10000014 66 60
10000008 75 79
10000001 64 90
```

### Explaining

根据给出的下限和上限，对记录的道德分数和天赋分数排序，排序规则如下：

1.德分和才分都超过下限，才参与排名

2.德分和才分都超过上限的，认为是圣人，按照总分排序；

3.才分低于上限，而德分高于上限的，认为是君子，按总分排序；

4.才分德分都低于上限的，且德分**不**低于才分的，认为是愚者，按总分排序

5.其他人排在愚者后面

### Thinking

结构体：长整型id，整型v_grade，整型t_grade，total

排序函数：按总分排序，总分相同的按id排序，

条件一在录入数据的时候可以使用，录入数据的时候分成四类

对四个数组分别排序

### Code

```c++
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
```

## 1075 PAT Judge (25分)

The ranklist of PAT is generated from the status list, which shows the scores of the submissions. This time you are supposed to generate the ranklist for PAT.

### Input Specification:

Each input file contains one test case. For each case, the first line contains 3 positive integers, *N* (≤104), the total number of users, *K* (≤5), the total number of problems, and *M* (≤105), the total number of submissions. It is then assumed that the user id's are 5-digit numbers from 00001 to *N*, and the problem id's are from 1 to *K*. The next line contains *K* positive integers `p[i]` (`i`=1, ..., *K*), where `p[i]` corresponds to the full mark of the i-th problem. Then *M* lines follow, each gives the information of a submission in the following format:

```
user_id problem_id partial_score_obtained
```

where `partial_score_obtained` is either −1 if the submission cannot even pass the compiler, or is an integer in the range [0, `p[problem_id]`]. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, you are supposed to output the ranklist in the following format:

```
rank user_id total_score s[1] ... s[K]
```

where `rank` is calculated according to the `total_score`, and all the users with the same `total_score` obtain the same `rank`; and `s[i]` is the partial score obtained for the `i`-th problem. If a user has never submitted a solution for a problem, then "-" must be printed at the corresponding position. If a user has submitted several solutions to solve one problem, then the highest score will be counted.

The ranklist must be printed in non-decreasing order of the ranks. For those who have the same rank, users must be sorted in nonincreasing order according to the number of perfectly solved problems. And if there is still a tie, then they must be printed in increasing order of their id's. For those who has never submitted any solution that can pass the compiler, or has never submitted any solution, they must NOT be shown on the ranklist. It is guaranteed that at least one user can be shown on the ranklist.

### Sample Input:

```in
7 4 20
20 25 25 30
00002 2 12
00007 4 17
00005 1 19
00007 2 25
00005 1 20
00002 2 2
00005 1 15
00001 1 18
00004 3 25
00002 2 25
00005 3 22
00006 4 -1
00001 2 18
00002 1 20
00004 1 15
00002 4 18
00001 3 4
00001 4 2
00005 2 -1
00004 2 0
```

### Sample Output:

```out
1 00002 63 20 25 - 18
2 00005 42 20 0 22 -
2 00007 42 - 25 - 17
2 00001 42 18 18 4 2
5 00004 40 15 0 25 -
```

### Expaining

输出每个提交用户的分数情况

### Thinking

根据分数记录，统计每个id的得分和每题的得分；

使用map存储记录，id作为key，每道题的分数存在vector里面

- 注意：
- 在结果中，未通过的题记为0分，没做的题记为-；
- 所以在存储过程中，对于每道题的初始分数要记为-2，未通过取原值-1

### Code

```c++
//#pragma warning(disable:4996)

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
```



## 1080 Graduate Admission (30分)

It is said that in 2011, there are about 100 graduate schools ready to proceed over 40,000 applications in Zhejiang Province. It would help a lot if you could write a program to automate the admission procedure.

Each applicant will have to provide two grades: the national entrance exam grade *G**E*, and the interview grade *G**I*. The final grade of an applicant is (*G**E*+*G**I*)/2. The admission rules are:

- The applicants are ranked according to their final grades, and will be admitted one by one from the top of the rank list.
- If there is a tied final grade, the applicants will be ranked according to their national entrance exam grade *G**E*. If still tied, their ranks must be the same.
- Each applicant may have *K* choices and the admission will be done according to his/her choices: if according to the rank list, it is one's turn to be admitted; and if the quota of one's most preferred shcool is not exceeded, then one will be admitted to this school, or one's other choices will be considered one by one in order. If one gets rejected by all of preferred schools, then this unfortunate applicant will be rejected.
- If there is a tied rank, and if the corresponding applicants are applying to the same school, then that school must admit all the applicants with the same rank, **even if its quota will be exceeded**.

### Input Specification:

Each input file contains one test case.

Each case starts with a line containing three positive integers: *N* (≤40,000), the total number of applicants; *M* (≤100), the total number of graduate schools; and *K* (≤5), the number of choices an applicant may have.

In the next line, separated by a space, there are *M* positive integers. The *i*-th integer is the quota of the *i*-th graduate school respectively.

Then *N* lines follow, each contains 2+*K* integers separated by a space. The first 2 integers are the applicant's *G**E* and *G**I*, respectively. The next *K* integers represent the preferred schools. For the sake of simplicity, we assume that the schools are numbered from 0 to *M*−1, and the applicants are numbered from 0 to *N*−1.

### Output Specification:

For each test case you should output the admission results for all the graduate schools. The results of each school must occupy a line, which contains the applicants' numbers that school admits. The numbers must be in increasing order and be separated by a space. There must be no extra space at the end of each line. If no applicant is admitted by a school, you must output an empty line correspondingly.

### Sample Input:

```in
11 6 3
2 1 2 2 2 3
100 100 0 1 2
60 60 2 3 5
100 90 0 3 4
90 100 1 2 0
90 90 5 1 3
80 90 1 0 2
80 80 0 1 2
80 80 0 1 2
80 70 1 3 2
70 80 1 2 3
100 100 0 2 4
```

### Sample Output:

```out
0 10
3
5 6 7
2 8

1 4
```

### Expaining

给出学校录取人数和学生分数及志愿，要求输出每个学校的录取结果，没有录取学生的空行

排序规则：

1 通过fi = （ge+gi）/2排序

2 fi相同时，按照ge排序

3 录取顺序必须遵循学生志愿，按照学生志愿依次寻找未录满的学校，（已录满的学校跟最后一名比排名，排名低于最后一名，不予录取）如果全部没有录上，则该考生落榜

4 只要是排名相同，即使超额也要录取

### Thinking

结构体：学生id，ge，gi，pre[]

school[]每个学校的上限

比较函数:均分第一优先级，ge第二优先级

### Code

```c++

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
```

