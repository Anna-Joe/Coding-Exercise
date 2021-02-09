
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