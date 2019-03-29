---
title: " DTOJ1299数学作业\t\t"
tags:
  - 矩阵
url: 3307.html
id: 3307
categories:
  - DTOJ
  - Solution
date: 2018-08-05 22:13:11
---

用递推很容易得到答案。 具体地，记$ans\_i$为当$N=i$时的答案，那么显然有 $$ans\_i=(ans_{i-1}\\times 10^k+i)\\%M$$ 其中，$k$是$i$的位数。 但是$N$很大，我们不能$\\Theta(N)$递推。 这种递归式几乎都可以用矩阵快速幂来优化。 比较麻烦的是$k$是会变的。 由于$N\\leqslant 10^{18}$，所以$k\\leqslant 18$，那么我们枚举$k$，分段进行矩阵快速幂即可。