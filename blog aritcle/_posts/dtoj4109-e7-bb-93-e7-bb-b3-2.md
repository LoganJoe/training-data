---
title: " DTOJ4109结绳\t\t"
tags:
  - NTT
  - 分治
  - 容斥
url: 6279.html
id: 6279
categories:
  - DTOJ
  - Solution
date: 2019-01-28 16:50:08
---

此题为[DTOJ4085圈圈圈圈圈圈圈圈圈圈圈圈](http://www.dtenomde.com/author=jiangyutong/article=5718/)加强版。 我们先不考虑种类的限制。 记$Sum=\\sum_{i=1}^{n}s\_i$。 如果$Sum$为奇数，答案一定是$0$。 考虑$Sum$为偶数的情况。 记$i$个结匹配的方案数为$f\[i\]$。 那么有 $$ f\[i\]=f\[i-2\](i-1) $$ 总方案数就是$f\[Sum\]$。 再考虑把有同种类匹配的方案扣掉。 假设选$i$对同种类出来的方案数为$g\[i\]$，那么答案就是 $$ \\sum\_{i=0}^{\\frac {Sum}2}(-1)^i\\cdot f\[Sum-2i\]\\cdot g\[i\] $$ 考虑如何求$g\[i\]$。 对于某个种类$s\_i$，选$i$对出来的方案数就是$\\binom{s\_i}{2i}$。 记多项式$A\_i(x)=\\sum\_{i=0}^{\\left \\lfloor \\frac{s\_i}{2}\\right \\rfloor}\\binom{s\_i}{2i}x^i$，也就是选$i$对出来的方案数的生成函数。 那么对于所有种类，一共选$i$对同种类出来的方案数，就是$\\prod_{i=1}^{n}A\_i(x)$中$x^i$前的系数。 $\\prod\_{i=1}^nA_i(x)$显然可以用分治NTT求出。 时间复杂度$\\Theta(n\\log ^2n)$。