查找最大子数组也是使用分治策略的一种算法。    
现实中常用来解决股票的涨势问题（应该在哪天买入哪天卖出），也就是求出各个间中增长最多的区间。   
```
FIND-MAX-CROSSING-SUBARRAY(A,low,mid,high)
left-sum = -∞
sum = 0
for i == mid downto low
  sum = sum+A[i]
