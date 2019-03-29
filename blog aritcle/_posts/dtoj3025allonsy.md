---
title: " DTOJ3025allonsy\t\t"
tags:
  - 概率
url: 3498.html
id: 3498
categories:
  - Solution
date: 2018-08-18 11:05:33
---

我们枚举走的情况。枚举向右走了$i$步，那么概率为

$q^i \\times (1-q)^(n-i) \\times \\binom{n}{i}$

离终点距离为$|n-2*i|$

枚举i计算答案。