# LeetCodeNotes
## 1. Two Sum
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

**Example 1:**
```C++
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].
```

**Example 2:**
```C++
Input: nums = [3,2,4], target = 6
Output: [1,2]
```

**Example 3:**
```
Input: nums = [3,3], target = 6
Output: [0,1]
```

**Constraints:**
```C++
2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.
```

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?

### Explaning
给出一个序列和目标值，求这个序列中和为目标值的两个元素下标

### Thinking
- 解法一：暴力求解，两层循环 时间复杂度n^2   
- 解法二：空间换时间，使用map存储每个元素与target的差值


### Coding
```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> num_diff_target;
        vector<int> result;
        for(int i = 0; i < nums.size();++i)
        {
            int diff = target-nums[i];
            if(num_diff_target.find(diff) == num_diff_target.end())
            {
                num_diff_target[nums[i]] = i;
            }
            else
            {
                result.push_back(i);
                result.push_back(num_diff_target[diff]);
                break;
            }            
        }
    return result;
    }
};
```

### Reflection
- 代码在所有提交中的数据不是很好，时间和空间都占用比较大？还有什么其他的算法吗

## 2. Add Two Numbers
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Example 1:**
```c++
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.
```

**Example 2:**
```c++
Input: l1 = [0], l2 = [0]
Output: [0]
```

**Example 3:**
```c++
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
```

**Constraints:**
```c++
The number of nodes in each linked list is in the range [1, 100].
0 <= Node.val <= 9
It is guaranteed that the list represents a number that does not have leading zeros.
```

### Explaining
给出两个存储非负整数的非空链表，求这两个非负整数的和。链表存储整数的方式是从个位数到百位数（从低位到高位存储）

### Thinking
每个节点相加时存储进位，并在下一次加法时用上

### Coding
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {        
        ListNode* rs = new ListNode();
        ListNode* ptr = rs;
        while(l1 != nullptr || l2 != nullptr)
        {
            int val = ptr->val;
            if(l1 != nullptr)
            {
                val += l1->val;
                l1 = l1->next; 
            }
            if(l2 != nullptr)
            {
                val += l2->val;
                l2 = l2->next;
            }

            ptr->val = val%10;
            ListNode* next = new ListNode(val/10);
            ptr->next = next;
            
            if(l1 == nullptr && l2 == nullptr && ptr->next->val == 0)
            {
                delete ptr->next;
                ptr->next = nullptr;
            }
            ptr = ptr->next;
        }
        return rs;
    }
};
```
### Reflection
- 不能对结构体指针进行++操作，会报AdressSanitizer heap_buffer_overflow
- 不能直接对头节点操作，会“仅返回零值”，可能后台测试是从头节点当前位置开始遍历的（应修改为使用另一指针指向头节点）
- 当所有节点遍历完，需要删除临时保存的下一节点，否则会“输出额外的0”


## 3. Longest Substring Without Repeating Characters
Given a string `s`, find the length of the **longest substring** without repeating characters.

**Example 1:**
```
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
```

**Example 2:**
```
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

**Example 3:**
```
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

**Example 4:**
```
Input: s = ""
Output: 0
```

**Constraints:**
- `0 <= s.length <= 5 * 104`
- `s` consists of English letters, digits, symbols and spaces.

### Explaining
找到一个字符串中最长的无重复字母的子串。

### Thinking
暴力求解 从最长子串开始，遍历每个字串，如果子串中没有重复字母就结束循环
### Coding
```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.empty())
        {
            return 0;
        }
        string sub;
        sub = s[0];
        int len = 1;
        auto i = 1;
        while(i < s.size())
        {
            if(sub.find(s[i]) == string::npos)
            {
                sub += s[i];
                i++;
            }
            else
            {   
                if(sub.size() > len)
                {
                    len = sub.size();
                }
                i = s.find_first_of(s[i]);
                
                sub = s[++i];
                ++i;
            }
        }
        len = sub.size() > len? sub.size():len;
        return len;

    }
};
```
### Reflection
- 一直使用string自带的字符串搜索函数，试图改变sub子串的内容，遇到重复字符串，都从上一个相同字符的下一位开始重新取串，但是发现了许多不能满足的特殊用例
- - 使用的搜索函数有 find_first_of，find_last_of。其中熟悉了find_last_of函数，并不是返回最后一个匹配子串的位置，而是从尾部开始寻找第一个不匹配子串的位置
- 最后参考算法指导手册，写出下列移动窗口的逻辑（比自己想的要简单多了）

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.empty())
        {
            return 0;
        }
        string sub;
        sub = s[0];
        int len = 1;
        int i = 0;
        int j = 1;
        //按移动窗口的逻辑
        //先移动窗口的右边 只要没有重复就一直右移，一旦有重复就左移
        while(i < s.size() && j < s.size())
        {
            if(sub.find(s[j]) == string::npos)
            {
                sub += s[j];
                ++j;
            }
            else
            {
                len = sub.size() > len? sub.size():len;   
                ++i;
                sub = s.substr(i,j-i);
            }
        }
        len = sub.size() > len? sub.size():len;
        return len;

    }
};
```

## [4. Median of Two Sorted Arrays](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/)

Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively, return **the median** of the two sorted arrays.

The overall run time complexity should be `O(log (m+n))`.

**Example 1:**
```
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
```

**Example 2:**
```
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
```

**Example 3:**
```
Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000
```

**Example 4:**
```
Input: nums1 = [], nums2 = [1]
Output: 1.00000
```

**Example 5:**
```
Input: nums1 = [2], nums2 = []
Output: 2.00000
```

**Constraints:**

