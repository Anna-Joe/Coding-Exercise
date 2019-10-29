数组A[p,...,r]被划分为两个子数组A[p,..,q-1]和A[q+1,...,r]，使得A[p,..,q-1]里面每一个元素都小于A[q]，而A[q]也小于等于A[q+1,...,r]里每个元素。    
通过递归调用快速排序算法分别对两个子数组进行递归排序。    
因为子数组都是原址排序，所以不需要合并操作，A已经有序。    
```C++
QUICKSORT(A,p,r)
if p < r
  q = PARTITION(A,p,r)
  QUICKSORT(A,p,q-1)
  QUICKSORT(A,q+1,r)
  
PATITION(A,p,r)
x = A[r]
i = p-1
for j = p to r - 1
  if A[j] <= x
    i = i + 1
    exchange A[i] with A[j]
exchange A[i+1] with A[r]
return i+1

//快速排序的随机化算法
RANDOMIZED-QUICKSORT(A,p,r)
if p < r
  q = RANDOMIZED-PARTITION(A,p,r)
  RANDOMIZED-QUICKSORT(A,p,q-1)
  RANDOMIZED-QUICKSORT(A,q+1,r)
  
RANDOMIZED-PARTITION(A,p,r)
i = RANDOM(p,r)
exchange A[r] with A[i]
return PARTITION(A,p,r)  
```

