---
title: " 雅礼集训Day6\t\t"
url: 1258.html
id: 1258
categories:
  - 笔记
date: 2018-03-28 20:59:54
tags:
---

容斥原理
----

### 二项式反演

*   $b\_k=\\sum\_{i=0}^{k}\\binom{k}{i}a_i$
*   $\\Rightarrow a\_k=\\sum\_{i=0}^{k}(-1)^{k-i}\\binom{k}{i}b_i$
*   $b\_k=\\sum\_{i=k}^{n}\\binom{i}{k}a_i$
*   $\\Rightarrow a\_k=\\sum\_{i=k}^{n}(-1)^{i-k}\\binom{i}{k}b_i$

### 广义容斥原理

设有与性质$1,2,3,…,n$相关的元素$m$个，$A\_i$为满足第$i$种性质的所有元素的集合。 定义$P\_k$为至少有$k$种性质的元素的元次，则有 $$P\_k=\\sum\_{I\\in C(n,k)}|\\bigcap_{i\\in I}A\_i|$$ 定义$Q\_k$为正好有$k$种性质的元素的个数，则有 $$Q\_k=\\sum\_{I\\in C(n,k)}|(\\bigcap_{i\\in I}A\_i)\\bigcap (\\bigcap\_{i\\in \\bar{I}}\\bar{A\_i})|$$ $$Q\_k=\\sum_{k\\leqslant i\\leqslant n}(-1)^{i-k}\\binom{i}{k}P_k$$