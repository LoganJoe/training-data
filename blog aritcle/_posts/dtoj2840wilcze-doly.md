---
title: " DTOJ2840Wilcze doly\t\t"
tags:
  - 单调队列
url: 4516.html
id: 4516
categories:
  - Solution
date: 2018-10-24 22:21:28
---

首先可以想到，每次删掉长度为$d$的最优。 考虑一段区间$\[l::r\]$，其中$r-l>d$。我们要找到一个位置$pos$，满足$pos \\in \[l,r-d+1\]$，有$Sum(l::r)-Sum(pos::pos+d-1)$最小。那么对于确定的$\[l::r\]$，要使得$Sum(pos,pos+d-1)$最大。 那么我们可以枚举$r$，单调推出$l$。随着$r$的后移，可以用单调队列维护最优的$pos$的位置，也就可以得到$Sum(pos::pos+d-1)_{min}$。那么合法的仅当$sum\[r\]-sum\[l\]-Sum(pos::pos+d-1)\\leq p$。然后一直向右推$l$直到这段区间满足条件为止。