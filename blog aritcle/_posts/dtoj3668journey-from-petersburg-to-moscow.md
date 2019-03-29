---
title: " DTOJ3668Journey from Petersburg to Moscow\t\t"
tags:
  - 思路
  - 最短路
url: 1679.html
id: 1679
categories:
  - DTOJ
  - Solution
date: 2018-04-24 14:44:53
---

先考虑经过的边数$\\geqslant k$的情况。 枚举第$k$条边的权值$x$，将所有边的权值$w$改成$max(w-x,0)$，然后跑一遍$1$到$n$的最短路，用$dist\[n\]+kx$更新答案。如果经过的原边权$\\geqslant x$的边数小于$k$，$x$减小答案不会更劣；如果经过的原边权$\\geqslant x$的边数大于$k$，$x$增大答案不会更劣。因此一定存在一个$x$能求出最优解。 如果经过的边数$<k$，那么直接跑一遍$1$到$n$的最短路即可。