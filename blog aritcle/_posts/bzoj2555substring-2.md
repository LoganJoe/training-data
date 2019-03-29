---
title: " BZOJ2555substring\t\t"
tags:
  - Link-Cut Tree
  - 后缀自动机
url: 6764.html
id: 6764
categories:
  - Solution
date: 2019-03-03 14:53:27
---

注意到，假设没有添加操作，那么其实就是相当于维护SAM上right集合的大小。 考虑添加字符串以后，实际操作就是对于原有的parent树，改变一下某些点的父亲，将新点挂上去。 因为right集合大小实际上是parent树上这个点子树中代表结尾的结点个数。因此我们就是要动态维护树上每个点的子树信息。那么我们用LCT直接维护parent树及其的right集合就好了。