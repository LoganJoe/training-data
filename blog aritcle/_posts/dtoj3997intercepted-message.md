---
title: " DTOJ3997Intercepted Message\t\t"
tags:
  - 无标签
url: 5211.html
id: 5211
categories:
  - Solution
date: 2018-11-21 21:35:03
---

容易想到的是对于一对划分的切点$i,j$，满足$SumA\_i=SumB\_j$。其中$SumA,SumB$为两数组前缀和。证明不难想到，就是前面的部分也是每段对应相等，那么这个条件就是充要的了。 然后贪心跳。对于两个数列$two_{}pointer$。每次对于前缀和比较小的那个向后推。很容易证明这个贪心是对的。