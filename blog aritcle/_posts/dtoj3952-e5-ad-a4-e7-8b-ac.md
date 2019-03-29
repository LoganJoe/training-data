---
title: " DTOJ3952孤独\t\t"
tags:
  - 容斥
  - 思路
url: 4064.html
id: 4064
categories:
  - DTOJ
  - Solution
date: 2018-10-23 18:08:53
---

我们考虑枚举$K$天的同学的话题的与的子集$x$，记话题包含$x$的同学有$cnt$个，那么方案数就是$cnt^K$。 根据容斥原理，答案就是$\\sum_{i=1}^{2^n-1}(-1)^{k+1}cnt\_i^K$，其中$k$是$i$二进制位上$1$的个数。 那么现在的问题就是如何求出所有的$cnt\_i$。 每个$A\_i$会对$A\_i$每个真子集的$cnt$造成$+1$的贡献。而一个数的真子集一定是在这个数的二进制位上去掉某些$1$得到的数。 初始$cnt\_i$为$A\_j=i$的$j$的个数。我们考虑每次去掉某个$1$来转移。但是这样会算重。 因为$x\\rightarrow x\\oplus i\\rightarrow x\\oplus i\\oplus j$和$x\\rightarrow x\\oplus j\\rightarrow x\\oplus j\\oplus i$是两种转移路径，这说明$cnt\_x$对$cnt\_{x\\oplus i\\oplus j}$的贡献会算两次。其中$\\oplus$表示异或。 只要按位转移就不会重复计算了。 假如我们现在枚举到第$i$位，如果$x$的第$i$位上为$1$，那么就由$cnt\_x$转移到$cnt\_{x\\oplus 2^i}$。 这样转移路径就是唯一的（因为其中一种一定不合法），所以贡献只会算一次。