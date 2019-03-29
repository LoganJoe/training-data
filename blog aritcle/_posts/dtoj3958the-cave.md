---
title: " DTOJ3958The Cave\t\t"
tags:
  - 思路
url: 4609.html
id: 4609
categories:
  - DTOJ
  - Solution
date: 2018-10-26 13:11:03
---

我们先把$1$号点作为答案。 假设不满足第$i$条限制，也就是说$dist(1,a\_i)+dist(1,b\_i)>d\_i$，那么我们至少要到$LCA(a\_i,b\_i)$向上走$\\left \\lfloor \\frac{d-dist(a\_i,b\_i)}{2}\\right \\rfloor$的位置才能满足这条限制。 我们找到最大的那条限制，即$\\left \\lfloor \\frac{d-dist(a\_i,b\_i)}{2}\\right \\rfloor$最大的限制，然后找这条限制的$LCA(a\_i,b\_i)$向上走$\\left \\lfloor \\frac{d-dist(a\_i,b_i)}{2}\\right \\rfloor$的点作为答案。记为$x$。 如果有解，则$x$一定可行，否则就无解了。稍微证明一下。

*   对于$a\_i,b\_i$都在$x$子树里的限制，一定可行。因为我们是根据最大的限制来求的$x$。
*   对于$a\_i,b\_i$一个在$x$子树内，一个在$x$子树外的限制，说明$x$在$a\_i$到$b\_i$的链上，显然不能再优了。
*   对于$a\_i,b\_i$都在$x$子树外的限制，$x$深度越小越好。但如果$x$再往上走的话，就满足不了最大的那条限制了。

那么我们求出$x$，再判断一下是否满足所有限制即可。