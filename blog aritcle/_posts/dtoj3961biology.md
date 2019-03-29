---
title: " DTOJ3961biology\t\t"
tags:
  - hash
  - 二分
url: 4098.html
id: 4098
categories:
  - Solution
date: 2018-10-06 19:35:17
---

谁能告诉我为什么难度倒序。

好像题目有点唬人。看到后缀自然想到SAM。

然后发现这就是求$T$个串的最长公共后缀。将所有串reverse一下就是求最长公共前缀了。

这个东西怎么写？二哈分析二分哈希啊！

$T$就到$10$，于是我们可以直接二分答案然后hash判定就好了。

hash值用vector存起来。