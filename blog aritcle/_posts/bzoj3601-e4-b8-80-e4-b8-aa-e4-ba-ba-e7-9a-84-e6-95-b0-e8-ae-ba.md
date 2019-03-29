---
title: " BZOJ3601一个人的数论\t\t"
tags:
  - 数论
  - 高斯消元
url: 6308.html
id: 6308
categories:
  - BZOJ
  - Solution
date: 2019-02-02 14:26:25
---

推式子啦！ $$ \\begin{aligned} f\_d(n)&=\\sum\_{i=1}^{n}\[gcd(i,n)=1\]i^d\\newline &=\\sum_{i=1}^{n}i^d\\sum_{g|i,g|n}\\mu(g)\\newline &=\\sum_{g|n}\\mu(g)\\sum_{i=1}^{n}\[g|i\]i^d\\newline &=\\sum_{g|n}\\mu(g)\\sum_{i=1}^{\\frac{n}{g}}(ig)^d\\newline &=\\sum_{g|n}\\mu(g)g^d\\sum_{i=1}^{\\frac{n}{g}}i^d \\end{aligned} $$ 好像不能继续化了。 记$g(x)=\\mu(x)x^d,h(x)=\\sum_{i=1}^{x}i^d$，那么有$f\_d(n)=(g\\ast h)(n)$，其中$\\ast$表示狄利克雷卷积。 如果$f\_d(n)$是个积性函数，我们就可以对$n$分解质因数然后一个一个质因数算过去。 显然$g(x)$是个积性函数，然而$h(x)$不是。这就说明$f\_d(n)$不是积性函数，真是差差。 我们来研究一下$h(x)$。 诶这好像是个自然数幂和？ 那么$h(x)$就是一个关于$x$的$d+1$次多项式了。 我们可以用高斯消元求出这个多项式。据说好像还可以用插值和伯努利数，效率更优，然而我不会。 不妨记$h(x)=\\sum\_{i=0}^{d+1}a\_ix^i$。 那么我们可以继续化简式子了。 $$ \\begin{aligned} f\_d(n)&=(g\\ast h)(n)\\newline &=\\sum_{g|n}\\mu(g)g^d\\sum_{i=0}^{d+1}a\_i(\\frac{n}{g})^i\\newline &=\\sum\_{i=0}^{d+1}a\_i\\sum\_{g|n}\\mu(g)g^d (\\frac{n}{g})^i \\end{aligned} $$ 显然$\\sum_{g|n}\\mu(g)g^d (\\frac{n}{g})^i​$是个积性函数。 记$n=\\prod_{i=1}^mp\_i^{k\_i}$，那么我们只用考虑每个$p^k$。 $$ \\sum_{g|p^k}\\mu(g)g^d(\\frac{p^k}{g})^i=\\sum_{j=0}^{k}\\mu(p^j)p^{jd}p^{(k-j)i} $$ 由于$\\mu(x)$的性质，只有当$j=0$或$j=1$时$\\mu(p^j)\\neq 0$。 所以有 $$ \\sum_{g|p^k}\\mu(g)g^d(\\frac{p^k}{g})^i=p^{ki}-p^{ki-i+d} $$ 那么直接算就好啦。 时间复杂度$\\Theta(d^3+md\\log )$，$\\log$是快速幂的。