---
title: " DTOJ3516attack\t\t"
tags:
  - dp
  - 斯特林数
url: 444.html
id: 444
categories:
  - DTOJ
  - Solution
  - 不会证
date: 2018-01-31 21:55:11
---

这题其实我也很懵，强行看题解理解的。所以就直接贴吧… ![](http://www.dtenomde.com/wp-content/uploads/2018/01/3182A71A-B1CC-4D30-B344-8C42CD15D20F.jpg) ![](http://www.dtenomde.com/wp-content/uploads/2018/01/62A52F9A-545A-4D1F-9A2E-1A26B485EA5F.jpg) 大致就是巧妙的dp计算方案，因为相同类型的国家是等价的，所以先把所有国家看成无标号的。计算完方案再换成有标号的。 列表其实就是每场战争的进攻方和失败方，若没有填失败方则意味着防守成功。组合数就是在剩下空着的$cnt1$个失败方放$cnt2$个的方案数。最后的$(N-1)^{cnt1-cnt2}$意味着有$cnt1-cnt2$场战争防守成功，每场战争的防守方可以是除了进攻方的任意一个国家。 $S(n,m)$是第二类斯特林数。