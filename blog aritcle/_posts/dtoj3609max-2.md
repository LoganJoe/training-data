---
title: " DTOJ3609max\t\t"
tags:
  - 状压dp
url: 6367.html
id: 6367
categories:
  - Solution
date: 2019-02-07 11:00:39
---

欺诈题。$m$较小，不妨考虑有哪几个操作对当前这个数有贡献。记$f(i,S,j)$为$A_i$被$S$集合中操作以后，值为$j$的概率：枚举当前$S$以及多选了哪个操作，增长的数$l$转移： $$ f(i,s|2^{k-1},j+l)\\Leftarrow f(i,S,j)\\times A(k,i,l) $$ 记$g(i,j,S)$为前$i$个元素最大值为$j$,还剩下$S$集合中操作没使用的概率。枚举$S$的子集$T$，以及当前这个数的值： $$ g(i,S\\oplus T,\\max (j, l)) \\Leftarrow g(i-1,S,j) \\times f(i,T,l) $$ 效率$O(n(cm)^23^m)$