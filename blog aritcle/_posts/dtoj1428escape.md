---
title: " DTOJ1428Escape\t\t"
tags:
  - 最大流
url: 511.html
id: 511
categories:
  - Solution
date: 2018-02-04 20:58:53
---

只要有缝，就可以过去。 那么我们将每个士兵拆成i与i+n两个点，范围与上界有相交或者相切的由S向i连一条容量为inf的边，与下界有相交的由i+n向T连一条容量为inf的边，士兵之间有相交则由i+n向j连一条容量为inf的边。最后每个士兵，从i向i+n连一条容量为1的边以后跑最大流求出最小割就可以了。这个画个图意会一下即可。