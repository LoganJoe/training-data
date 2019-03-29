---
title: " DTOJ3603table\t\t"
tags:
  - 数学
url: 1946.html
id: 1946
categories:
  - Solution
date: 2018-05-11 17:05:20
---

我们先考虑往下走。 考虑第p行对下方的贡献，我们可以视其为一个位于$(p,i)$,且值为$f_{p,i}$的数，每向下走一步并乘$a$或向右走一步并乘$b$，并把所处的方格加上这个数，那么会有 $$f_{x,y}=\\sum_{i=1}^{y}f_{p,i}a^{(x-p)-(y-i)}b^{y-i}\\binom{x-p}{y-i}$$ 那么对于x>p,可以每次O(n)回答一个询问。 再考虑怎么往上走。 类似之前的思路，我们可以视其为一个位于$(p,i)$,且值为$f_{p,i}$的数，每向下走一步并除$a$或向右走一步并乘$-\\frac{b}{a}$，并把所处的方格加上这个数，那么会有 $$f_{x,y}=\\sum_{i=1}^{y}\\frac{f_{p,i}(-b)^{y-i}\\binom{p-x+y-i-1}{y-i}}{a^{p-x+y-i}}$$ 同样可以在O(n)内回答询问。两式中的$N!,N!^{-1},a^k,b^k,(a^k)^{-1},(-b)^k$均可以预处理。