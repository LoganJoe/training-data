---
title: " DTOJ2594字符串\t\t"
tags:
  - 思路
url: 4042.html
id: 4042
categories:
  - Solution
date: 2018-09-23 16:05:30
---

首先枚举重复串的长度$len$。

考虑两个重复串，其一定会经过$\[k\*len,k\*len+len\]$这段。

于是我们可以$O(\\frac{N}{len}log \ N)$计算两个相邻$\[k\*len,k\*len+len\]$的$LCP$和$LCS$长度。如果有$LCP+LCS > len$，那么说明这里存在一个$len$的重复串。那么我们用hash判断相等,二分计算$LCP$与$LCS$长度，同时对于找到的重复串，用$O(n)$的时间删去所有重复串并且rebuild hash数组。

由于合法的字符串长度衰减的很快，效率其实是$O(n log ^2 n)$的。因为可以证明经过$log$步削减到1，而这个$log$和第一个$log$是同阶的。