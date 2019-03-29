---
title: " DTOJ2935询问\t\t"
tags:
  - 线段树
url: 2808.html
id: 2808
categories:
  - DTOJ
  - Solution
date: 2018-07-18 20:57:41
---

答案不好直接求，我们考虑二分答案$mid$，然后将问题变成前$mid$个回答会不会有矛盾。 注意到一个十分关键的条件：序列中元素两两不同。 那么如果两个不相交区间有着相同的最小值，一定是矛盾的。 如果有一个最小值较大的区间包含了一个最小值较小的区间，也是矛盾的。 按最小值从大到小给回答排序。扫一遍回答，如果当前的区间被之前的区间的并完全包含，那么就是矛盾的。 注意最小值相同的区间我们要先合并起来，也就是取交集。此时才有最小值在合并完的区间内。所以要拿合并完的区间去查询。 那么就是区间覆盖和区间查询的操作，用线段树实现即可。