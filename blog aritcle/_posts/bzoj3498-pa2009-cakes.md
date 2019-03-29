---
title: " BZOJ3498 PA2009 Cakes\t\t"
tags:
  - 思路
url: 6771.html
id: 6771
categories:
  - Solution
date: 2019-03-03 14:54:51
---

考虑这是简单的三元环计数。 我们可以对于每个点按照编号排序，每条边算在度数小的那个点上。 之后枚举一条边，two-pointer的枚举两个端点的出边。对于每个枚举到的三元环计算相应贡献即可。