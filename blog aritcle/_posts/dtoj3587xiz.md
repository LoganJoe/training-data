---
title: " DTOJ3587xiz\t\t"
tags:
  - hash
url: 1314.html
id: 1314
categories:
  - DTOJ
  - Solution
date: 2018-04-04 15:38:26
---

一个很巧妙的转换。 记串中每个字符和前一个这个字符的距离为$d\_i$。那么可以发现，如果两个串的$d$数组相同，那么这两个串就可以匹配了。 那么问题就变成了$S$串的$d$数组和$T$串的$d$数组匹配。 这个我们可以用hash来做。 先预处理出$S$串和$T$串的$d$数组。 然后求出$T$串的$d$的hash值，枚举$S$串中的位置作为匹配开头，计算出hash值。 容易发现匹配开头向后移动一位时，只有两个位置的$d\_i$会发现变换，重新计算一下这两个位置对hash值的贡献即可。 听说KMP也能做，但不是很懂。