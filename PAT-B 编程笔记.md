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

### 1040 有几个PAT
字符串 APPAPT 中包含了两个单词 PAT，其中第一个 PAT 是第 2 位(P)，第 4 位(A)，第 6 位(T)；第二个 PAT 是第 3 位(P)，第 4 位(A)，第 6 位(T)。

现给定字符串，问一共可以形成多少个 PAT？    

输入格式：    
输入只有一行，包含一个字符串，长度不超过10   
​5   
​​ ，只包含 P、A、T 三种字母。   

输出格式：   
在一行中输出给定字符串中包含多少个 PAT。由于结果可能比较大，只输出对 1000000007 取余数的结果。   

输入样例：   
APPAPT   
输出样例：   
2   
```C++
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    cin >> s;
    int len = s.length(), result = 0, countp = 0, countt = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == 'T')
            countt++;
    }//为什么先计算T的数量？
    for (int i = 0; i < len; i++) {
        if (s[i] == 'P') countp++;
        if (s[i] == 'T') countt--;
        if (s[i] == 'A') result = (result + (countp * countt) % 1000000007) % 1000000007;
    }//感觉应该是根据T匹配P和A的数量
    cout << result;
    return 0;
}
```

### 1051 复数乘法
复数可以写成 (A+Bi) 的常规形式，其中 A 是实部，B 是虚部，i 是虚数单位，满足 i
​2
​​ =−1；也可以写成极坐标下的指数形式 (R×e
​(Pi)
​​ )，其中 R 是复数模，P 是辐角，i 是虚数单位，其等价于三角形式 (R(cos(P)+isin(P))。

现给定两个复数的 R 和 P，要求输出两数乘积的常规形式。

输入格式：
输入在一行中依次给出两个复数的 R
​1
​​ , P
​1
​​ , R
​2
​​ , P
​2
​​ ，数字间以空格分隔。

输出格式：   
在一行中按照 A+Bi 的格式输出两数乘积的常规形式，实部和虚部均保留 2 位小数。注意：如果 B 是负数，则应该写成 A-|B|i 的形式。   

输入样例：       
2.3 3.5 5.2 0.4   
输出样例：   
-8.68-8.23i   
```C++
//我的代码 有一个测试用例不通过
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	float r1,p1,r2,p2;
	cin >> r1 >> p1 >> r2 >> p2;
	float a,b,c,d;
	a = r1 * cos(p1);
	b = r1 * sin(p1);
	c = r2 * cos(p2);
	d = r2 * sin(p2);
	float rp,ip;
	rp = a * c - b * d;
	ip = b * c + a * d;
	printf("%.2f%s%.2fi",rp,ip>0?"+":"-",abs(ip));
	return 0;
}
```
```C++
//可以通过所有测试用例的代码 AB应该分别代表实部和虚部，不明白为什么要这样处理AB
#include <iostream>
#include <cmath>
using namespace std;
int main() {
    double r1, p1, r2, p2, A, B;
    cin >> r1 >> p1 >> r2 >> p2;
    A = r1 * r2 * cos(p1) * cos(p2) - r1 * r2 * sin(p1) * sin(p2);
    B = r1 * r2 * cos(p1) * sin(p2) + r1 * r2 * sin(p1) * cos(p2);
    if (A + 0.005 >= 0 && A < 0)
        printf("0.00");
    else
        printf("%.2f", A);
    if(B >= 0)
        printf("+%.2fi", B);
    else if (B + 0.005 >= 0 && B < 0)
        printf("+0.00i");
    else
        printf("%.2fi", B);
    return 0;
}
```

### 1052 卖个萌 (20 分)
萌萌哒表情符号通常由“手”、“眼”、“口”三个主要部分组成。简单起见，我们假设一个表情符号是按下列格式输出的：     

[左手]([左眼][口][右眼])[右手]    
现给出可选用的符号集合，请你按用户的要求输出表情。    

输入格式：   
输入首先在前三行顺序对应给出手、眼、口的可选符号集。每个符号括在一对方括号 []内。题目保证每个集合都至少有一个符号，并不超过 10 个符号；每个符号包含 1 到 4 个非空字符。    

之后一行给出一个正整数 K，为用户请求的个数。随后 K 行，每行给出一个用户的符号选择，顺序为左手、左眼、口、右眼、右手——这里只给出符号在相应集合中的序号（从 1 开始），数字间以空格分隔。    

输出格式：    
对每个用户请求，在一行中输出生成的表情。若用户选择的序号不存在，则输出 Are you kidding me? @\/@。    

输入样例：   
```
[╮][╭][o][~\][/~]  [<][>]   
 [╯][╰][^][-][=][>][<][@][⊙]   
[Д][▽][_][ε][^]  ...   
4    
1 1 2 2 2    
6 8 1 5 5   
3 3 4 3 3   
2 10 3 9 3  
```
输出样例：
```
╮(╯▽╰)╭
<(@Д=)/~
o(^ε^)o
Are you kidding me? @\/@
```
```C++
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
	vector<vector<string> > v;//以string动态数组为元素的动态数组
	for(int i = 0; i < 3; i++) {
		string s;
		getline(cin, s);
		vector<string> row;//row表示的是口 眼 手 三行 三个动态数组
		int j = 0, k = 0;
		while(j < s.length()) {
			if(s[j] == '[') {//k,j分别是需要得到的字符串的头标志和尾标志（就是[]）在字符串中的位置
				while(k++ < s.length()) {
					if(s[k] == ']') {
						row.push_back(s.substr(j+1, k-j-1));
						break;
					}
				}
			}
			j++;
		}
		v.push_back(row);
	}
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		int a, b, c, d, e;
		cin >> a >> b >> c >> d >> e;
		if(a > v[0].size() || b > v[1].size() || c > v[2].size() || d > v[1].size() || e > v[0].size() || a < 1 || b < 1 || c < 1 || d < 1 || e < 1) {
			cout << "Are you kidding me? @\\/@" << endl;
			continue;
		}
		cout << v[0][a-1] << "(" << v[1][b-1] << v[2][c-1] << v[1][d-1] << ")" << v[0][e-1] << endl;
	}
	return 0;
}
```

### 1059 C语言竞赛
C 语言竞赛是浙江大学计算机学院主持的一个欢乐的竞赛。既然竞赛主旨是为了好玩，颁奖规则也就制定得很滑稽：    

0、冠军将赢得一份“神秘大奖”（比如很巨大的一本学生研究论文集……）。    
1、排名为素数的学生将赢得最好的奖品 —— 小黄人玩偶！    
2、其他人将得到巧克力。    
给定比赛的最终排名以及一系列参赛者的 ID，你要给出这些参赛者应该获得的奖品。     
 
输入格式：    
输入第一行给出一个正整数 N（≤10 
​4
​​ ），是参赛者人数。随后 N 行给出最终排名，每行按排名顺序给出一位参赛者的 ID（4 位数字组成）。接下来给出一个正整数 K 以及 K 个需要查询的 ID。

输出格式：   
对每个要查询的 ID，在一行中输出 ID: 奖品，其中奖品或者是 Mystery Award（神秘大奖）、或者是 Minion（小黄人）、或者是 Chocolate（巧克力）。如果所查 ID 根本不在排名里，打印 Are you kidding?（耍我呢？）。如果该 ID 已经查过了（即奖品已经领过了），打印 ID: Checked（不能多吃多占）。

输入样例：  
```
6   
1111    
6666    
8888
1234
5555
0001
6
8888
0001
1111
2222
8888
2222
```
输出样例：
```
8888: Minion
0001: Chocolate
1111: Mystery Award
2222: Are you kidding?
8888: Checked
2222: Are you kidding?
```
```c++
//我的代码 总有一个测试用例不通过
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

bool isprime(int n)
{
	int flag = 1;
	for(int i = 2; i*i < n; i++)
	{
		flag = 1;
		if(n%i == 0)
		{
			flag = 0;
			break;
		}
	}
	if(flag == 1)
		return true;
	else
		return false;
}
int main()
{
	int n;
	cin >> n;
	int rank[10000] = {0};
	for(int i = 0; i < n; i++)
	{
		int t;
		cin >> t;
		rank[t] = i+1;
	}
	int m;
	cin >> m;
	vector<int> check(m);
	for(int i = 0; i < m; i++)
	{
		int id;
		cin >> id;
		if(rank[id] == 0)
			printf("%04d: Are you kidding?\n",id);
		else
		{
			if(find(check.begin(),check.end(),id) != check.end())
				printf("%04d: Checked\n",id);
			else
			{
				check.push_back(id);
				if(rank[id] == 1)
					printf("%04d: Mystery Award\n",id);
				else if(isprime(rank[id]))
					printf("%04d: Minion\n",id);
				else
					printf("%04d: Chocolate\n",id);
			}
		}
	}
	return 0;
}
```
```c++
#include <iostream>
#include <set>
#include <cmath>
using namespace std;
int ran[10000];
bool isprime(int a) {
    if(a <= 1) return false;
    int Sqrt = sqrt((double)a);
    for(int i = 2; i <= Sqrt; i++) {
        if(a % i == 0)
            return false;
    }
    return true;
}
int main() {
    int n, k;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int id;
        scanf("%d", &id);
        ran[id] = i + 1;
    }
    scanf("%d", &k);
    set<int> ss;//使用set集合来存储搜索过的id
    for(int i = 0; i < k; i++) {
        int id;
        scanf("%d", &id);
        printf("%04d: ", id);
        if(ran[id] == 0) {
            printf("Are you kidding?\n");
            continue;
        }
        if(ss.find(id) == ss.end()) {
            ss.insert(id);
        } else {
            printf("Checked\n");
            continue;
        }
        if(ran[id] == 1) {
            printf("Mystery Award\n");
        }else if(isprime(ran[id])) {
            printf("Minion\n");
        }else {
            printf("Chocolate\n");
        }
    }
    return 0;
}
```
### 1094 谷歌的招聘
本题要求你编程解决一个更通用的问题：从任一给定的长度为 L 的数字中，找出最早出现的 K 位连续数字所组成的素数。    

输入格式：    
输入在第一行给出 2 个正整数，分别是 L（不超过 1000 的正整数，为数字长度）和 K（小于 10 的正整数）。接下来一行给出一个长度为 L 的正整数 N。   

输出格式：
在一行中输出 N 中最早出现的 K 位连续数字所组成的素数。如果这样的素数不存在，则输出 404。注意，原始数字中的前导零也计算在位数之内。例如在 200236 中找 4 位素数，0023 算是解；但第一位 2 不能被当成 0002 输出，因为在原始数字中不存在这个 2 的前导零。    

输入样例 1：  
```
20 5    
23654987725541023819
```
输出样例 1： 
```
49877    
```

输入样例 2： 
```
10 3    
2468024680 
```
输出样例 2： 
`404`   

```c++
#include <iostream>
#include <string>
using namespace std;
bool isPrime(int n) {
    if (n == 0 || n == 1) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}
int main() {
    int l, k;
    string s;
    cin >> l >> k >> s;
    for (int i = 0; i <= l - k; i++) {
        string t = s.substr(i, k);//substr获取string的子串
        int num = stoi(t);//stoi直接将子串转化为整型
        if (isPrime(num)) {
            cout << t;
            return 0;
        }
    }
    cout << "404\n";
    return 0;
}
```
