---
title: Fundamental data structure
date: 2025/2/23 18:50
categories: notes
tags:
  - study
  - C
series: fds
cover: /fds.png
---
# Algorithm analysis
## algorithm and program
- **algorithm**:described by human languages,flow charts,programming lanuage,pseudocode
- **program**:written in some programming language(==can be meaningless==)
## what to analyze
> running time?

==run time==:machine and compiler-dependent
==Time & space complexities==:machine and compiler-**in**dependent
### Assumption(usually not true)
- sequentially executed
- each instruction is **simple**,tasks exactly **one time unit**
- integer size is fixed & infinite memory
$T_{avg}(N)\ T_{worst}(N)$ --the average and worst time complexity , as function of **input size N**
## Asympotic Notation
$$
\begin{aligned}
\begin{cases}
O:upper\ bound(worst\ case)\\
\Omega:lower\ bound(best\ case)\\
\Theta:upper=lower\\
o:T(N)=O(p(N))\ and\ T(N)\neq\Theta(p(N))
\end{cases}
\end{aligned}
$$
### rules
- if $T_1(N)=O(f(N))$ and $T_2(N)=O(g(N))$,then
	- $T_1(N)+T_2(N)=\max{O(f(N)),O(g(N))}$
	- $T_1(N)\times T_2(N)=O(f(N)\times g(N))$
- if $T(N)$ is a polynomial(多项式) of degree k($T(N)=\sum a_iN^i$),then $T(N)=\Theta(N^k)$
- $\log^k N=O(N)$ for any constant k. This tells us that ==logarithms grow very slowly==

| Function  |    Name     |
| :-------: | :---------: |
|     c     |  Constant   |
| $\log N$  | Logarithmic |
| $\log^2N$ | Los-squared |
|    $N$    |   Linear    |
| $N\log N$ | Log linear  |
|   $N^2$   |  Quadratic  |
|   $N^3$   |    Cubic    |
|   $2^N$   | Exponential |
|   $N!$    |  Factorial  |
![[Pasted image 20250621105319.png]]
### recursions
```c
long int Fib(int N)  /*T(N)*/
{
	if(N <= 1)      /*O(1)*/
		return 1;
	else
		return Fib(N - 1) + Fib(N - 2);
		       /*T(N - 1)*//*T(N - 2)*/
}
```
$$
\begin{align}
T(N) =T(N-1)+&T(N-2)+2\geq Fib(N)\\
\bigg(\frac 32\bigg)^N\leq Fib&(N)\leq\bigg(\frac 53\bigg)^N
\end{align}
$$
# Compare the algorithm
## example
> find the largest list

1. $T(N)=O(N^3)$
```c
int MaxSubsequenceSum (const int A[], int N)
//暴力搜索，寻找所有求和关系，i外层循环控制求和起始位，j中间层循环控制求和终止位，k内层循环控制求和过程
{
    int ThisSum, MaxSum, i, j, k;
    MaxSum = 0; /* 初始化最大和 */
    for(i = 0; i < N; i++) /* 从 A[i] 开始 */
        for(j = i; j < N; j++) { /* 到 A[j] 结束 */
            ThisSum = 0;
            for(k = i; k <= j; k++)
                ThisSum += A[k]; /* 计算从 A[i] 到 A[j] 的和 */
            if (ThisSum > MaxSum)
                MaxSum = ThisSum; /* 更新最大和 */
        } /* 结束内层 for-j 和 for-i */
    return MaxSum;
}
```
2. $T(N)=O(N^2)$
```c
int MaxSubsequenceSum ( const int A[], int N )
//相比暴力搜索，简化起始位固定情况相加情况，set起始i，计算所有以i开头的list的sum，并在一步步求和过程中不断比较，最终保留最大结果
{
    int ThisSum, MaxSum, i, j, k;
    MaxSum = 0; /* initialize the maximum sum */
    for(i = 0; i < N; i++) { /* start from A[i] */
        ThisSum = 0;
        for(j = i; j < N; j++) { /* end at A[j] */
            ThisSum += A[j]; /* sum from A[i] to A[j] */
            if ( ThisSum > MaxSum )
                MaxSum = ThisSum; /* update max sum */
        } /* end for-j */
    } /* end for-i */
    return MaxSum;
}
```
3. Divide and Conquer
![[Pasted image 20250621105922.png]]
- binarily divide the list into two half , and recursively find the max list in the sublist.
	- divide into sublist of minimum size -> one node for each sublist
	- conquer:compare1.two max sum of the two sublists 2. max list grow from the boarder of two sublists
