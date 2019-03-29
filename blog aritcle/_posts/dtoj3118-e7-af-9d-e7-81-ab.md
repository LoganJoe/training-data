---
title: " DTOJ3118篝火\t\t"
tags:
  - 思路
  - 树形dp
url: 1821.html
id: 1821
categories:
  - DTOJ
  - Solution
date: 2018-04-30 16:11:27
---

一看就知道这是一个树形dp，然而就是想不出来。这题思路真的很巧妙。 记$f\[i\]\[j\]$为以$i$为根的子树全部都被照亮，且第$i$个点是被第$j$个点照亮的最小代价。记$g\[i\]$为$min_{j=1}^{n}\\{f\[i\]\[j\]\\}$。 对于$i$的儿子$son$，有 $$f\[i\]\[j\]=\\sum_{son}min(g\[son\],f\[son\]\[j\]-w\_j)+w\_j$$ $g\[1\]$即为答案。