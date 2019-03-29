---
title: " Codeforces741D Arpa’s letter-marked tree and Mehrdad’s Dokhtar-kosh paths\t\t"
tags:
  - Dsu on tree
url: 969.html
id: 969
categories:
  - Codeforces
  - Solution
date: 2018-03-08 13:19:09
---

显然题目要求的链上出现次数为奇数次的字母种类数只能为$0$或$1$。 把每个点到根的路径上字母的出现状态状压起来，记为$val\[x\]$。某一位为$0$意味着出现了偶数次，为$1$意味着出现了奇数次。那么我们就是要找两个点$a$和$b$，使得$val\[a\]\\space xor\\space val\[b\]$为$0$或者只有一位为$1$，且$deep\[a\]+deep\[b\]-2deep\[lca\]$最大。 用$f\[i\]$表示当前点的子树内，$val$为$i$的点最深的深度。 然后就可以用Dsu on tree的技巧。 先继承儿子的信息，然后算出以当前为端点和$lca$的答案。轻儿子暴力更新和清空，重儿子保留。 由于得保证从$lca$走下去的两条链不能在同一子树内，所以我们对于每一个儿子，先更新答案，再更新信息。 然而这样会超时。 发现我们多次遍历子树。每次都用dfs遍历的话常数太大，先预处理出dfs序然后扫一遍dfs序上的区间即可，常数优化显著。