---
title: " DTOJ3523环线\t\t"
tags:
  - 分治
  - 矩阵
url: 649.html
id: 649
categories:
  - DTOJ
  - Solution
date: 2018-02-17 20:14:47
---

用$A\_1\[i\]\[j\]$表示初始的邻接矩阵。 令$A\_p=A\_1^p$。 显然$A\_p\[i\]\[j\]$为$i$到$j$经过$p$步的方案数。 令$Ans\_p=\\sum\_{i=1}^{p}A\_i$。 显然答案是$\\sum\_{i=1}^{n}Ans\_k\[i\]\[i\]$，即$k$步之内从$i$到$i$的方案数。 考虑如何快速地求$Ans\_k$。

1.  如果$k$为偶数$$Ans\_k=\\sum\_{i=1}^{k}A\_i=\\sum\_{i=1}^{\\frac{k}{2}}A\_i+A^{\\frac{k}{2}}(\\sum\_{i=1}^{\\frac{k}{2}}A\_i)=(A^{\\frac{k}{2}}+1)Ans\_{\\frac{k}{2}}$$
2.  如果$k$为奇数$$Ans\_k=\\sum\_{i=1}^{k}A\_i=\\sum\_{i=1}^{\\lfloor \\frac{k}{2}\\rfloor}A\_i+A^{\\lfloor \\frac{k}{2}\\rfloor}(\\sum\_{i=1}^{\\lfloor \\frac{k}{2}\\rfloor}A\_i)+A^k=(A^{\\lfloor \\frac{k}{2}\\rfloor}+1)Ans\_{\\lfloor \\frac{k}{2}\\rfloor}+A^k$$

分治求解即可。