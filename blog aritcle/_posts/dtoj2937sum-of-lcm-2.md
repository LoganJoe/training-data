---
title: " DTOJ2937Sum of LCM\t\t"
tags:
  - 数论
url: 2391.html
id: 2391
categories:
  - Solution
date: 2018-06-14 12:33:27
---

答案让我们求 $$\\sum_{i=1}^{n}\\sum_{j=1}{n}\\frac{A\_iA\_j}{(A\_iA\_j)}$$ 考虑枚举gcd,设$f\_d$为$gcd=d$的数对$A\_i,A\_j$的乘积和。显然有 $$f\_d=\\sum_{i=1}^{n}\\sum_{j=1}^{n}A\_iA\_j\[(A\_i,A\_j)==1\]$$ 而答案显然为$\\sum_{d=1}^{n}\\frac{f\_d}{d}$。 f并不是很好求。我们考虑用莫比乌斯反演来求f。 设$g\_d$为$gcd$为$x$倍数的乘积和。反演可得$f\_d=\\sum\_{d|d'} \\mu(\\frac{d'}{d})g(d')$。 考虑如何求d: $$g\_d=\\sum\_{i=1}^{n} A\_i \[d|A\_i\] \\sum_{j=1}^{n} A\_j\[d|A\_j\]=(\\sum_{i=1}^{n} A\_i \[d|A\_i\] )^2$$ 这个我们可以枚举每个数，记录每个因子的反因子来求出。时间效率$O(n log n)$