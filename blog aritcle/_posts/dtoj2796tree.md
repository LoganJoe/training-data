---
title: " DTOJ2796tree\t\t"
tags:
  - 思路
  - 线段树
url: 5301.html
id: 5301
categories:
  - Solution
date: 2018-11-25 22:23:42
---

这题强制换根...2333 动态树我们会想到LCT实现，但是子树覆盖用dfs序可以用线段树解决。 仍然考虑在dfs序上处理问题。我们可以尝试将换根后的dfs区间转化到以$1$为根的dfs序区间上。 考虑当前根到$1$（即原来的根）的路径。以下分三类讨论：

1.  假设当前根为$1$，那么区间仍然是$\[pos\[lca\],sub\[lca\]\]$。
2.  假设当前$u \\to v$的路径与$rt \\to 1$的路径没有交集的时候，换根不会改变$lca$下子树的形态，也就是不会对dfs序的区间产生影响。这种情况的判定就是$lca(lca(u,v),rt)\\neq lca(u,v)$，否则就一定存在交集。这个时候的区间也是$\[pos\[lca\],sub\[lca\]$。
3.  否则我们会发现，将rt吊起来做根以后，最少影响到的点就是两交集最深的点（也是就是下图中的$lca(rt,v)$)。可以在$lca(u,rt)$与$lca(v,rt)$间取最深点，这个点是换根后，路径往上深度最小的点。这个最深点沿路径往下的下一个点的子树中就不会被影响，也就是说除了$\[pos\[deepest\],sub\[deepest\]\]$中的点，其他部分都会被影响。那么我们只需要全树加$x$，这个区间减$x$即可。

![](https://img-blog.csdn.net/20180124183032216?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvc2R1dDE2c3px/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast) 然后对于查询的也是同理，对于第三种情况也是取全部的然后减去最深点下面那块的。 至于取出那个最深点，就从$rt$开始向上跳链，然后找到与$maxdeep(lca(u,rt),lca(v,rt))$深度相同的点即可。