- `nums1.length == m`
- `nums2.length == n`
- `0 <= m <= 1000`
- `0 <= n <= 1000`
- `1 <= m + n <= 2000`
- `-106 <= nums1[i], nums2[i] <= 106

### Thinking
输出两个已排序数组的中位数，中位数就是奇数个元素的最中间那个，或者偶数个元素中间两个数的平均数，如果只有一个数，那么这个数本身就是中位数。
首先将两个数组合并为一个新数组，判断新数组的size是奇数还是偶数，如果是奇数就取首尾索引均值的那个数，如果是偶数就取首尾相加除二，和首尾相加除二加一。

### Code
```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> sorted_nums;
        int i = 0;
        int j = 0;
        while(i < nums1.size() && j< nums2.size())
        {
            if(nums1[i] < nums2[j])
            {
                sorted_nums.push_back(nums1[i]);
                i++;
            }
            else
            {
                sorted_nums.push_back(nums2[j]);
                j++;  
            }            
        }

        while(i < nums1.size())
        {
            sorted_nums.push_back(nums1[i]);
            i++;
        }

        while(j < nums2.size())
        {
            sorted_nums.push_back(nums2[j]);
            j++;    
        }

        int count = sorted_nums.size();
        if(count % 2 == 0)
        {
            int end = count-1;
            int begin = 0;
            int i1 = (end+begin)/2;
            int i2 = i1+1;
            double rs = (sorted_nums[i1] + sorted_nums[i2])/2.0;
            return rs;
        }
        else
        {
            int end = count-1;
            int begin = 0;
            int i = (end+begin)/2;
            double rs = sorted_nums[i];
            return rs;
        }

    }
};
```
- 根据题目所给的时间复杂度的要求 上述算法虽然能通过但其实是不合格的
- 尝试使用下列二分法搜索 但是未能通过 理由是无法判断第二个数组的中线位置
```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        //固定搜索两个数组里面更小的那个
        if(nums2.size() < nums1.size())
        {
            return findMedianSortedArrays(nums2,nums1);
        }

        int count = nums1.size()+nums2.size();
        //定义两个数组的中线
        //通过二分搜索 确定中线的位置
        int l = 0,h = nums1.size()-1;
        int ma = l + (h-l)/2;
        int mb = (count-1)>>1 - ma;
        while(l <= h)
        {
            //if(nums1[ma-1] <= nums2[mb] && nums1[mb-1] < nums2[ma] )
            if(ma > 0 && nums1[ma-1] > nums2[mb])//左移
            {
                h = ma-1;               
            }
            else if(ma < nums1.size() && nums2[mb-1] > nums1[ma])//右移
            {
                l = ma+1;
            }
            else
            {
                break;
            }
            ma = (l+h)/2;
            mb = (count-1)>>1 - ma;
        }
        
        int mr = 0;
        int ml = 0;
        if(ma ==0 )
        {
            ml = nums2[mb-1];
        }
        else if(mb ==0 )
        {
            ml = nums1[ma-1];
        }
        else 
        {
            ml = nums1[ma-1] > nums2[mb-1] ? nums1[ma-1]:nums2[mb-1];
        }

        

        if(count%2 == 1)
        {
            return ml;
        }

        if(ma == nums1.size()-1)
        {
            mr = nums2[mb];
        }
        else if(mb == nums2.size()-1)
        {
            mr = nums1[ma];
        }
        else 
        {
            mr = nums1[ma] < nums2[mb] ? nums1[ma]:nums2[mb];
        }
        return (mr+ml)/2.0;
    }
};
```

## [5. Longest Palindromic Substring](https://leetcode-cn.com/problems/longest-palindromic-substring/)

Given a string `s`, return *the longest palindromic substring* in `s`.

**Example 1:**

```
Input: s = "babad"
Output: "bab"
Note: "aba" is also a valid answer.
```

**Example 2:**

```
Input: s = "cbbd"
Output: "bb"
```

**Example 3:**

```
Input: s = "a"
Output: "a"
```

**Example 4:**

```
Input: s = "ac"
Output: "a"
```

**Constraints:**

- `1 <= s.length <= 1000`
- `s` consist of only digits and English letters (lower-case and/or upper-case),

### Thinking

返回最长的回文子串？

一个子串的反向等于子串本身

一个字符是回文串，两个相同字符是回文串，三个字符需要首尾相同

所以从简单的问题想起就是动态规划的思想 ，n个字符判断方法就是 首尾相同并且中间的字符是回文串
- 中心扩散法
```c++
class Solution {
public:
    string longestPalindrome(string s) {
        int len = 1;
        string rs = s.substr(0,1);
        for(int i = 0; i < s.size(); i++)
        {
            string sub1,sub2;           
            sub1 = palindrome(s,i,i+1);                
            sub2 = palindrome(s,i,i);

            if(sub1.size() > sub2.size() && s[i] == s[i+1])
            {
                if(len < sub1.size())
                {
                    len = sub1.size();
                    rs = sub1;
                }
            }
            else
            {
                if(len < sub2.size())
                {
                    len = sub2.size();
                    rs = sub2;
                }
            } 
        }
        return rs;
    }

