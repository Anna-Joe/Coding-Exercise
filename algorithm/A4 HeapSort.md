堆的插入排序算法
首先获取插入位置的左子树和右子树 如果插入位置的左子树和右子树中有大于插入值的值 则替换二者的位置（必须保证根节点大于左右子树节点）
```
MAX-HEAPIFY(A,i)
l = LEFT(i)
r = RIGHT(i)
if l <= A.heap-size and A[l] > A[i]
  largest = l
 else
  largest = i
if r <= A.heap-size and A[r] > A[i]
  largest = r
if largest != i
  exchange(A[i],A[largest])
  MAX-HEAPIFY(A,largest)
```

堆的构造算法（构造最大堆）
子数组A[n/2+1,...,n]中的元素都是树的叶子节点。这里构造的时候遍历的都是根节点
```
BUILD-MAX-HEAP(A)
A.heap-size = A.length
for i = A.length / 2 to 1
  MAX-HEAPIFY(A,i)
```

堆排序算法
A【1】是整个堆中最大的项点，通过exchange每次先将最大的顶点放置到数组的末尾，以便取下（size-1），然后重新排列数组得到新的大根堆。
```
HEAPSORT(A)
BUILD-MAX-HEAP(A)
for i = A.length downto 2
  exchange A[1] with A[i]
  A.heap-size = A.heap-size - 1
  MAX-HEAPIFY(A,1)
```
