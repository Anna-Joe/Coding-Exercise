#### 一个最大优先队列支持以下操作：
- INSERT(S,X)把元素X插入集合S中   
- MAXIMUM(S)返回S中具有最大关键字的元素   
- EXTRACT-MAX(S)去掉并返回具有最大关键字的元素   
- INCREASE-KEY(S,X,K)将元素X的关键字值增加到K，这里假设K的值不小于X的原值

返回最大值
```
HEAP-MAXIMUM(A)
  return A[1]
```

去掉并返回具有最大关键字的元素（像是出栈）
```
HEAP-EXTRACT-MAX(A)
if A.heap-size < 1
    error "heap underflow"
max = A[i]
A[1] = A[A.heap-size]
A.heap-size = A.heap-size - 1
MAX-HEAPIFY(A,1)
return max
```

将元素的最大关键字加到key
```
HEAP-INCREASE-KEY(A,i,key)
if key < A[i]
  error"new key is smaller than current key"
A[i] = key
while i > 1 and A[PARENT(i) < A[i])
    exchange A[i] with A[PARENT[i])
    i = PARENT(i)
```

为新节点设置关键字，并保持最大堆的性质
```
MAX-HEAP-INSERT(A,key)
A[A.heap-size] = -∞
HEAP-INCREASE-KEY(A,A.heap-size,key)
```
