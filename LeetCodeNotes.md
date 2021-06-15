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