- recursion time complexity
$$
\begin{aligned}	
T(N)=&2T(\frac N{2})+cN\\
T(\frac N{2})=&2T(\frac N{2^2})+c\frac N2\\
T(\frac N{2^2})=&2T(\frac N{2^3})+c\frac N4\\
&\vdots\\
T(\frac N{2^{k-1}})=&2T(\frac N{2^k})+c\frac N{2^{k-1}}\\
\\
\\
T(N)=&2^kO(1)+cN\log N\\
=&O(N\log N)
\end{aligned}
	$$
4. On-line Algorithm $T(N)=O(N)$
```c
int MaxSubsequenceSum( const int A[], int N )
//从正数开始加，然后和小于0了就重新开始
{
    int ThisSum, MaxSum, j;
    ThisSum = MaxSum = 0;
    for (j = 0; j < N; j++) {
        ThisSum += A[j];
        if ( ThisSum > MaxSum )
            MaxSum = ThisSum;
        else if ( ThisSum < 0 )
            ThisSum = 0;
    } /* end for-j */
    return MaxSum;
}
```
## Logarithm in the running time
> find the median

Binary Search
![[Pasted image 20250418152746.png]]
```c
int BinarySearch ( const ElementType A[], ElementType X, int N )
// just a basic algorithm of binary search
{
    int Low, Mid, High;
    Low = 0; High = N - 1;
    while (Low <= High) {
        Mid = (Low + High) / 2;
        if ( A[ Mid ] < X )
            Low = Mid + 1;
        else
            if ( A[ Mid ] > X )
                High = Mid - 1;
            else
                return Mid; /* Found */
    } /* end while */
    return NotFound; /* NotFound is defined as -1 */
}
```
$$
T_{worst}(N)=O(\log N)$$

