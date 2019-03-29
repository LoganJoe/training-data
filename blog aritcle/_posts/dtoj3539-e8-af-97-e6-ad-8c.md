---
title: " DTOJ3539诗歌\t\t"
tags:
  - hash
url: 909.html
id: 909
categories:
  - DTOJ
  - Solution
date: 2018-03-05 18:55:09
---

为DTOJ1729等差子序列的加强版。 首先枚举一个位置$j$，然后判断是否有$i,k$满足$H\_i+H\_k=2H\_j$，即是否有合法解。 我们维护在$j$左侧出现过的高度序列$s$，$s\[i\]=1$表示高度为$s\[i\]$的山在位置$j$的左侧。 如果存在一个$x$，使得$H\_j-x$在位置$j$的左侧，$H\_j+x$在位置$j$的右侧（$x$可以为负数），那么就一组合法解。而这种情况是$s\[H\_j-x\]=1,s\[H\_j+x\]=0$。 那么如果序列$s$中以$H\_j$为中心的极长子串是一个回文串的话，那么说明满足的$H\_i$和$H\_k$都在位置$j$的同一侧出现，也就是没有合法解。 判断回文串可以用hash，用树状数组或线段树动态维护$s$的hash值和$s$翻转后的hash值即可。