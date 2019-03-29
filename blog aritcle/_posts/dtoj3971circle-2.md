---
title: " DTOJ3971circle\t\t"
tags:
  - 倍增
  - 最短路
url: 4761.html
id: 4761
categories:
  - Solution
date: 2018-10-29 19:55:52
---

我原本有一个枚举每条边然后跑一遍的做法。 然后它被无情的卡掉了。 正解是倍增floyd。 $dis(i,u,v)$是从$u$走到$v$，在$2^i$步内所能走出的最大权值。 于是我们对于邻接矩阵用floyd的方法做倍增，直接按倍增的方法跑出答案。