## Euclid's algorithm（欧几里得算法）
>Find the GCD(Greatest Common Divisor)(辗转相除法求最大公约数）

```c
function gcd(a, b):
    while b ≠ 0:
        temp := b
        b := a mod b
        a := temp
    return a
```
$$T(N)=O(\log{\min\{a,b\}})$$
## Exponentiation（快速幂算法)
>To compute $a^b$ efficiently

```c
int power(int base, int exp, int modulus) { 
//(X⋅Y)(modM)=((X(modM))⋅(Y(modM)))(modM)
	int res = 1; 
	base %= modulus; 
	while (exp > 0) { 
		if (exp % 2 == 1) { 
			res = (res * base) % modulus; 
		} 
		base = (base * base) % modulus; 
		exp /= 2; 
	} 
	return res; 
}
```
$$T(N)=O(\log b)$$
## Check your analysis
$$
when\ T(N)=O(f(N)),check\ if\lim_{N\rightarrow +\infty}\frac{T(N)}{f(N)}=constant
$$
---
# Lists,Stacks, and Queues
## Abstract Data Type(ADT)
>A date type that is organized in such a way that the **specification** on the objects and **specification** of the operations on the objects are **separated from** the **representation** of the objects and the **implementaion** on the operations.（对于数据类型和操作的规约和具体实现方式分离）

## The List ADT
### Operations
- Find the length
- Print
- Making an empty
- Find the k-th
- Insert
- Delete
- Find next
- Find previous
## implementations
1. array
	- maxsize has to be estimated
	- find_kth takes O(1) time
	- insetion and deletion takes O（N） time, involve a lot of data movements
```c
array[i]=item
```

2.  linked list
	- find kth takes O(n) time
	- insertion and deletion takes O(N) time to find , and O(1) time to change 
	- cursor implementation of linked list
		- requires customized malloc 
3. Doubly linked circular lists
![[Pasted image 20250418160124.png]]
![[Pasted image 20250418160151.png]]
### Multilist
![[Pasted image 20250418160605.png]]
### Cursor implementation of linked list
Use the linked list to serve as malloc and free function.
![[Pasted image 20250418161641.png]]
## The Stack ADT
fundamental data arrange
**Last-In-First-Out** -> reverse order
### operation
- IsEmpty
- CreatStack
- DisposeStack
- MakeEmpty
- **Push**
- Top
- **Pop**

> a pop on a empty stack is errror in the stack ADT

### Implements
1. linked list
2. array
	```c
struct stack{
	int capacity;
	int topofstack;
	Elementtype *array
}
```

### Application
1. balancing symbols
	check if parenthesis , brackets , braces are balanced
```c
Algorithm {
//简单的遇到左括号入栈，遇到右括号检查栈顶元素，匹配则出栈，否则error
    Make an empty stack S;
    while (read in a character c) {
        if (c is an opening symbol)
            Push(c, S);
        else if (c is a closing symbol) {
            if (S is empty) { ERROR; exit; }
            else { /* stack is okay */
                if (Top(S) doesn’t match c) { ERROR, exit; }
                else Pop(S);
            } /* end else-stack is okay */
        } /* end else-if-closing symbol */
    } /* end while-loop */
    if (S is not empty) ERROR;
}
```
2. postfix conversion
Infix to Postfix Conversion
- the order of **operands** is the same
- **operators** with higher precedence appear before those with lower precedence
- how to solve ()
	- never pop a ( from the stack except when processing a )
	- when ( is not in the stack ,its precedence is the **highest**,but when it is in the stack its the **lowest**.
2. function calls
```c
void PrintList (List L) {
    if ( L != NULL ) {
        PrintElement ( L->Element );
        PrintList( L->next );
    }
} /* a bad use of recursion */

void PrintList (List L) {
top: if ( L != NULL ) {
    PrintElement ( L->Element );
    L = L->next;
    goto top; /* do NOT do this */
}
} /* compiler removes recursion */
```
## The Queue ADT
limited resources
**First-In-First-Out**
### operation
- isempty
- creatqueue
- disposequeue
- makeempty
- enqueue
- front
- dequeue
### Implementation
#### Array
```c
struct QueueRecord {
    int Capacity; /* max size of queue */
    int Front;    /* the front pointer */
    int Rear;     /* the rear pointer */
    int Size;     /* Optional - the current size of queue */
    ElementType *Array; /* array for queue elements */
};
```
### Circular Queue
常用方法是牺牲一个位置的空间来区分队列是满还是空(rear指向的是最后一个元素的下一个位置）
- 空：rear=front
- 满:(rear+1)%MAX_SIZE=front
# Tree
>A tree is a collection of nodes. The collection can be empty;otherwise, a tree consists of
>	- a distinguished node r,called the**root**
>	- zero or more nonempty **(sub)trees** $T_1,\cdots,T_k$,each of whose roots are connected by a directed **edge** from r

1. **degree of a node**:number of subtrees of the node子树个数
2. **degree of a tree**:the *max* degree of the nodes of the tree最大子树个数
3. **parent**:a node that has subtrees
4. **children**:the roots of the subtrees of a parent
5. **siblings**:children of the same parent
6. **leaf**:a node with degree 0
7. **path from $n_1$ to $n_k$**:a (**unique**) sequence of nodes $n_1,n_2,\cdots,n_k$ such that $n_i$ is the parent of $n_{i+1}$
8. **length of path**:number of **edges** on the path
9. **depth of $n_i$**:length of the unique path from **the root to $n_i$**
10. **height of $n_i$**:length of the longest path from $n_i$ to a leaf
11. **height(depth) of a tree**:height(root)=depth(deepest leaf)
12. **ancestors of a node**:all the nodes along the path from the node up to the root
13. **descendants of a node**:all the nodes in its subtrees
## Implementation
### List representation
![[Pasted image 20250418184834.png]]
**The size of each node depends on the number of branches.**
### FirstChild-NextSibling Representation
![[Pasted image 20250418184945.png]]
## Binary Tree
>A binary tree is a tree in which no node can have more than **two children**

### Expression tree
![[Pasted image 20250418185239.png]]
### Tree traversals
```c
Preorder Traversal
void preorder (tree_ptr tree) {
    if (tree) {
        visit (tree);
        for(each child C of tree)
            preorder (C);
    }
}

Postorder Traversal
void postorder (tree_ptr tree) {
    if (tree) {
        for(each child C of tree)
            postorder (C);
        visit (tree);
    }
}

Levelorder Traversal
void levelorder (tree_ptr tree) {
    enqueue (tree);
    while(queue is not empty){
        visit ( T = dequeue ());
        for(each child C of T)
            enqueue (C);
    }
}

Inorder Traversal
void inorder (tree_ptr tree) {
    if (tree) {
        inorder (tree->Left);
        visit (tree->Element);
        inorder (tree->Right);
    }
}
```
#### An interative program of inorder traversal
```c
void iter_inorder(tree_ptr tree){
	Stack S = CreatStack(MAX_SIZE);
	for(;;){
		for(;tree;tree = tree->left)
			Push(tree,S);
		tree = Top(S);
		Pop(S);
		if(!tree)
			break;
		visit(tree->Element);
		tree = tree->Right;
	}
}
```

### Skewed binary tree
![[Pasted image 20250418190926.png]]
### Complete binary tress
![[Pasted image 20250418190946.png]]
### Threaded Binary Trees
1. 如果左子树为空，则指向遍历的前一个节点
2. 如果右子树为空，则指向遍历的下一个节点
3. 新建head node作为遍历的第一个节点的左子树和最后一个节点的右子树
![[Pasted image 20250621123046.png]]
### Properties
- The max number of nodes on **level** $i$ is $2^{i-1}$
- The max number of nodes in **a binary tree of depth** $k$ is $2^{k-1}$
- For any none empty binary tree $n_0 =n_2+1$
$$
\begin{aligned}
n&=n_0+n_1+n_2\\
n&=B+1=n_1+2n_2+1
\end{aligned}
$$
## Binary Search Trees
> A **binary search tree** is a binary tree.It may be empty.If it is not empty,it satisfies the following properties:
> 	- Every node has a **key** which is an **integer** ,and the keys are **distinct**.
> 	- The keys in a nonempty **left** subtree must be **smaller** than the key in the root of the subtree.
> 	- The keys in a nonempty **right** subtree must be **larger** than the key in the root of the subtree.
> 	- The left and right subtree are also **binary search trees**
### ADT
#### Operations
- MakeEmpty
- Find
```c
Position Find(ElementType X, SearchTree T) {
    if (T == NULL)
        return NULL; /* not found in an empty tree */
    if (X < T->Element) /* if smaller than root */
        return Find(X, T->Left); /* search left subtree */
    else if (X > T->Element) /* if larger than root */
        return Find(X, T->Right); /* search right subtree */
    else /* if X == root */
        return T; /* found */
}
```
$$
T(N)=O(d)\ where\ d\ is\ the\ depth\ of\ X
$$
```c
Position Iter_Find(ElementType X, SearchTree T) {
    /* iterative version of Find */
    while (T) {
        if (X == T->Element)
            return T; /* found */
        if (X < T->Element)
            T = T->Left; /* move down along left path */
        else
            T = T->Right; /* move down along right path */
    } /* end while-loop */
    return NULL; /* not found */
}
```

- FindMin
```c
Position FindMin(SearchTree T) {
    if (T == NULL)
        return NULL; /* not found in an empty tree */
    else if (T->Left == NULL)
        return T; /* found left most */
    else
        return FindMin(T->Left); /* keep moving to left */
}
```
$$
T(N)=O(d)
$$
- FindMax
```c
Position FindMax(SearchTree T) {
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right; /* keep moving to find right most */
    return T; /* return NULL or the right most */
}
```
$$
T(N)=O(d)
$$
- Insert
	1. check if the new number is **already** in the tree
	2. **the last key** when search for the key number will be the **parent** of the new node 
```c
SearchTree Insert(ElementType X, SearchTree T) {
    if (T == NULL) {
        /* Create and return a one-node tree */
        T = malloc(sizeof(struct TreeNode));
        if (T == NULL)
            FatalError("Out of space!!!");
        else {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    } /* End creating a one-node tree */
    else /* If there is a tree */
        if (X < T->Element)
            T->Left = Insert(X, T->Left);
        else if (X > T->Element)
            T->Right = Insert(X, T->Right);
        /* Else X is in the tree already; we'll do nothing */
    return T; /* Do not forget this line!! */
}
```
$$
T(N)=O(d)
$$
- Delete
	1. Delete a **leaf node**:reset its parent link to NULL
	2. Delete a **degree 1 node**:replace the node by its single child
	3. Delete a **degree 2 node**:
		1. replace the node by the **largest** one in its **left** subtree *or* the **smallest** one in its **right** subtree.
		2. Delete the replacing node from the subtree
```c
SearchTree Delete(ElementType X, SearchTree T) {
    Position TmpCell;
    if (T == NULL)
        Error("Element not found");
    else if (X < T->Element) /* Go left */
        T->Left = Delete(X, T->Left);
    else if (X > T->Element) /* Go right */
        T->Right = Delete(X, T->Right);
    else /* Found element to be deleted */
        if (T->Left && T->Right) {
            /* Two children */
            /* Replace with smallest in right subtree */
            TmpCell = FindMin(T->Right);
            T->Element = TmpCell->Element;
            T->Right = Delete(T->Element, T->Right);
        } /* End if */
        else {
            /* One or zero child */
            TmpCell = T;
            if (T->Left == NULL) /* Also handles 0 child */
                T = T->Right;
            else if (T->Right == NULL)
                T = T->Left;
            free(TmpCell);
        } /* End else 1 or 0 child */
    return T;
}
```
$$
T(N)=O(d)
$$
>**lazy deletion**
>add a flag field to each node ,to **mark** if a node is active or is deleted
- Retrieve
### Average-Case Analysis
Place $n$ elements in a binary search tree.How high can this tree be?
>The height depends on the **order of insertion**

![[Pasted image 20250418200739.png]]
# Priority Queues(Heaps)
## Operations
- Initialize
- Insert
- DeleteMin
- FindMin
## Simple Implementation
![[Pasted image 20250418201003.png]]
## Binary Heap
>A **binary tree** with $n$ nodes and height $h$ is **complete** iff its nodes correspond to the node number from 1 to $n$ in the perfect binary tree of height $h$

$$
h=\lfloor\log N\rfloor
$$
### Array representation
![[Pasted image 20250418201906.png]]
![[Pasted image 20250418201931.png]]
### Initialize
```c
PriorityQueue Initialize(int MaxElements) {
    PriorityQueue H;
    if (MaxElements < MinPQSize)
        return Error("Priority queue size is too small");
    H = malloc(sizeof(struct HeapStruct));
    if (H == NULL)
        return FatalError("Out of space!!!");
    /* Allocate the array plus one extra for sentinel */
    H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));
    if (H->Elements == NULL)
        return FatalError("Out of space!!!");
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData; /* set the sentinel */
    return H;
}
```
### Heap Order Property
>A **min tree** is a tree in which the key value in each node is no larger than the key values in its children.
>A **min heap** is a **complete** binary tree that is also a min tree
#### Insertion
**The only possible position for a new node**
![[Pasted image 20250418202701.png]]
```c
void Insert(ElementType X, PriorityQueue H) {
    int i;
    if (IsFull(H)) {
        Error("Priority queue is full");
        return;
    }
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}
```
$$T(N)=O(\log N)$$
#### DeleteMin
```c
ElementType DeleteMin(PriorityQueue H) {
    int i, Child;
    ElementType MinElement, LastElement;
    if (IsEmpty(H)) {
        Error("Priority queue is empty");
        return H->Elements[0];
    }
    MinElement = H->Elements[1]; /* save the min element */
    LastElement = H->Elements[H->Size--]; /* take last and reset size */
    for (i = 1; i * 2 <= H->Size; i = Child) { /* Find smaller child */
        Child = i * 2;
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            Child++;
        if (LastElement > H->Elements[Child]) /* Percolate one level */
            H->Elements[i] = H->Elements[Child];
        else
            break; /* find the proper position */
    }
    H->Elements[i] = LastElement;
    return MinElement;
}
```
$$T(N)=O(\log N)$$
#### Other Heap Operations
1. Finding any key except min will have to take **a linear scan through the entire heap**
2. DecreaseKey
3. IncreaseKey
4. Delete
5. BuildHeap
	time complexity:for perfect binary tree of height h containing $2^{h+1}-1$ nodes,the sum of the heights of the nodes is $2^{h+1}-1-(h+1)$,so $T(N)=O(N)$
### Application
>Given a list of N elements and a integer K.Find the kth largest element.

### d-Heaps
![[Pasted image 20250418203708.png]]
DeleteMin will cost $O(d\log_d N)$
# Disjoint set ADT
## Equivalence Relations
>A **relation R** is defined on a set S if for every pair of elements$(a,b),a,b\in S,a\ R\ b$ is either true or false.If $a\ R\ b$ is true ,then we say that **a is related to b**

>A relation,~, over a set,S,is said to be a **equivalence relation** over S iff it is **symmetric(对称性),reflexive(反身性) and transitive(传递性)** over S

>Two member x and y of a set S are said to be in the same **equivalence class** iff $x\sim y$

```c
/* Step 1: Read the relations in */
Initialize N disjoint sets;
while (read in a ~ b) {
    if (! (Find(a) == Find(b))) {
        Union the two sets;
    }
} /* end-while */

/* Step 2: Decide if a ~ b */
while (read in a and b) {
    if (Find(a) == Find(b)) {
        output(true);
    } else {
        output(false);
    }
}
```
## Operation
- Union
	1. Implementation1:
![[Pasted image 20250418210825.png]]
	2. Implementation2:
![[Pasted image 20250418210842.png]]
```c
/* Union by setting the parent pointer of one root to the other root */
void SetUnion(DisjSet S, SetType Rt1, SetType Rt2) {
    S[Rt2] = Rt1;
}
```

- Find
	1. Implementation1:
![[Pasted image 20250418210957.png]]
	2. Implementation2:
```c
/* Find operation */
SetType Find(ElementType X, DisjSet S) {
    for (; S[X] > 0; X = S[X]);
    return X;
}
```
### Algorithm using union-find operations
```c
/* Algorithm using union-find operations */
{
    Initialize Si = { i } for i = 1, ..., 12;
    for (k = 1; k <= 9; k++) {
        /* for each pair i ~ j */
        if (Find(i) != Find(j)) {
            SetUnion(Find(i), Find(j));
        }
    }
}
```
## Smart Union Algorithm
### Union-by-size
>always change the smaller tree

$$h\leq\lfloor\log_2 N\rfloor+1$$
**N Union and M Find** operations takes$O(N+M\log_2N)$
### Union-by-Height
>always change the shallow tree
### Path Compression（Union-by-rank）
```c
SetType Find(ElementType X, DisjSet S) {
    if (S[X] <= 0)
        return X;
    else
        return S[X] = Find(S[X], S);
}

/* Another version of Find with path compression */
SetType Find(ElementType X, DisjSet S) {
    ElementType root, trail, lead;
    for (root = X; S[root] > 0; root = S[root]); /* find the root */
    for (trail = X; trail != root; trail = lead) {
        lead = S[trail];
        S[trail] = root;
    } /* collapsing */
    return root;
}
```
#### Worst Case For
$$
k_1M\alpha(M,N)\leq T(M,N)\leq k_2M\alpha(M,N)

$$
##### Ackermann's Function
$$
A(i,j)=\begin{cases}
2^j&i=1\ and\ j\geq1\\
A(i-1,2)&i\geq2\ and\ j=1\\
A(i-1,A(i,j-1))&i\geq2\ and\ j\geq2
\end{cases}
$$
$$
\alpha(M,N)=\min\{i\geq1|A(i,\lfloor M/N\rfloor)>\log N\}\leq O(log^*N)\leq 4
$$
# Graph Algorithms
## Definition
- G(V,E)
	- G::=graph
	- V::=finite nonempty set of vertices
	- E::=finite set of edges
- Undirected graph:$(v_i,v_j)=(v_j,v_i)$::=the same edge
- Directed graph:$<v_i,v_j>::=v_i \rightarrow v_j \neq <v_j,v_i>$
- Restrictions
	- self loop is illegal
	- multigraph is not considered
- Complete graph:a graph that has the maximum number of edges
- ![[Pasted image 20250621151949.png]]
- Length of a path::=number of edges on the path
- Simple path::=vertexes on the path are distinct
- Cycle::=simple path with the same start and end
- $v_i\ and\ v_j$ in a undirected G are **connnected** if there's a path from i to j
- 连通图（无向）：对于每个$v_i,v_j$组合都是连通的
![[Pasted image 20250621152909.png]]


## Shortest Path Algorithm
### Single-Source Shortest -Path Problem
>Given as input a weighed grah ,$G=(V,E)$,and a distinguished vertex,$s$,find the shortest weighed path **from s to every other vertex in $G$**

![[Pasted image 20250424134054.png]]
>If there's no negative-cost cycle, the shortest path from s to s is defined to zero.
#### Unweighed Shortest Paths
![[Pasted image 20250424134310.png]]
>Breadth-first search（广度优先算法）
>[广度优先搜索](https://so.csdn.net/so/search?q=%E5%B9%BF%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2&spm=1001.2101.3001.7020)（也称宽度优先搜索，缩写BFS，以下采用广度来描述）是**连通图**的一种遍历策略。因为它的思想是从一个顶点$V_0$开始，辐射状地优先遍历其周围较广的区域，因此得名。

```c
void Unweighted(Table T) {
    int CurrDist;
    Vertex V, W;
    for (CurrDist = 0; CurrDist < NumVertex; CurrDist++) {
        for (each vertex V)
            if (!T[V].Known && T[V].Dist == CurrDist) {
                T[V].Known = true;
                for (each W adjacent to V)
                    if (T[W].Dist == Infinity) {
                        T[W].Dist = CurrDist + 1;
                        T[W].Path = V;
                    } /* end-if Dist == Infinity */
            } /* end-if !Known && Dist == CurrDist */
    } /* end-for CurrDist */
}
```
The worst case:
![[Pasted image 20250424134824.png]]
$$T=O(|V|^2)$$
>Improvement

```c
void Unweighted(Table T) {
    /* T is initialized with the source vertex S given */
    Queue Q;
    Vertex V, W;
    Q = CreateQueue(NumVertex);
    MakeEmpty(Q);
    Enqueue(S, Q); /* Enqueue the source vertex */
    while (!IsEmpty(Q)) {
        V = Dequeue(Q);
        T[V].Known = true; /* not really necessary */
        for (each W adjacent to V)
            if (T[W].Dist == Infinity) {
                T[W].Dist = T[V].Dist + 1;
                T[W].Path = V;
                Enqueue(W, Q);
            } /* end-if Dist == Infinity */
    } /* end-while */
    DisposeQueue(Q); /* free memory */
}
```
$$T=O(|V|+|E|)$$

#### Dijkstra's Algorithm
>Let S={s and $v_i$'s whose shortest paths have been fonund}
>For any $u\notin S$, define **distance[u]=minimal length of path{$s\rightarrow (v_i\in S)\rightarrow u$}** If the paths are generated in **non-decreasing** order,then
>	- the shortest path must go through **ONLY** $v_i\in S$
>	- u is chosen so that **distance[u]=$\min\{w\notin S|distance[w]\}$**
>	- if $distance[u_1]< distance[ u_2 ]$ and we add $u_1$ into S,then $distance[u_2]$ may change.If so ,a shorter path from s to $u_2$ must go through $u_1$ and $distance^\prime[u_2]=distance[u_1]+length(<u1,u_2>)$

```c
void Dijkstra(Table T) {
    /* T is initialized by Figure 9.30 on p.303 */
    Vertex V, W;
    for (;; ) {
        V = smallest unknown distance vertex;
        if (V == NotAVertex)
            break;
        T[V].Known = true;
        for (each W adjacent to V)
            if (!T[W].Known)
                if (T[V].Dist + Cvw < T[W].Dist) {
                    Decrease(T[W].Dist to T[V].Dist + Cvw);
                    T[W].Path = V;
                } /* end-if update W */
    } /* end-for(;;) */
}
```
##### Implementation
1. simply scan the table
$$T=O(|V|^2+|E|)$$
2. keep distances in a priority queue and call DeleteMin
$$T=O(|E|\log |V|)$$
#### Graphs with Negative Edge Costs
```c
void WeightedNegative(Table T) {
    /* T is initialized by Figure 9.30 on p.303 */
    Queue Q;
    Vertex V, W;
    Q = CreateQueue(NumVertex);
    MakeEmpty(Q);
    Enqueue(S, Q); /* Enqueue the source vertex */
    while (!IsEmpty(Q)) {
        V = Dequeue(Q);
        for (each W adjacent to V)
            if (T[V].Dist + Cvw < T[W].Dist) {
                T[W].Dist = T[V].Dist + Cvw;
                T[W].Path = V;
                if (W is not already in Q)
                    Enqueue(W, Q);
            } /* end-if update */
    } /* end-while */
    DisposeQueue(Q); /* free memory */
}
```
$$T=O(|V|\times |E|)$$
### Acyclic Graphs
>If the graph is acyclic, vertices may be selected in **topological order** since when a vertex is selected,its distance can no longer be lowered without any incoming edges form unknown nodes.

$$T=O(|E|+|V|)$$ and no priority queue is needed.
$EC[j]/LC[j]$ the earliest\latest completion time for node $v_j$
![[Pasted image 20250424162509.png]]
![[Pasted image 20250424171434.png]]
## All-Pairs Shortest Path Problem
For all pairs of $v_i$ and $v_j (i\neq j)$ 