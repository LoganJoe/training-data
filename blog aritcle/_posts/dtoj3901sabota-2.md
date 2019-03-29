---
title: " DTOJ3901Sabota\t\t"
tags:
  - 树形dp
url: 3907.html
id: 3907
categories:
  - Solution
date: 2018-09-09 21:35:03
---

设$f\[i\]$为无法使$i$的子树中所有人都变成叛徒的最小$x$。那么就有

$$f\[x\]=\\max_{v}\\left\\{min(f\[v\],\\frac{Size\[v\]}{Size\[x\]-1})\\right\\}$$

答案是所有满足$size>k$的点$f$的最小值。