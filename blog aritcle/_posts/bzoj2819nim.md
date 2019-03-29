---
title: " BZOJ2819Nim\t\t"
tags:
  - 无标签
url: 6228.html
id: 6228
categories:
  - BZOJ
  - Solution
date: 2019-01-26 23:25:50
---

我们要维护路径的异或和，并且要支持修改点权。 用树链剖分可以做到$\\Theta(n\\log ^2 n)$。 但是没有必要。 我们对于每个点，维护它到根的路径异或和。 修改就是子树对应的区间异或上某个数。 询问$a,b$就查询点$a,b,LCA(a,b)$和$fa\[LCA(a,b)\]$的信息即可。 容易用树状数组实现。 时间复杂度$\\Theta(n\\log n)$。