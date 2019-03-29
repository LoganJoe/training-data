---
title: " BZOJ2688Green Hackenbush\t\t"
tags:
  - 博弈
  - 树形dp
  - 概率dp
url: 6287.html
id: 6287
categories:
  - BZOJ
  - Solution
date: 2019-02-01 15:43:25
---

树上切边游戏是一种博弈模型，一棵树的$SG$值为所有儿子的$SG$值$+1$后的异或和。 显然每棵树是独立的，每棵树的$SG$值的异或和就是整个游戏的$SG$值。 考虑求游戏$SG$值为$0$的概率，然后用$1$去减就是答案了。 我们考虑dp。 记$C\_i$为$i$个点的不同的二叉树数量，也就是卡特兰数。 记$f\[i\]\[j\]$为$i$个点的树，$SG$值为$j$的概率。 我们枚举左右子树的大小和$SG$值即可转移。 具体地，有 $$ \\frac{2C\_i\\times f\[i\]\[j\]}{C_{i+1}}\\Rightarrow f\[i+1\]\[j+1\] $$ 表示左子树或右子树为空的转移。 还有 $$ \\frac{C\_i\\cdot f\[i\]\[k\]\\times C\_{j} \\cdot f\[j\]\[l\]}{C_{i+j+1}}\\Rightarrow f\[i+j+1\]\[(k+1)\\oplus (l+1)\] $$ 表示左右子树都不为空的转移。其中$\\oplus​$表示异或。 我们再把$n$棵树合并起来。 记$g\[i\]\[j\]$为前$i$棵树$SG$值的异或和为$j$的概率。 那么有 $$ g\[i\]\[j\]\\times f\[a_{i+1}\]\[k\]\\Rightarrow g\[i+1\]\[j\\oplus k\] $$ 其中$\\oplus$表示异或。 最后$1-g\[n\]\[0\]$就是答案。 什么？你说$C_i$太大会爆long long？ 没关系，相信double是万能的（雾）。