---
title: " DTOJ3617Faulty Factorial\t\t"
tags:
  - 数学
url: 1404.html
id: 1404
categories:
  - DTOJ
  - Solution
date: 2018-04-12 07:28:20
---

发现$n$很大而$p$较小，$n$的阶乘肯定无法直接求，直接考虑求$\\%p$余数。发现当$n\\geqslant p$时，$n!\\%p=0$。因此可以分情况讨论。

1.  $n\\geqslant 2p$。$r>0$无解；$r=0$随便找个数换。
2.  $p\\leqslant n<2p$。$r>0$要把$p$换掉，可以枚举换成什么数来判断是否有解；$r=0$可以随便换一个除了$p$之外的数。注意当$n=2,p=2,r=0$时无解。
3.  $n<p$。假设我们要把$x$换成$y(0<y<x)$，那么需要满足$$n!\\times \\frac{y}{x}\\equiv r(mod\\space p)$$即$$y\\equiv rx\\frac{1}{n!}(mod\\space p)$$因此我们可以枚举$x$，算出$y$看是否满足条件。