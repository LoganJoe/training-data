---
title: " DTOJ1641交换棋子\t\t"
tags:
  - 二分图
url: 1490.html
id: 1490
categories:
  - DTOJ
  - Solution
date: 2018-04-15 15:00:54
---

如果每行每列都有一个棋子，那么肯定可以通过交换构出解。 那么问题就变成了判断是否每行每列都有一个棋子。 这显然是一个匹配问题。建出代表行的$n$个点和代表列的$n$个点，对于一个在位置$(x,y)$的棋子，行的$x$点和列的$y$点连一条边，代表第$x$行可以和第$y$列匹配。 用匈牙利算法求出最大匹配，最大匹配为$n$就有解，否则无解。