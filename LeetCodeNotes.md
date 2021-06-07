# LeetCodeNotes
## 1. Two Sum
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.

### Example 1:
```C++
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].
```

### Example 2:
```C++
Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
```

### Constraints:
```C++
2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.
```

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?

### Thinking
- 解法一：暴力求解，两层循环 时间复杂度n^2   
- 解法二：空间换时间，使用map存储每个元素与target的差值
- 下列代码在所有提交中的数据不是很好，时间和空间都占用比较大？还有什么其他的算法吗
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
