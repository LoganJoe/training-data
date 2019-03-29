---
title: " DTOJ3842yist\t\t"
tags:
  - 分块
url: 3085.html
id: 3085
categories:
  - DTOJ
  - Solution
date: 2018-07-27 16:41:33
---

先考虑如何判断$-1$。即判断答案是否可能无限大。 这个还是很好判断的，对于一个点，如果它被操作了，且与它有连边的点中有没被操作的权值$>0$的点，答案就是无限大的，因为每次答案都至少会增加那个点的权值。 然后我们开始考虑如何计算答案。 记第$i$个点在$s$序列中出现了$cnt\_i$次。 我们扫一遍序列，假如当前这个点是$x$，记$y$是与$x$相邻的点，那么这一次$y$会给答案带来的贡献记为$v$。那么再进行$k$次操作，也就是一轮过去，$y$会给答案带来的贡献就是$\\frac{v}{2^{cnt\_y}}$。那么每对点对答案的贡献都是一个等比数列，可以直接用等比数列求和公式来算。 但如果序列里每个点度数都很大的话，这样子枚举点对就会超时了。 但由于所有点的度数和是$2m$，因此度数大的点不会很多。我们将序列里的点按$\\sqrt{n}$将点分为两类。（其实我也不知道取什么根号是最优的…不会算）

*   度数$\\leqslant \\sqrt{n}$的点。每次枚举相邻点算答案。
*   度数$\> \\sqrt{n}$的点。显然这样的点不会超过$\\frac{2m}{\\sqrt{n}}$个。记这个点会给答案带来的贡献为$val$，那么我们就是要维护最多$\\frac{2m}{\\sqrt{n}}$个$val$。我们可以在枚举序列里的点时顺便维护，先预处理出每个点和哪些这类点有连边，当一个点的权值$\\div 2$后，更改会影响到的这类点的$val$即可。

时间复杂度$\\Theta(K\\sqrt{n})$，可能常数会有点大。