    string palindrome(string s,int left,int right)
    {
        while(left >= 0 && right < s.size())
        {
            if(s[left] == s[right])
            {
                left--;
                right++;
            }
            else
            {
                break;
            }
        }
        return s.substr(left+1,right-left-1);
    }
    
};
```
- 动态规划法
```c++
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        
        if(s.empty())
            return 0;
        int len = 1;
        string rs = s.substr(0,1);
        //动态规划其实就是记录子串左右端点的过程
        vector<vector<bool>> dp(n,vector<bool>(n,false));
        for(int i = n-1;i >= 0;i--)
        {
            for(int j = i;j < n;j++)
            {
                //所有单个字母都是回文
                if(i == j)
                {
                    dp[i][j] = true;
                }
                else if(j == i+1)
                {
                    dp[i][j] = (s[i] == s[j]);
                }
                else
                {
                    dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1];
                }
                if(dp[i][j])
                {
                    if(j-i+1 > len)
                    {
                        len = j-i+1;
                        rs = s.substr(i,j-i+1);
                    }
                }
                
            }
        }
        return rs;    
    }  
};
```

## [6. ZigZag Conversion](https://leetcode-cn.com/problems/zigzag-conversion/)

The string `"PAYPALISHIRING"` is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

```
P   A   H   N
A P L S I I G
Y   I   R
```

And then read line by line: `"PAHNAPLSIIGYIR"`

Write the code that will take a string and make this conversion given a number of rows:

```
string convert(string s, int numRows);
```

**Example 1:**

```
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
```

**Example 2:**

```
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
```

**Example 3:**

```
Input: s = "A", numRows = 1
Output: "A"
```

**Constraints:**

- `1 <= s.length <= 1000`
- `s` consists of English letters (lower-case and upper-case), `','` and `'.'`.
- `1 <= numRows <= 1000`

### Thinking

弯曲字符串。给出一个字符串从列开始遍历的序列和总行数，要求输出从行开始遍历的序列。

找规律：

### Coding

```c++
class Solution {
public:
    string convert(string s, int numRows) {
        //结果为偶数 按余数正序保存
        //结果为奇数 按余数倒序保存
        if(s.empty() || numRows < 1)return 0;
        if(numRows == 1)return s;
        vector<string> tmp(numRows);

        for(int i = 0; i < s.size();i++)
        {
            int ans = i/(numRows-1);
            int res = i%(numRows-1);
            if(ans % 2 == 0)
            {
                tmp[res].push_back(s[i]);
            }
            else
            {
                tmp[numRows-res-1].push_back(s[i]);
            }
        }

        string rs;
        for(auto str:tmp)
        {
            rs += str;
        }
        return rs;
    }
};
```

## [7. Reverse Integer](https://leetcode-cn.com/problems/reverse-integer/)

Given a signed 32-bit integer `x`, return `x` *with its digits reversed*. If reversing `x` causes the value to go outside the signed 32-bit integer range  
[2^{31},2^{31}-1] , then return `0`.

**Assume the environment does not allow you to store 64-bit integers (signed or unsigned).**



**Example 1:**

```
Input: x = 123
Output: 321
```

**Example 2:**

```
Input: x = -123
Output: -321
```

**Example 3:**

```
Input: x = 120
Output: 21
```

**Example 4:**

```
Input: x = 0
Output: 0
```

**Constraints:**

- `-2^31 <= x <= 2^31 - 1`

### Thinking

给出三十二位的符号数，反转这个数字的位数

### Coding

```c++
class Solution {
public:
    int reverse(int x) {
        string str = to_string(abs(x));
        std::reverse(str.begin(),str.end());
        long num = stol(str);
        if(num < -pow(2,31) || num > pow(2,31)-1)
        {
            return 0;
        }
        else
        {
            if(x < 0)
            {
                return -num;
            }
            else
            {
                return num;
            }
        }
    }
};
```

## [9. Palindrome Number](https://leetcode-cn.com/problems/palindrome-number/)

Given an integer `x`, return `true` if `x` is palindrome integer.

An integer is a **palindrome** when it reads the same backward as forward. For example, `121` is palindrome while `123` is not.

**Example 1:**

```
Input: x = 121
Output: true
```

**Example 2:**

```
Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
```

**Example 3:**

```
Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
```

**Example 4:**

```
Input: x = -101
Output: false
```

**Constraints:**

- `-231 <= x <= 231 - 1`

### Thinking

判断反转前后的字符串是否相等

### Coding

- 使用string

```c++
class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        string t =s;
        reverse(s.begin(),s.end());
        return s == t;
    }
};
```

- 不使用string

```c++
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0)
            return false;
        long rem = 0, y = 0;
        int quo = x;

        //循环取余数的办法倒置这个数 再判断是否与原数相等
        while(quo != 0)
        {
            rem = quo%10;//个位数
            y = y*10+rem;
            quo = quo/10;
        }
        return y==x;
    }
};
```

## [10. Regular Expression Matching](https://leetcode-cn.com/problems/regular-expression-matching/)

Given an input string (`s`) and a pattern (`p`), implement regular expression matching with support for `'.'` and `'*'` where:` `

- `'.'` Matches any single character.
- `'*'` Matches zero or more of the preceding element.

The matching should cover the **entire** input string (not partial).

**Example 1:**

```
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
```

**Example 2:**

```
Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
```

**Example 3:**

```
Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
```

**Example 4:**

```
Input: s = "aab", p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
```

**Example 5:**

```
Input: s = "mississippi", p = "mis*is*p*."
Output: false
```

**Constraints:**

- `0 <= s.length <= 20`
- `0 <= p.length <= 30`
- `s` contains only lowercase English letters.
- `p` contains only lowercase English letters, `'.'`, and `'*'`.
- It is guaranteed for each appearance of the character `'*'`, there will be a previous valid character to match.

### Thinking

正则表达式匹配，给出字符串s和正则表达式p，输出p是否是满足s的表达式。其中.表示任何字符，*表示前一个字符的重复

### Coding
```c++
class Solution{
public:
    bool isMatch(string s,string p)
    {
        if(p.empty())return s.empty();//处理空值的情况
        
        auto first_match = !s.empty() && (s[0] == p[0] || p[0] == '.');//判断第一个字符是否匹配
        
        //如果P串第一个字符是非确定项
        if(p.length() >= 2 && p[1] == '*')
        {
            //s串是否与之后的p匹配（也就是认为p的第一个字符没有） 或者 s串的第一个字符已经匹配上 判断s串后半段是否与p匹配
            return isMatch(s,p.substr(2)) || (first_match && isMatch(s.substr(1),p));
        }
        //如果p串第一个字符是确定项
        else
        {   
            //直接判断第一字符和之后的串是否匹配
            return first_match && isMatch(s.substr(1),p.substr(1));
        }
    }
}
```
## [11. Container With Most Water](https://leetcode-cn.com/problems/container-with-most-water/)

Given `n` non-negative integers `a1, a2, ..., an` , where each represents a point at coordinate `(i, ai)`. `n` vertical lines are drawn such that the two endpoints of the line `i` is at `(i, ai)` and `(i, 0)`. Find two lines, which, together with the x-axis forms a container, such that the container contains the most water.

**Notice** that you may not slant the container.

![](https://aliyun-lc-upload.oss-cn-hangzhou.aliyuncs.com/aliyun-lc-upload/uploads/2018/07/25/question_11.jpg)

**Example 1:**

```
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
```

**Example 2:**

```
Input: height = [1,1]
Output: 1
```

**Example 3:**

```
Input: height = [4,3,2,1,4]
Output: 16
```

**Example 4:**

```
Input: height = [1,2,1]
Output: 2
```

**Constraints:**

- `n == height.length`
- `2 <= n <= 105`
- `0 <= height[i] <= 104`

### Thinking

已知每个柱子的高度，求两个柱子围成的最大面积。

求序列之间的序号差（底）与当前元素（高）的乘积（面积）最大值

### Coding
- 局限（很多测试用例不能通过）
```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_h = height[0];
        int max_h_index = 0;
        //找出最高的柱子 和 他的下标
        for(int i = 1;i < height.size();++i)
        {
            if(height[i] > max_h)
            {
                max_h = height[i];
                max_h_index=i;
            }
        }

        int max_a = 0;
        //找出到最高的柱子 距离最长的点
        for(int i = 0 ; i < height.size();++i)
        {
            if(i == max_h_index)
                continue;
            int h = height[i];
            int s = abs(i-max_h_index);
            if(h*s > max_a)
            {
                max_a = h*s;
            }
            
        }
        return max_a;
    }
};
```
- o(n^2)(最长的用例超时）

- 双指针 可以通过 但是时间和空间数据不是很好
```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        //双指针
        int i = 0;
        int j = height.size()-1;
        int max_a = 0;
        while(i < j)
        {
            int s = j-i;
            int h = height[i]<height[j]?height[i]:height[j];
            if(s*h > max_a)
            {
                max_a = s*h;
            }
            if(height[i]<height[j])
            {
                ++i;
            }
            else
            {
                --j;
            }
        }

    return max_a;
    }
};
```
## [12. Integer to Roman](https://leetcode-cn.com/problems/integer-to-roman/)

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D` and `M`.

