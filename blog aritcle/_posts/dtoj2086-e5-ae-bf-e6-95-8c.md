---
title: " DTOJ2086宿敌\t\t"
tags:
  - dp
url: 1919.html
id: 1919
categories:
  - DTOJ
  - Solution
date: 2018-05-10 14:46:33
---

显然修改成单调不增和单调不减是类似的，我们只考虑修改成单调不减的情况。 如果$m\_1=m\_2$，那么就只用求要修改几个位置，求出最长不降子序列的长度$m$，要修改的位置就是$n-m$个。 但是这题修改的代价不同。注意到题目给了一个奇怪的限制：不同的实力值不会超过$1000$个，这意味着我们的解法可能和实力值个数有关。 我们将实力值离散化后，很容易想到一个dp：记$f\[i\]\[j\]$为前$i$个人单调不减，且第$i$个人实力值（离散后的）$\\leqslant j$的最小代价。 转移也很简单 $$f\[i\]\[j\]=min\\{f\[i\]\[j-1\],f\[i-1\]\[j\]+cost(p_i,j)\\}$$ 其中$cost(a,b)$是将$a$改成$b$的代价。 觉得空间太大还能把第一维滚掉。