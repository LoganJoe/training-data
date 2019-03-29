---
title: " DTOJ2392Can\t\t"
tags:
  - 分治
url: 382.html
id: 382
categories:
  - DTOJ
  - Solution
date: 2018-01-23 14:59:30
---

注意到$D\\leqslant 4$，$2\\leqslant k\\geqslant 3$。 考虑分治。 对于区间在$\[l,r\]$内的答案，只在$\[l,mid\]$或$(mid,r\]$的答案我们分治解决。现在考虑跨越$mid$的答案。 先枚举$mid$要选哪一个数，再尽量向两边拓展。拓展到无法拓展我们继续新选一个数，直到选的数的数量$>k$。然后用当前区间更新答案。 效率是$O(D^k2^{k-1}nlogn)$，最优性剪枝减一下差不多能过。