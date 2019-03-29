---
title: " DTOJ2601采药人接水果\t\t"
tags:
  - dp
  - 思路
url: 4620.html
id: 4620
categories:
  - DTOJ
  - Solution
date: 2018-10-26 23:22:22
---

记$f\[i\]$为接到了第$i$秒的水果时能达到的最高的分数。 考虑能转移的$j$要满足什么条件： $$\\begin{cases}j<i \\\ |x\_i-x\_j|\\leq i-j\\end{cases}$$ 对于能转移的$j$，有$f\[i\]=max\_j\\{f\[j\]\\}+p\_i$。 我们把第二个条件拆开，变成 $$j-i\\leq x\_i-x\_j\\leq i-j$$ 这仿佛是个三维偏序的问题。 我们稍微再把第二个条件变形一下，变成 $$\\begin{cases}x\_i-x\_j\\geq j-i\\\ x\_i-x\_j\\leq i-j\\end{cases}$$ 移项一下，有 $$\\begin{cases}i+x\_i\\geq j+x\_j\\\ i-x\_i\\geq j-x\_j\\end{cases}$$ 这时我们发现，将这两个不等式加起来，就得到了$i\\geq j$！ 也就是说，我们只要满足第二个条件，并且保证$i\\neq j$，就能转移了。 那么就变成了二维偏序的问题。 一维sort，另一位用树状数组维护，就可以转移了。