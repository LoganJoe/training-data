---
title: " DTOJ4234permutation\t\t"
tags:
  - 思路
  - 斯特林数
url: 7052.html
id: 7052
categories:
  - 未分类
date: 2019-03-17 20:35:56
---

这题要求的东西和[DTOJ2577建筑师](http://10.110.182.1/problem/2577)一致，只不过数据范围变大了很多，没办法$O(n^2)$预处理出Strling数。这题的题解见[这里](http://www.dtenomde.com/author=iftest614/article=5016/)。 但是第一类斯特林数是可以倍增求的。 第一类斯特林数其实可以NTT求出。 考虑实际上，$s(n,m)=\\begin{bmatrix} n \\\ m \\end{bmatrix} = \[x^m\] x^{ \\overline{n}}$。 现在直接求第一类斯特林数的某一行，即直接求$x^{ \\overline{n}}=\\prod_{i=0}^{n-1}(x+i)$。分治NTT可以在$O(n \\log^2 n)​$内求$x^{ \\overline{n}}$。 考虑现在已知$F(x)=x^{ \\overline{\\frac{n}{2}}} \\mod x^{\\frac{n}{2}}$，要求$x^{ \\overline{n}}$的$G(x)=\\sum f\_i(x+\\frac{n}{2})^i$. $$ \\begin{aligned} G(x) &=\\sum\_{i=0}^n f\_i(x+\\frac n2)^i \\\&=\\sum\_{i=0}^nf\_i\\sum\_{j=0}^i \\binom{i}{j}x^j\\left(\\frac n2\\right)^{i-j} \\\&=\\sum_{j=0}^nx\_j \\sum\_{i=j}^n \\binom{i}{j}f\_i\\left(\\frac n2\\right)^{i-j} \\end{aligned} $$ 后面是一个卷积的形式。令$A(x)=\\sum f\_ii! x^i, B(x)=\\sum\\frac 1i\\left(\\frac n2\\right)^i x^i$， 那么 $$ \[x^k\]G(x)=k!\\sum_{j=1}^{n}A\_iB\_{i-j} $$ 可以直接倍增求出。