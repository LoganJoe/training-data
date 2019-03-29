---
title: " DTOJ3177影魔\t\t"
tags:
  - 线段树
url: 5733.html
id: 5733
categories:
  - Solution
date: 2018-12-23 11:58:25
---

考虑题目中限制的含义。对于当前区间$\[l,r\]$假设$l,r$分别是区间最大值和次大值的时候，则会产生$p\_1$的贡献，否则假设其中有一个是最大值而另外一个不是次大值则会产生$p\_2$的贡献。 那么我们考虑当前一个点会对那部分有贡献。当$k\_i$是$\[l,r\]$最大值的时候，就会对\[l,r\]$中的所有点对产生一次贡献。 由于$k\_i$是一个排列，我们可以用单调栈求出$i$左边第一个比$k\_i$大的位置和右边第一个比$k\_i$大的位置。 然后这时，$k\_i$会对于$\[L\_i,R\_i\]$产生$p\_1$的贡献，对于$\\forall x \\in (i,R\_i),\[L\_i,x\]$，$\\forall x \\in(L\_i,i) ,\[x,R\_i\]$产生$p_2$的贡献。 将每个点带来的贡献放到二维平面上考虑。那么每个点的贡献就是一条线段。而查询这是要求一个矩形内的贡献和。 可以离线以后扫描线+线段树解决。