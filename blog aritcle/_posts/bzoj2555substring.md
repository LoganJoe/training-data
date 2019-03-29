---
title: " BZOJ2555SubString\t\t"
tags:
  - Link-Cut Tree
  - 后缀自动机
url: 6718.html
id: 6718
categories:
  - BZOJ
  - Solution
date: 2019-02-28 19:35:42
---

我们考虑建出字符串的后缀自动机。 由于SAM的构造是增量法，是可以在线不断加字符的。 考虑询问。 我们找到SAM中表示字符串$s$的结点，那么答案就是这个点的$right$集合大小。 考虑如何动态维护每个点的$right$集合大小。 $right$集合大小实际上是parent树上这个点子树中代表结尾的结点个数。因此我们就是要动态维护树上每个点的子树信息。 使用维护子树信息的LCT动态维护parent树即可。将子树求和变成链加单点查询也可以，这样的LCT就不用维护子树信息了。