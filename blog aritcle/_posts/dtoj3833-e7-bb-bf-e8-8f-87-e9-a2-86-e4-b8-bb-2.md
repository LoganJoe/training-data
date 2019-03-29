---
title: " DTOJ3833绿菇领主\t\t"
tags:
  - 思路
  - 线段树
url: 3051.html
id: 3051
categories:
  - Solution
date: 2018-07-25 16:22:28
---

##### 简化问题

我们先来考虑这个问题的简化版问题，即在一个排列上的情况。 我们区间内的数权值化后在数轴上打标记。那么一个区间是连续的，在数轴上的连续块个数就为1。 那么我们先考虑$O(n^2)$的做法。确定一个左端点以后顺序往后推右端点，并且每次加一个数到数轴上。

*   如果两侧均有标记，那么联通块个数减一。
    
*   如果仅有一侧有标记，联通块个数不变。
    
*   否则，联通块个数加一。
    

考虑这样的问题怎么优化维护。倒着枚举固定数字区间左端点 $i $。我们需要知道对于任意的右端点 $j(i \\leqslant j \\leqslant n)$，区间$ \[i, j\] $会被分为$ P $中几段,记为 $f_{i,j}$。 递推，即左端点枚举到 $i$ 时，我们已知所有 $f_{i+1,j}$ 若 $i$ 在 $P$ 中的位置为 $x$，考虑 $x − 1$, $x + 1$ 两个位置上的数

*   若 $P_{x−1} < i$且$P_{x+1} < i$，则 $i$ 只能新开一个连通块 $\\forall i \\leq j \\leq n$,$f_{i,j} = f_{i+1,j + 1}$
    
*   若 $P_{x−1} > i$且$P_{x+1} > i$，假设 $R = max(P_{x−1}, P_{x+1}), L = min(P_{x−1}, P_{x+1})$
    
*   $j \\geq R$ 时，$i$ 就能与 $L、R $所在块分别合并，连通块个数减一 $\\forall R \\leq j \\leq n, f_{i,j} = f_{i+1,j − 1}$
    
*   $ L \\leq j < R$ 时，$i$ 能与 $L$ 所在块合并，连通块个数不变 $\\forall L \\leq j < R, f_{i,j} = f_{i+1,j}$
    
*   $i \\leq j < L$，$i$ 只能单独开一段，连通块个数加一 $\\forall i \\leq j < L, f_{i,j }= f_{i+1,j + 1}$
    

$ P_{x−1} $与$ P_{x+1}$中恰有一个数大于$ i$ 的情况可以类似讨论 。 那么我们用线段树维护$f_{i,j}$，每个节点记录最小值与最小值个数。然后统计$f_{i,j}=1$的数目即可。 对于DTOJ3487第三题，DTOJ3036区间，做法几乎等同。 那么我们考虑这题的十个值要怎么处理。 我们可以对于相邻两个数，由于出现时候一定要同时出现，那么我们维护一下相邻两个数，其中一个出现a次，另外一个出现b次的左/右区间，以及更新的区间$\[l,r\]$。在生效与失效的时间戳上打上-1与+1标记，线段树操作推过去的时候扫描线处理一下就好了。