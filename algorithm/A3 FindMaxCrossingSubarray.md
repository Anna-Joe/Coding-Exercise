查找最大子数组也是使用分治策略的一种算法。    
现实中常用来解决股票的涨势问题（应该在哪天买入哪天卖出），也就是求出各个区间中跨度最大的区间，或者说增长最多的区间。   
整个问题的解法分为两部分，一个是递归函数，另一个是递归函数本体（可以叫做非递归部分之类的？）     

先看本体，我感觉本体是整个处理方法的核心部分。将整个数组平均分成两部分，分别求左子数组和右子数组的最大子数组，~~再求跨越中点的子数组。   
但是这样看的话这个算法就只求了最大差值，并没有求到区间的端点吧？？？还是我对上面描述的解法有什么误解？？~~

```
FIND-MAX-CROSSING-SUBARRAY(A,low,mid,high)
left-sum = -∞
sum = 0
for i == mid downto low
  sum = sum + A[i]
  if sum > left-sum
    left-sum = sum
    max-left = i
    
right-sum = -∞
sum = 0
for j == mid+1 to high
  sum = sum + A[j]
  if sum > right-sum
    right-sum = sum
    max-right = j
    
return (max-left, max-right, left-sum+right-sum)
```

重新看了一遍上面的算法，发现并不是自己想的那样。应该是将整个数组从中点分成两部分（中点是一个识别点），分别求左半部分的最大子数组之和，和右半部分的最大子数组之和，并且分别记录从中点开始取到最大子数组的左坐标，和右左标（这其实就是确定了最大子数组的区间端点，返回的第三个值就是区间值）

精简地重述一次上述算法的过程：

- 从中点开始向左遍历，直到取到左半部分的最大子数组，记录左坐标
- 从中点开始向右遍历，直到取到右半部分的最大子数组，记录右坐标
- 返回 左坐标，右左标，最大子数组和



再来看递归函数的部分:

- 对数组的左半部分和右半部分分别递归求最大子数组，再求跨越中点的子数组
- 取三者之中最大的那个值返回

```
FIND-MAXIMAM-SUBARRAY(A,low,high)
if low == high
	return (low,high,A[low])
else
	mid = [(low + high)/2]
	(left-low,left-high,left-sum) = FIND-MAXIMAM-SUBARRAY(A,low,mid)
	(right-low,right-high,right-sum) = FIND-MAXIMAM-SUBARRAY(A,mid+1,high)
	(crossing-low,crossing-high,crossing-sum) = FIND-MAX-CROSSING-SUBARRAY(A,low,mid,high)
	max-sum = max of(left-sum,right-sum,crossing-sum)
	if(max-sum == left-sum)
		return (left-low,left-high,left-sum)
	else if(max-sum == right-sum)
		return (ight-low,right-high,right-sum)
	else
		return (crossing-low,crossing-high,crossing-sum)
```

