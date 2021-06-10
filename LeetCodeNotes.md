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
