---
title: " DTOJ3871game\t\t"
tags:
  - FFT
  - 点分治
url: 3773.html
id: 3773
categories:
  - Solution
date: 2018-08-30 18:51:46
---

和“每次随机选择一个点，将所在联通块捶一遍，删除该点及其连边”是等价的。

于是我们发现，答案相当于每个点被删掉的时候，其他点被锤的概率之和。

那么当$i$被删的时候$j$能被锤，一定是$i$被删的时候$i$到$j$的路径上没有点被删。

那么，删除$i$时$j$被锤的概率就是$\\frac{1}{dist(i,j)}$。

直接做树形dp是$O(n^2)$的，我们可以点分治，然后合并的时候$FFT$优化。