```
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

For example, `2` is written as `II` in Roman numeral, just two one's added together. `12` is written as `XII`, which is simply `X + II`. The number `27` is written as `XXVII`, which is `XX + V + II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not `IIII`. Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as `IX`. There are six instances where subtraction is used:

- `I` can be placed before `V` (5) and `X` (10) to make 4 and 9. 
- `X` can be placed before `L` (50) and `C` (100) to make 40 and 90. 
- `C` can be placed before `D` (500) and `M` (1000) to make 400 and 900.

Given an integer, convert it to a roman numeral.



**Example 1:**

```
Input: num = 3
Output: "III"
```

**Example 2:**

```
Input: num = 4
Output: "IV"
```

**Example 3:**

```
Input: num = 9
Output: "IX"
```

**Example 4:**

```
Input: num = 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.
```

**Example 5:**

```
Input: num = 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
```

**Constraints:**

- `1 <= num <= 3999`

### Thinking

使用两个数组分别存放罗马数字和对应的阿拉伯数字。



### Coding

```c++
class Solution {
public:
    string intToRoman(int num) {

        int values[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        string roman[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};

        string str;
        for(int i = 0;i < 13;i++)
        {
            while(num >= values[i])
            {
                num -= values[i];
                str += roman[i];
            }
        }
        return str;
    }
};
```
## [13. Roman to Integer](https://leetcode-cn.com/problems/roman-to-integer/)

难度简单1397收藏分享切换为中文接收动态反馈

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D` and `M`.

```
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

For example, `2` is written as `II` in Roman numeral, just two one's added together. `12` is written as `XII`, which is simply `X + II`. The number `27` is written as `XXVII`, which is `XX + V + II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not `IIII`. Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as `IX`. There are six instances where subtraction is used:

