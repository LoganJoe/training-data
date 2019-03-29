---
title: " DTOJ2263诸神眷顾的梦幻乡\t\t"
tags:
  - 后缀自动机
url: 3768.html
id: 3768
categories:
  - DTOJ
  - Solution
date: 2018-08-30 18:14:24
---

注意一个性质：只与一个空地相邻的空地的数量不超过$20$个。 我看成了每个点的度数$\\leq 20$…… 这个性质告诉我们叶子节点的数量$\\leq 20$。 我们以某个叶子节点为根，然后可以建出一棵Trie树，那么每种颜色序列都是Trie树中从上到下的一段。 我们最多可以建出$20$棵Tire树，我们要统计这$20$棵Trie树中不同的子串个数。 我们可以将$20$棵Tire数合并成一棵大Tire树，然后统计这棵大Tire树不同的子串个数。 考虑SAM。插入每个点的时候，$last$为它的父亲在SAM中的点。 那么答案就是每个点的$max$的和减去每个点$parent$的$max$的和。 听说这个叫广义SAM……