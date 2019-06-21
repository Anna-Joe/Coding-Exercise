### 1003 我要通过！
得到“答案正确”的条件是：
1.字符串中必须仅仅含有PAT这三种字符，不可以包含其他字符
2.形如xPATx的字符串都可以获得答案正确，其中x是空字符串或者<u>仅由字母A组成的字符串</u>(A,AA,AAA...)。
3.如果aPbTc是正确的，那么aPbATca也是正确的，其中abc均是空串或者仅有字母A组成的字符串。

> 条件一好理解，主要是针对二三两点的理解。   
> 条件二就是在PAT前后加上等量的A，可以通过。   
> 条件三 思考过程如下：   
> > 如果<u>&nbsp;PAT&nbsp;</u>是正确的，那么 <u>&nbsp;PAAT&nbsp;</u> 是正确的,其中ac是空格。
> > 如果<u>APATA</u>是正确的，那么<u>APAATAA</u>是正确的。
> > 如果AAPATAA是正确的，那么AAPAATAAAA是正确的
> 可以得出只能有一个P和一个T，中间开头结尾可以加入A，但是加入A的数量必须满足 首A*中间A=尾A
```c++
关键代码
//m是字符和该字符出现次数的映射
m['A'] == 1 && m['A'] != 0 && m['T'] == 1  //只能有一个P和一个T并且必须有A
m.size() == 3 //m映射的大小为3，即只有PAT三种字符
t - p != 1 && p * (t - p - 1) == s.length() - t - 1 //首A*中间A=尾A
//p是'P'的位置，就是首A，t是'T'的位置，表示到'T'为止字符的个数，(t - p - 1)是中间A，
```



### 1005 继续（3n+1）猜想
当验证卡拉兹猜想（遇到偶数，除以2；遇到奇数，奇数的三倍加一除以二，最后会得到一）的时候，为了避免重复计算，可以给出一个关键数字。
例如 计算3的时候 需要计算3，5，8，4，2，1 在这整个数列中3是关键数字。
1005题的目的是找出数列中的关键数字，并且按降序输出。

**对每个输入的数字n进行验证，把验证过的数字对应的arr标记为1，然后对输入的数字从大到小排列，输出arr标记为0的数字**
> 也就是不在已验证之列的数字，不明白为什么输出这些数字，也许不在已验证之列就说明验证这个数字需要经过其他数字？



### 1007 素数对
找出小于N的素数中，相邻之差为2的素数对个数。

```c++
for(i = 5; i < n; i++)
{
    if(isprime(i-2) && isprime(i))count++;
}
//只需要判断相邻的奇数是否都是素数即可
```



### 1010 多项式求导
flag是输出标志，判断是否已经有过输出。
直接判断b（x的指数）可以将输出结果分为两类：Ⅰ零多项式 输出 0 0；Ⅱ 非零多项式 正常计算



### 1013  数素数
多次运行超时，最终确定是判断素数的算法，时间复杂度过高。
`用的 i <= n/2 判断，最好用i * i <= n判断。`



### 1014 福尔摩斯的暗号
#include<cctype> 有 isdigit()判断字符串是否数字，isalpha()判断是否是字母（包括大小写）



### 1015 德才论
N考生数 L最低录取分 H优先录取线
考号 德分 才分
Ⅰ 德分才分均高于H，按总分高到低排序
Ⅱ 德分高于H，才分不及，按总分
Ⅲ 德才分低于H，但德分不低于才分
Ⅳ 达到L
输出 M（录取的学生）以及所有录取考生的信息

**要点：1.结构体存储 2.cmp函数 先按总分排序，再按德分排序，最后按才分排序**
```c++
struct stu
{
    int id,ds,cs;
}

bool cmp(struct stu a,struct stu b)
{
    if((a.ds + a.cs) != (b.ds + b.cs))
    	return (a.ds+a.cs) > (b.ds + b.cs);
    else if(a.ds != b.ds)
    	return a.ds > b.ds;
    else 
        return a.id < b.id;    
}
```