- `I` can be placed before `V` (5) and `X` (10) to make 4 and 9. 
- `X` can be placed before `L` (50) and `C` (100) to make 40 and 90. 
- `C` can be placed before `D` (500) and `M` (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer.

**Example 1:**

```
Input: s = "III"
Output: 3
```

**Example 2:**

```
Input: s = "IV"
Output: 4
```

**Example 3:**

```
Input: s = "IX"
Output: 9
```

**Example 4:**

```
Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
```

**Example 5:**

```
Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
```

 

**Constraints:**

- `1 <= s.length <= 15`
- `s` contains only the characters `('I', 'V', 'X', 'L', 'C', 'D', 'M')`.
- It is **guaranteed** that `s` is a valid roman numeral in the range `[1, 3999]`.

### Thinking

上一题倒置过来

### Coding

```c++
class Solution {
public:
    int romanToInt(string s) {
        int values[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        string roman[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};

        int num = 0;
        for(int i = 0;i < 13;i++)
        {
            int len = roman[i].size();
            while(s.substr(0,len) == roman[i])
            {
                s = s.substr(len);
                num += values[i];
            }
    
        }
        return num;

    }
};
```

## [14. Longest Common Prefix](https://leetcode-cn.com/problems/longest-common-prefix/)

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string `""`.

 

**Example 1:**

```
Input: strs = ["flower","flow","flight"]
Output: "fl"
```

**Example 2:**

```
Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
```

**Constraints:**

- `1 <= strs.length <= 200`
- `0 <= strs[i].length <= 200`
- `strs[i]` consists of only lower-case English letters.

### Thinking

获取字符串数组中，最长的前缀，如果没有则返回空

从第一个字符开始，遍历数组里每个字符串，如果相同则遍历第二个字符串，遇到不同的则退出循环

### Coding

```c++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty())
            return "";
        if(strs.size() == 1)
            return strs[0];

        string pre = strs[0].substr(0,1);
        int min_len = 200;
        for(auto str:strs)
        {
            if(str.substr(0,1) != pre)
            {
                return "";
            }
            min_len = min_len < str.size()?min_len:str.size();
        }
        
        
        for(int pos = 1; pos < min_len; pos++)
        {
            string tmp = strs[0].substr(pos,1);
            int match = true;
            for(int i = 1; i < strs.size(); i++)
            {
                if(tmp != strs[i].substr(pos,1))
                {
                    match = false;
                    break;
                }
            }
            if(match)
            {
                pre+=tmp;
            }
            else
            {
                break;
            }
        }

    return pre;
    }
};
```

### [15. 3Sum](https://leetcode-cn.com/problems/3sum/)

Given an integer array nums, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must not contain duplicate triplets.

**Example 1:**

```
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
```

**Example 2:**

```
Input: nums = []
Output: []
```

**Example 3:**

```
Input: nums = [0]
Output: []
```

**Constraints:**

- `0 <= nums.length <= 3000`
- `-105 <= nums[i] <= 105`

### Thinking

返回一个序列中所有和为0的三元组

和为0的三元组 的 特点：

1.含有一个0，另外两个数必须互为相反数（符号相反绝对值相等）

2.不含有0，其中两个数的和 与 另一个数互为相反数

### Coding

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> vec_rs;
        if(nums.size() < 3)
            return vec_rs;
        
        vector<int> num_in;
        for(int i = 0; i < nums.size();i++)
        {
            for(int j = i+1; j < nums.size();j++)
            {
                for(int k = j+1; k < nums.size();++k)
                {
                    if(nums[i] +nums[j] + nums[k] == 0 )
                    {
                        int count = 0;
                        if(find(num_in.begin(),num_in.end(),nums[i]) != num_in.end())
                            count++;
                        if(find(num_in.begin(),num_in.end(),nums[j]) != num_in.end())
                            count++;
                        if(find(num_in.begin(),num_in.end(),nums[k]) != num_in.end())
                            count++;

                        if(count <= 1)
                        {
                            num_in.push_back(nums[i]);
                            num_in.push_back(nums[j]);
                            num_in.push_back(nums[k]);
                            vec_rs.push_back({nums[i],nums[j],nums[k]});
                        }
                    }
                              
                }
            }
        }

        return vec_rs;
    }
};
```
- 正确解法
```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> vec_rs;
        if(nums.size() < 3)
            return vec_rs;
        
        sort(nums.begin(),nums.end());
        int n = nums.size();
        //固定一个数字的双指针法 从求三个数的和转化为求两个数的和
        for(int i = 0; i < nums.size();i++)
        {
            //当第一个数大于0时，后面的数字已经不用计算
            if(nums[i] > 0)
                break;

            if(i > 0 && nums[i] == nums[i-1])
                continue;

            int l = i+1;
            int h = nums.size()-1;
            while( l < h)
            {
                if(nums[l] + nums[h] > -nums[i])
                {
                    h--;
                }
                else if(nums[l] + nums[h] < -nums[i])
                {
                    l++;
                }
                else if(nums[l] + nums[h] == -nums[i])
                {
                    vec_rs.push_back({ nums[i],nums[l],nums[h] });
		    while (l < h && nums[l + 1] == nums[l])
		    {
			l++;				
		    }
		    while (l < h  && nums[h - 1] == nums[h])
		    {
			h--;
		    }
		    h--;
		    l++;
                }
            }            
        }

        return vec_rs;
    }
};
```
## [16. 3Sum Closest](https://leetcode-cn.com/problems/3sum-closest/)

Given an array `nums` of *n* integers and an integer `target`, find three integers in `nums` such that the sum is closest to `target`. Return the sum of the three integers. You may assume that each input would have exactly one solution.

**Example 1:**

```
Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
```

**Constraints:**

- `3 <= nums.length <= 10^3`
- `-10^3 <= nums[i] <= 10^3`
- `-10^4 <= target <= 10^4`

### Thinking

找到一个序列中，三个数之和与目标值最接近的三个数

查找一个序列中所有组合，计算所有组合的和与目标值的差值，选择差值最小的输出

### Coding

- 暴力解法

```c++
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if(nums.size() == 3)
        {
            return nums[0]+nums[1]+nums[2];
        }
        sort(nums.begin(),nums.end());
        int n = nums.size(); 
        int min = 10000;
        for (int i = 0; i < n; ++i)
		{
			if (i > 0 && nums[i] == nums[i - 1])
				continue;
			for (int j = i + 1; j < n; ++j)
			{
				//if (j > 1 && nums[j] == nums[j - 1])
					//continue;
				for (int k = j + 1; k < n; ++k)
				{
					//if (k > 2 && nums[k] == nums[k - 1])
						//continue;
					int tmp = nums[i] + nums[j] + nums[k];
					if (abs(tmp - target) <= abs(min - target))
					{
						min = tmp;
					}
				}
			}

		}
        return min;

    }
};
```

- 双指针

```c++
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if(nums.size() == 3)
        {
            return nums[0]+nums[1]+nums[2];
        }
        sort(nums.begin(),nums.end());
        int n = nums.size(); 
        int min = 10000;
        for(int i = 0; i < n; ++i)
        {
            if(i > 0 && nums[i] == nums[i-1])
                continue;
            int l = i+1;
            int h = n-1;
            while(l < h)
            {
                int tmp= nums[i] + nums[l] + nums[h];
                if(abs(tmp - target) < abs(min-target))
                {
                    min = tmp;
                }
                if(tmp < target)l++;
                else if(tmp > target)h--;
                else return min;
                
            }
        }
        return min;

    }
};
```

## [17. Letter Combinations of a Phone Number](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/)

Given a string containing digits from `2-9` inclusive, return all possible letter combinations that the number could represent. Return the answer in **any order**.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.


<img src="https://assets.leetcode-cn.com/aliyun-lc-upload/original_images/17_telephone_keypad.png" alt="img10" style="zoom:33%;" />



**Example 1:**

```
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
```

**Example 2:**

```
Input: digits = ""
Output: []
```

**Example 3:**

```
Input: digits = "2"
Output: ["a","b","c"]
```
**Constraints:**

- `0 <= digits.length <= 4`
- `digits[i]` is a digit in the range `['2', '9']`.

### Thinking

获取输入数字代表的所有字母组合

从第一个数字的第一个字母开始跟后面每个数字分别匹配

### Coding

```c++
class Solution {
public:
    //使用映射存储数字和数字代表的字符
    map<char,string> mp = {{'2',"abc"},{'3',"def"},{'4',"ghi"},{'5',"jkl"},{'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"}};
    vector<string> rs;
    string cur;//组合串 每个字母串其中一个字符的组合  
    //一直存储上一个数字代表字母串的字符，直到digit的内容被取完（所有数字都被遍历）才将这个组合串推进结果列表
    //深度优先遍历就是实现了 构思的时候想实现的从第一个数字的第一个字母开始跟后面每个数字分别匹配
    vector<string> letterCombinations(string digits) {
        if(!digits.size())
            return rs;
        
        DFS(digits);
        return rs;
    }

    void DFS(string digit)
    {
        if(!digit.size())//结束时 存入结果串
            return rs.push_back(cur);
        else
        {
            char num = digit[0];
            string letter = mp[num];//取到字符
            for(int i = 0; i < letter.size();++i)
            {
                cur.push_back(letter[i]);
                DFS(digit.substr(1));
                cur.pop_back();
            }
        }
    }
};
```

## [18. 4Sum](https://leetcode-cn.com/problems/4sum/)

Given an array `nums` of `n` integers, return *an array of all the **unique** quadruplets* `[nums[a], nums[b], nums[c], nums[d]]` such that:

- `0 <= a, b, c, d < n`
- `a`, `b`, `c`, and `d` are **distinct**.
- `nums[a] + nums[b] + nums[c] + nums[d] == target`

You may return the answer in **any order**.

**Example 1:**

```
Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
```

**Example 2:**

```
Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]
```

**Constraints:**

- `1 <= nums.length <= 200`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`

### Thinking

返回和满足目标值的四个数字，数字不可重复

求任意两个数的和，然后用目标值减去这两个数，差值不存在的保存在映射中，差值已存在的存进列表里

### Coding

- 行不通 后面和与前面和相同的数字组合会覆盖掉

```c++
class Solution 
{
    public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) 
    {
        vector<vector<int>> rs; 
        int n = nums.size(); 
        if(n < 4)
            return rs;
        if(n == 4 && nums[0]+nums[1]+nums[2]+nums[3] != target)
            return rs;
        string index;
        map<int,pair<int,int>> mp;
        for(int i = 0;i < n;++i)
        {
            for(int j = i+1;j<n;++j)
            {
                int sum = nums[i]+nums[j];
                int dif = target - sum;
                if(mp.find(dif) != mp.end())
                {
                    auto f = mp.find(dif);
                    pair<int,int> p = f->second;
                    int k = p.first;
                    int l = p.second;

                    vector<int> tmp;
                    tmp.push_back(i);
                    tmp.push_back(j);
                    tmp.push_back(k);
                    tmp.push_back(l);
                    sort(tmp.begin(),tmp.end());
                    string str = to_string(tmp[0])+to_string(tmp[1])+to_string(tmp[2])+to_string(tmp[3]);

                    if(k != i && k != j && l != i && l != j && index.find(str) == string::npos)
                    {
                        rs.push_back({nums[i],nums[j],nums[k],nums[l]});
                        index.append(str);
                    }
                        
                }
                else
                {
                    mp[sum] = pair<int,int>(i,j);
                }
            }
        }
        return rs;
    }
};
```

## [19. Remove Nth Node From End of List](https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/)

Given the `head` of a linked list, remove the `nth` node from the end of the list and return its head.


**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)

