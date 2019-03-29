---
title: " DTOJ1231 Count on a tree\t\t"
tags:
  - 可持久化线段树
url: 467.html
id: 467
categories:
  - Solution
date: 2018-02-04 12:47:24
---

看到“第k小”，我们可以想到主席树。 如何把主席树放到树上？我们对于一个点，以他的父亲节点对应的主席树作为历史版本构建一棵树。 那么要查询一条链（u，v）上的第k小，就可以利用树上前缀和思想，树链上值k的数目tot可以表示为：

$tot=u.tot+v.tot-lca.tot-\[lca.fa\].tot$

其中，a.tot表示树根到a点的值k的数目。lca为u,v两点的最近公共祖先。 那么剩下的操作就与K-th Number无异了。