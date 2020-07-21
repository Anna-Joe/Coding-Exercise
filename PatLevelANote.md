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