```
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
```

**Example 2:**

```
Input: head = [1], n = 1
Output: []
```

**Example 3:**

```
Input: head = [1,2], n = 1
Output: [1]
```

 

**Constraints:**

- The number of nodes in the list is `sz`.
- `1 <= sz <= 30`
- `0 <= Node.val <= 100`
- `1 <= n <= sz`

 ### Thinking

删除链表的倒数第N个节点

先取到这个节点的位置，然后从列表中找到节点 移动节点的前后节点

### Coding

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //删除链表的倒数第N个节点
        vector<ListNode*> vc_link;
        ListNode* p = head;
        while(p!=nullptr)
        {
            vc_link.push_back(p);
            p = p->next;
        }
        int del_i = vc_link.size()-n;
        
        if(del_i == 0)
        {
            ListNode* q = head;
            head = head->next;
            q->next = nullptr;
            delete q;
        }
        else
        {
            ListNode* q =  vc_link[del_i];
            vc_link[del_i-1]->next = q->next;
            q->next = nullptr;
            delete q;
        }

        return head;

    }
};
```
## [20. Valid Parentheses](https://leetcode-cn.com/problems/valid-parentheses/)

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.

 

**Example 1:**

```
Input: s = "()"
Output: true
```

**Example 2:**

```
Input: s = "()[]{}"
Output: true
```

**Example 3:**

```
Input: s = "(]"
Output: false
```

**Example 4:**

```
Input: s = "([)]"
Output: false
```

**Example 5:**

```
Input: s = "{[]}"
Output: true
```

 

**Constraints:**

- `1 <= s.length <= 104`
- `s` consists of parentheses only `'()[]{}'`.

### Thinking

使用堆栈

### Coding

```c++
class Solution {
public:
    bool isValid(string s) {
        stack<char> tk_ch;
        for(auto c:s)
        {
            if(c == '(')
            {
                tk_ch.push(c);
            }
            else if(c == ')')
            {
                if(tk_ch.empty())
                    return false;
                else if(tk_ch.top() == '(')
                    tk_ch.pop();
                else
                    return false;
            }
            else if(c == '{')
            {
                tk_ch.push(c);
            }
            else if(c == '}')
            {
                if(tk_ch.empty())
                    return false;
                else if(tk_ch.top() == '{')
                    tk_ch.pop();
                else
                    return false;
            }
            else if(c == '[')
            {
                tk_ch.push(c);
            }
            else if(c == ']' )
            {
                if(tk_ch.empty())
                    return false;
                if(tk_ch.top() == '[')
                    tk_ch.pop();
                else
                    return false;
            }
        }
        if(tk_ch.empty())
            return true;

        return false;

    }
};
```

```c++
class Solution {
public:
    bool isValid(string s) {
        stack<int> st;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') st.push(')');
            else if (s[i] == '{') st.push('}');
            else if (s[i] == '[') st.push(']');
            // 第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号 return false
            // 第二种情况：遍历字符串匹配的过程中，发现栈里没有我们要匹配的字符。所以return false
            else if (st.empty() || st.top() != s[i]) return false;
            else st.pop(); // st.top() 与 s[i]相等，栈弹出元素
        }
        // 第一种情况：此时我们已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以return false，否则就return true
        return st.empty();
    }
};
```


## [21. Merge Two Sorted Lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

Merge two sorted linked lists and return it as a **sorted** list. The list should be made by splicing together the nodes of the first two lists.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/03/merge_ex1.jpg)

```
Input: l1 = [1,2,4], l2 = [1,3,4]
Output: [1,1,2,3,4,4]
```

**Example 2:**

```
Input: l1 = [], l2 = []
Output: []
```

**Example 3:**

```
Input: l1 = [], l2 = [0]
Output: [0]
```

 

**Constraints:**

- The number of nodes in both lists is in the range `[0, 50]`.
- `-100 <= Node.val <= 100`
- Both `l1` and `l2` are sorted in **non-decreasing** order.

### Thinking

将两个已排序的链表合并

### Coding

- 借助第三个链表二路归并

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        //链表归并
        //比较链表元素值的大小 大的插入在后面 小的插入在前面
        if(l1 == nullptr)
            return l2;
        else if(l2 == nullptr)
            return l1;
        ListNode* p1 = l1;
        ListNode* p2 = l2;
        
        ListNode* l3 = new ListNode();
        ListNode* p3 = l3;

        while(p2 != nullptr && p1 != nullptr)
        {
            if(p2->val > p1->val)
            {
                p3->val = p1->val;
                p3->next = new ListNode();
                p3 = p3->next;
                p1 = p1->next;
            }
            else
            {
                p3->val = p2->val;
                p3->next = new ListNode();
                p3 = p3->next;
                p2 = p2->next;
            }
               
        }
        if(p2 != nullptr)
        {
            p3->val = p2->val;
            p3->next = p2->next;
        }
        if(p1 != nullptr)
        {
            p3->val = p1->val;
            p3->next = p1->next;
        }
        if(p3->next == nullptr && p3->val == 0)
        {
            p3 = nullptr;
        }
        return l3;
    }
};
```