### 1021 个位数统计
给定一个k位整数N = dk-1*10k-1 + … + d1*101 + d0 (0<=di<=9, i=0,…,k-1, dk-1>0)，请编写程序统计每种不同的个位数字出现的次数。例如：
给定N = 100311，则有2个0，3个1，和1个3。
**要点笔记：使用map<char,int>做结果的存储结构，map中能自动按照key值升序排序。**


### 1024 科学计数法
将一个形如“+1.23E-3”的数字写成完整的数字“0.00123”。   
解题思路：   
1.取E前面的数字，不包括符号的部分，即这个数num；   
2.取E后面的数字，包括符号，即10的指数，也就是这个数的小数点移动位数index；   
3.分E后指数大于零和小于零的情况，决定了小数点是向左移动还是向右移动；   
4.小数点向左移动，先输出“0.”，再按移动位数index-1次输出0，最后输出num中的数字（除去“.”）；   
小数点向右移动，先输出num的第一位，然后从num[2]开始循环输出（循环条件是不超过num的长度，移动位数小于index），使用count记录已输出的位数，如果count小于index：输出0，把剩余位数补齐；如果count大于index输出小数点，并输出剩下的num。   
**要点：s.substr(begin,end)取子串，stoi()字符串转整型**

```C++
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string scn,num;
    cin >> scn;
    int index,i = 0,count;
    while(scn[i] != 'E')i++;
    num = scn.substr(1,i-1);
    index = stoi(scn.substr(i+1));
    if(scn[0] == '-')cout << '-';
    if(index < 0)
    {
        cout << "0.";
        for(i = 0; i < abs(index) - 1; i++)
            cout << 0;
        for(i = 0; i < num.length(); i++)
            if(num[i] != '.')cout << num[i];
    }
    else
    {
        cout << num[0];
        for(i = 2, count = 0; i < num.length() && count < index; i++, count++)
            cout << num[i];
        if(i == num.length())
            for(int j = 0; j < index - count; j++)
                cout << 0;
        else
        {
            cout << '.';
            for(int j = i; j < num.length(); j++)
                cout << num[j];
        }
    }
    
    return 0;
}             
```

### 1025 反转链表
**algorithm头文件里的reverse函数可以直接调用，反转指定数组**
```C++
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int first, k, n, temp;
    cin >> first >> n >> k;
    int data[100005], next[100005], list[100005];
    for (int i = 0; i < n; i++) {//将先输入的地址做为data和next数组的下标
        cin >> temp;
        cin >> data[temp] >> next[temp];
    }
    int sum = 0;//不一定所有的输入的结点都是有用的，加个计数器
    while (first != -1) {
        list[sum++] = first;
        first = next[first];
    }
    for (int i = 0; i < (sum - sum % k); i += k)
        reverse(begin(list) + i, begin(list) + i + k);
    for (int i = 0; i < sum - 1; i++)
        printf("%05d %d %05d\n", list[i], data[list[i]], list[i + 1]);
    printf("%05d %d -1", list[sum - 1], data[list[sum - 1]]);
    return 0;
}

```

### 1029 旧键盘
**要点：string里包含find函数，可以直接搜索字符串，如果未找到则返回str.npos。cctype里包含toupper()大写字符串 tolower()小写字符串 函数**

### 1030 完美数列
给定一个正整数数列，和正整数 p，设这个数列中的最大值是 M，最小值是 m，如果 M≤mp，则称这个数列是完美数列。

现在给定参数 p 和一些正整数，请你从中选择尽可能多的数构成一个完美数列。

输入格式：
输入第一行给出两个正整数 N 和 p，其中 N（≤10
​5
​​ ）是输入的正整数的个数，p（≤10
​9
​​ ）是给定的参数。第二行给出 N 个正整数，每个数不超过 10
​9
​​ 。

输出格式：
在一行中输出最多可以选择多少个数可以用它们组成一个完美数列。

