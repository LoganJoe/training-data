---
title: " DTOJ1539Gcd反应堆\t\t"
tags:
  - 数论
url: 1202.html
id: 1202
categories:
  - DTOJ
  - Solution
date: 2018-03-22 21:06:53
---

$1$不算质数，所以令$1\\leqslant i\\leqslant m$不会影响答案。 考虑枚举$gcd$，也就是枚举$\\leqslant n,m$的质数。 对于一个质数$p$，满足$1\\leqslant i\\leqslant m,1\\leqslant j\\leqslant n$且$gcd(i,j)=p$的数对个数，一定和满足$1\\leqslant i\\leqslant \\lfloor \\frac{m}{p}\\rfloor,1\\leqslant j\\leqslant \\lfloor \\frac{n}{p}\\rfloor$且$gcd(i,j)=1$的数对个数相同。 那么我们对于每个质数$p$，令$N=\\lfloor \\frac{m}{p}\\rfloor,M=\\lfloor \\frac{n}{p}\\rfloor$，那么问题变成了求 $$\\sum_{i=1}^{N}\\sum_{j=1}^{M}\[gcd(i,j)=1\]$$ 也就是 $$\\sum_{i=1}^{N}\\sum_{j=1}^{M}\\sum_{d|i,d|j}μ(d)$$ 把$μ(d)$提前 $$\\sum_{d=1}^{N}μ(d)\\sum_{i=1}^{\\lfloor \\frac{N}{d}\\rfloor}\\sum_{j=1}^{\\lfloor \\frac{M}{d}\\rfloor}1$$ 也就是 $$\\sum_{d=1}^{N}μ(d)\\lfloor \\frac{N}{d}\\rfloor \\lfloor \\frac{M}{d}\\rfloor$$ 将$\\lfloor \\frac{N}{d}\\rfloor$相同且$\\lfloor \\frac{M}{d}\\rfloor$也相同的$d$放在一起算即可。 总效率不会算，反正能过。