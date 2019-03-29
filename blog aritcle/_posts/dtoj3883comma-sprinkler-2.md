---
title: " DTOJ3883Comma Sprinkler\t\t"
tags:
  - 并查集
url: 3894.html
id: 3894
categories:
  - Solution
date: 2018-09-09 19:31:51
---

暴力啊。

记一下这个单词上次出现的位置，然后用并查集维护，将相同的单词连在一起。这样就可以得到每个位置是否要加逗号。

用map判定。句号就mark判定一下。