输入样例：
10 8
2 3 20 4 5 1 6 7 8 9
输出样例：
8
```C++
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int N,p,m,M,count;
	int n[100005];
	cin >> N >> p;
	for(int i = 0; i < N; i++)
		cin >> n[i];
	m = 0;
	M = N - 1;
	count = N;
	sort(n,n+N);
	while(count != 0)
	{
		if(n[M] > n[m] * p)
		{
			if(n[M - 1] <= n[m] * p)
            {
                M--;
                count --;
            }
            else if(n[M] <= n[m+1] * p)
            {
                m ++;
                count --;
            }
            else 
            {
                M --;
                m ++;
                count -= 2;
            }
		}
		else break;
	}
	cout << count;
	return 0;

}//有一个测试用例不通过
```

```C++
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	int N,i,j,x;
	long long p;
	vector<int> n;
	cin >> N >> p;

	for(i = 0;i < N; i++)
	{
		cin >> x;
		n.push_back(x);
	}

	sort(n.begin(),n.end());

	int result = 0,temp = 0;
	for(i = 0; i < N; i ++)
	{
		for(j = i + result; j < N; j++)
		{
			if(n[j] <= n[i] * p)
			{
				temp = j - i + 1;
				if(temp > result)
					result = temp;
			}
			else
				break;
		}
	}
	cout << result;

	return 0;
}
```

### 1032 旧键盘打字
**通过跳过不合条件的，直接输出字符串的方式**
```C++
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
	string badkey,content;
	getline(cin,badkey);
    getline(cin,content);//如果没有字符输出，要输出空行，getline能得到空格
	int i,j;
	
	for(i = 0; i < content.length(); i ++)
	{
		if(badkey.find(toupper(content[i])) != badkey.npos) continue;
		if(isupper(content[i]) && badkey.find('+') != badkey.npos) continue;
		cout << content[i];
	}
	
	return 0;
}
```

### 1034 有理数四则运算
本题要求编写程序，计算 2 个有理数的和、差、积、商。

输入格式：
输入在一行中按照 a1/b1 a2/b2 的格式给出两个分数形式的有理数，其中分子和分母全是整型范围内的整数，负号只可能出现在分子前，分母不为 0。

输出格式：
分别在 4 行中按照 有理数1 运算符 有理数2 = 结果 的格式顺序输出 2 个有理数的和、差、积、商。注意输出的每个有理数必须是该有理数的最简形式 k a/b，其中 k 是整数部分，a/b 是最简分数部分；若为负数，则须加括号；若除法分母为 0，则输出 Inf。题目保证正确的输出中没有超过整型范围的整数。

输入样例 1：   
2/3 -4/2    
输出样例 1：   
2/3 + (-2) = (-1 1/3)   
2/3 - (-2) = 2 2/3    
2/3 * (-2) = (-1 1/3)    
2/3 / (-2) = (-1/3)    

输入样例 2：    
5/3 0/6    
输出样例 2：    
1 2/3 + 0 = 1 2/3    
1 2/3 - 0 = 1 2/3    
1 2/3 * 0 = 0    
1 2/3 / 0 = Inf    
```C++
long long gcd(long long t1,long long t2)//求最大公约数
{
	return t2 == 0 ? t1 : gcd(t2, t1 % t2);
}
//对这个算法不太明白
```

```C++
void func(long long m, long long n)
{
	//第一步 确认分子分母中是否含零
	if(m * n == 0)
	{
		printf("%s", n == 0 ? "Inf" : "0");
		return ;
	}
	
	//第二步 确认化简分数的符号
	bool flag = ((m > 0 && n < 0) || (m < 0 && n > 0));
	printf("%s",flag ? "(-" : "");

	//第三步 约分-分子大于分母的情况（有整数部分）；没有整数部分；
	m = abs(m);
	n = abs(n);
	long long x = m / n;
	if( x != 0)printf("%lld",x);
	if(m % n == 0)
	{
		printf("%s",flag ? ")" : "");
		return ;
	}
	if(x != 0) printf(" ");
	m = m - x * n;
	long long t = gcd(m,n);
	m = m / t;
	n = n / t;
	printf("%lld/%lld%s",m,n,flag ? ")" : "");
}
```
