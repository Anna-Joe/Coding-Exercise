归并排序算法的关键步骤是合并两个已排序的序列。   
对于给定的数组A，其中的序列p<q<r，可以假设A[p,...,q],A[q+1,...,r]都已排序，   
MERGE函数要做的就是合并这两个有序序列。
```
MERGE(A,p,q,r)
n1 = q-p+1
n2 = r-q
//let L[1...n1+1] and R[1...n2+1] be new arrays
for i = 1 to n1 + 1
  L[i] = A[p+i-1]
for j = 1 to n2 + 1
  R[i] = A[q+j]
L[n1+1] = ∞
R[n2+1] = ∞
i = 1
j = 1
for k = p to r
  if(L[i] < R[j])
    A[k] = L[i ++]
   else
    A[k] = R[j ++]
```

通过分治的思想进一步完善算法，递归地归并排序A的左半部分和右半部分就能得到一个完整的排序序列
```
MERGE-SORT(A,p,r)
if p < r
  q = [(p+r)/2]向下取整
  MERGE-SORT(A,p,q)
  MERGE-SORT(A,q+1,r)
  MERGE(A,p,q,r)
```
