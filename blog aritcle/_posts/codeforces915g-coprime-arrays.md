---
title: " Codeforces915G Coprime Arrays\t\t"
tags:
  - 数论
url: 5187.html
id: 5187
categories:
  - Codeforces
  - Solution
date: 2018-11-18 11:10:36
---

### 题意

给两个数$n,k$，对于$\\forall i\\in\[1,k\]$，求出长度为$n$且每个数$\\leq i$的序列中，满足所有数的$gcd=1$的个数。

### 题解

记$i$的答案为$ans\_i$。 所有的序列个数是$i^n$，我们要减去不合法的个数。 我们枚举序列所有数的$gcd$，计算此时的序列个数。根据一些数论知识可以知道 $$ ans\_i=i^n+\\sum_{g=2}^{i}\\left \\lfloor \\frac{i}{g}\\right \\rfloor ^n\\times \\mu(g) $$ 直接算是$\\Theta(k^2)$的，就算用整除分块优化也是$\\Theta(k\\sqrt{k})$的。 我们反着考虑，考虑每个$g$对每个$ans\_i$的贡献。 对于一个$g$，它给$i\\in\[g,2g)$的$ans\_i$贡献为$1^n\\times \\mu(g)$，给$i\\in\[2g,3g)$的$ans\_i$贡献为$2^n\\times \\mu(g)$。依次类推，给$i\\in\[tg,(t+1)g)$的$ans\_i$贡献就是$t^n\\times \\mu(g)$。 容易发现，一个$g$的贡献都是很多段长度为$g$的区间，那么我们可以在区间端点打上差分标记，最后前缀和一下就能算出$ans_i$。 所有$g$的最大的$t$的和，根据调和级数可知，是$k\\log k$级别的。 因此时间复杂度为$\\Theta(k\\log k)$。