---
title: " BZOJ2216[Poi2011]Lightning Conductor\t\t"
tags:
  - 决策单调性
  - 分治
url: 2462.html
id: 2462
categories:
  - BZOJ
  - Solution
date: 2018-06-15 22:15:30
---

记$f\[i\]=max_{j=1}^{n}\\{a\_j+\\sqrt{|i-j|}\\}$。那么$f\[i\]-a\_i$就是答案。 考虑如何求$f\[i\]$。 我们先把绝对值拆开，两种情况是类似的。现在只考虑$f\[i\]=max_{j=1}^{i-1}\\{a_j+\\sqrt{i-j}\\}$的情况。 观察一下可以发现，这个满足决策单调性。 那么用分治就可以求出所有的$f$了。然后把数组反过来再求一次。综合两次就能得到答案了。