- 递归算法

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1==NULL)
        return l2;
    if(l2==NULL)
        return l1;
    if(l1->val < l2->val){
        l1->next = mergeTwoLists(l1->next,l2);
        return l1;
    }else{
        l2->next = mergeTwoLists(l1,l2->next);
        return l2;
    }
    }
};
```

## [23. Merge k Sorted Lists](https://leetcode-cn.com/problems/merge-k-sorted-lists/)

You are given an array of `k` linked-lists `lists`, each linked-list is sorted in ascending order.

*Merge all the linked-lists into one sorted linked-list and return it.*

**Example 1:**

```
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
```

**Example 2:**

```
Input: lists = []
Output: []
```

**Example 3:**

```
Input: lists = [[]]
Output: []
```

**Constraints:**

- `k == lists.length`
- `0 <= k <= 10^4`
- `0 <= lists[i].length <= 500`
- `-10^4 <= lists[i][j] <= 10^4`
- `lists[i]` is sorted in **ascending order**.
- The sum of `lists[i].length` won't exceed `10^4`.

### Thinking

一层循环套用，两个链表归并的算法

### Coding

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0)return nullptr;
        ListNode* ls = lists[0];
        for(int i = 1;i < lists.size();++i)
        {
            ls = mergeTwoLists(ls, lists[i]);
        }
        return ls;
    }
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
    {
        if(l1==NULL)
            return l2;
        if(l2==NULL)
            return l1;
        if(l1->val < l2->val){
            l1->next = mergeTwoLists(l1->next,l2);
            return l1;
        }else{
            l2->next = mergeTwoLists(l1,l2->next);
            return l2;
        }
    }
};
```
## [24. Swap Nodes in Pairs](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)

Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/03/swap_ex1.jpg)

```
Input: head = [1,2,3,4]
Output: [2,1,4,3]
```

**Example 2:**

```
Input: head = []
Output: []
```

**Example 3:**

```
Input: head = [1]
Output: [1]
```

 

**Constraints:**

- The number of nodes in the list is in the range `[0, 100]`.
- `0 <= Node.val <= 100`

### Thinking

交换相邻的两个节点

