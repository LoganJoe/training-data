---
title: " DTOJ2881C\t\t"
tags:
  - 无标签
url: 1276.html
id: 1276
categories:
  - Solution
date: 2018-03-29 19:27:46
---

对于一段相似，当且仅当一段中1的个数与s相同。 由于询问的串长度不会很大，那么我们在$i \\subseteqq \\sqrt{n}$中预处理出f\[i\]\[j\],代表长度为i的字符串s，其中具有j个1，能得到的所有满足条件的位置。对于原串用前缀和处理后时间复杂度为$O(N^{\\frac{1}{ 2}} \\times N^{\\frac {1}{2}})$ 对于长度大于$\\sqrt{n}$的我们再暴力统计即可。由于$\\sum len(s) \\leq 2\\times 10^5$，导致效率最多会被卡到\[latex\]O( n^{\\frac {3} {2}} )\[/latex\]