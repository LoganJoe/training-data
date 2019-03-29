---
title: " DTOJ3990迷宫\t\t"
tags:
  - 无标签
url: 5062.html
id: 5062
categories:
  - Solution
date: 2018-11-05 23:07:00
---

这个数据范围一眼就是meet in the middle的题。 一共可以走$n+m-2$步，从里面抽出$n-1$步向下走。求最后异或和为$k$的方案数。 那么这个东西很容易meet in the middle。发现一定会穿过一条对角线，那么我们从起点到终点分别走到对角线就好了。 那么一侧的方案为$k$，我们要在另外一半中匹配所有走到这个点，方案为$k\\oplus x$的数量。这个可以分类后two_point解决。