### Coding

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        //第一步 整体化分解问题 可递归解决的问题 一定是重复一个操作的问题
        //把这个重复操作 分解为已操作的部分+重复的最小单元 这个已操作部分往往就是递归的入口
        //比如 链表交换问题的最小单元 就是三个节点，当前节点的前驱，当前节点，和当前节点的后继。
        //交换操作 是 使当前节点的后指针指向前驱，前驱节点的后指针指向当前节点的后继
        //其中当前节点的后继应该是已操作部分 也就是递归入口
        //终止条件 链表为空
        //返回值 返回已反转的链表
        //本级应该做什么 反转开头两个节点
        //链表和树是天生适合递归的结构
        if(head == nullptr || head->next == nullptr)
            return head;
        ListNode* next = head->next;
        head->next = swapPairs(next->next);
        next->next = head;
        return next;
    }
};
```


## [26. Remove Duplicates from Sorted Array](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/)

Given an integer array `nums` sorted in **non-decreasing order**, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that each unique element appears only **once**. The **relative order** of the elements should be kept the **same**.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the **first part** of the array `nums`. More formally, if there are `k` elements after removing the duplicates, then the first `k` elements of `nums` should hold the final result. It does not matter what you leave beyond the first `k` elements.

Return `k` *after placing the final result in the first* `k` *slots of* `nums`.

Do **not** allocate extra space for another array. You must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with O(1) extra memory.

**Custom Judge:**

The judge will test your solution with the following code:

```
int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
```

If all assertions pass, then your solution will be **accepted**.

 

**Example 1:**

```
Input: nums = [1,1,2]
Output: 2, nums = [1,2,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
```

**Example 2:**

```
Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
```

 

**Constraints:**

- `0 <= nums.length <= 3 * 104`
- `-100 <= nums[i] <= 100`
- `nums` is sorted in **non-decreasing** order.

### Thinking



### Coding

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        if(nums.size() == 1)return 1;
        int i = 0;
        int j = 1;
        while(j < nums.size())
        {
            if(nums[j] != nums[i])
            {
                nums[i+1] = nums[j];
                i++;                
            }
            j++;
        }
        return i+1;

    }
};
```

## [27. Remove Element](https://leetcode-cn.com/problems/remove-element/)

Given an integer array `nums` and an integer `val`, remove all occurrences of `val` in `nums` [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm). The relative order of the elements may be changed.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the **first part** of the array `nums`. More formally, if there are `k` elements after removing the duplicates, then the first `k` elements of `nums` should hold the final result. It does not matter what you leave beyond the first `k` elements.

Return `k` *after placing the final result in the first* `k` *slots of* `nums`.

Do **not** allocate extra space for another array. You must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with O(1) extra memory.

**Custom Judge:**

The judge will test your solution with the following code:

```
int[] nums = [...]; // Input array
int val = ...; // Value to remove
int[] expectedNums = [...]; // The expected answer with correct length.
                            // It is sorted with no values equaling val.

int k = removeElement(nums, val); // Calls your implementation

assert k == expectedNums.length;
sort(nums, 0, k); // Sort the first k elements of nums
for (int i = 0; i < actualLength; i++) {
    assert nums[i] == expectedNums[i];
}
```

If all assertions pass, then your solution will be **accepted**.

 

**Example 1:**

```
Input: nums = [3,2,2,3], val = 3
Output: 2, nums = [2,2,_,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 2.
It does not matter what you leave beyond the returned k (hence they are underscores).
```

**Example 2:**

```
Input: nums = [0,1,2,2,3,0,4,2], val = 2
Output: 5, nums = [0,1,4,0,3,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums containing 0, 0, 1, 3, and 4.
Note that the five elements can be returned in any order.
It does not matter what you leave beyond the returned k (hence they are underscores).
```

 

**Constraints:**

- `0 <= nums.length <= 100`
- `0 <= nums[i] <= 50`
- `0 <= val <= 100`



### Coding

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //删除序列中与给出数字相同的元素
        int k = 0;
        for(int i = 0; i< nums.size();++i)
        {
            if(nums[i] != val)
            {
                nums[k++] = nums[i];
            }
        }
        return k;

    }
};
```

## [28. Implement strStr()](https://leetcode-cn.com/problems/implement-strstr/)



Implement [strStr()](http://www.cplusplus.com/reference/cstring/strstr/).

Return the index of the first occurrence of needle in haystack, or `-1` if `needle` is not part of `haystack`.

**Clarification:**

What should we return when `needle` is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when `needle` is an empty string. This is consistent to C's [strstr()](http://www.cplusplus.com/reference/cstring/strstr/) and Java's [indexOf()](https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#indexOf(java.lang.String)).

 

**Example 1:**

```
Input: haystack = "hello", needle = "ll"
Output: 2
```

**Example 2:**

```
Input: haystack = "aaaaa", needle = "bba"
Output: -1
```

**Example 3:**

```
Input: haystack = "", needle = ""
Output: 0
```

 

**Constraints:**

- `0 <= haystack.length, needle.length <= 5 * 104`
- `haystack` and `needle` consist of only lower-case English characters.

### Coding

```c++
class Solution {
public:
    int strStr(string haystack, string needle) {
        //返回子串在主串中出现的位置
        if(haystack == needle || needle.empty())
            return 0;
        int j = 0;
        int i = 0;
        while (i < haystack.size())
		{
			if (haystack[i] == needle[j])
			{
				j++;
				i++;
			}
			else
			{
				i = i - j + 1;
				if (j != 0)
					j = 0;				
			}
			if (j == needle.size())
				break;
		}
        if(j == needle.size())
            return i-j;
        else return -1;
    }
};
```
## [32. Longest Valid Parentheses](https://leetcode-cn.com/problems/longest-valid-parentheses/)

Given a string containing just the characters `'('` and `')'`, find the length of the longest valid (well-formed) parentheses substring.

 

**Example 1:**

```
Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
```

**Example 2:**

```
Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".
```

**Example 3:**

```
Input: s = ""
Output: 0
```

 

**Constraints:**

- `0 <= s.length <= 3 * 104`
- `s[i]` is `'('`, or `')'`.

### Thinking



### Coding

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
		int len = s.length();
		if(len < 2) return 0;
        vector<int> dp(len,0);
        int max = 0;
        for(int i = 1 ; i < len;++i)
        {
            if(s[i] == ')')
            {
                int pre = i - dp[i-1]-1;
                if(pre >= 0 && s[pre] == '(')
                {
                    dp[i] = dp[i-1]+2;
                    if(pre>0)
                    {
                        dp[i] += dp[pre-1];
                        
                    }
                    if(dp[i] > max)
                        max = dp[i];
                }
            }
        }
        return max;
    }
};
```


