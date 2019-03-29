---
title: " DTOJ3602Kayaking Trip\t\t"
tags:
  - 二分
  - 贪心
url: 1399.html
id: 1399
categories:
  - DTOJ
  - Solution
  - 不会证
date: 2018-04-11 07:29:32
---

显然要二分答案。二分答案$mid$后，记$a\_i=\\lfloor \\frac{ans}{c\_i}\\rfloor$。那么问题就变成了有$b$个$s\_b$，$n$个$s\_n$，$e$个$s\_e$，两两组合出$b\_i$，使得$\\forall i\\in\[1,\\frac{b+n+e}{2}\]$，都有$a\_i\\leqslant b\_i$。 考虑贪心。将$a\_i$从大到小排序后，一个一个组合出$b\_i$。每次从剩下的数中选出最小的$\\geqslant a\_i$的组合，若没有$\\geqslant a\_i$的组合即无解。 贪心不是很会证。