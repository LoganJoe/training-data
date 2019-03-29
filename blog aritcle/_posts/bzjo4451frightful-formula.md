---
title: " BZJO4451Frightful Formula\t\t"
tags:
  - FFT
  - 卷积
url: 6471.html
id: 6471
categories:
  - BZOJ
  - Solution
date: 2019-02-11 09:53:59
---

如果$c=0$的话，就是一道很普通的题了。 每个$f\[i\]\[1\]/f\[1\]\[i\]$对$f\[n\]\[n\]$的贡献系数都是一个组合数，即$(i,1)/(1,i)$向右或向下走到$(n,n)$的方案数。 具体为 $$ \\begin{aligned} \\forall i\\in\[2,n\],f\[i\]\[1\]:\\binom{n-i+n-2}{n-2}a^{n-1}b^{n-i}\\\ \\forall i\\in\[2,n\],f\[1\]\[i\]:\\binom{n-2+n-i}{n-2}a^{n-i}b^{n-1}\\\ \\end{aligned} $$ 如果$c\\neq 0$的话，其实我们可以单独计算每个$c$对$f\[n\]\[n\]$的贡献，贡献系数也是一个组合数。 具体为 $$ \\forall i,j\\in\[2,n\],(i,j):c\\binom{n-i+n-j}{n-i}a^{n-j}b^{n-i} $$ 考虑一起算所有格子的$c$对$f\[n\]\[n\]$的贡献，并化简，也就是 $$ \\begin{aligned} &=c\\sum_{i=2}^{n}\\sum_{j=2}^n\\binom{n-i+n-j}{n-i}a^{n-j}b^{n-i}\\newline &=c\\sum_{i=0}^{n-2}\\sum_{j=0}^{n-2}\\binom{i+j}{i}a^ib^j\\newline &=c\\sum_{i=0}^{n-2}\\sum_{j=0}^{n-2}\\frac{(i+j)!}{i!\\cdot j!}a^ib^j\\newline &=c\\sum_{i=0}^{n-2}\\sum_{j=0}^{n-2}(i+j)!\\cdot \\frac{a^i}{i!}\\cdot \\frac{b^j}{j!} \\end{aligned} $$ 这显然是一个卷积的形式。 记$A\_i=\\frac{a^i}{i!},B\_i=\\frac{b^i}{i!}$，我们用$A$和$B$卷积一下即可。 注意模式并不适用NTT，要写FFT。但FFT可能会爆精度，要卡精或者写拆分的FFT或者双模数NTT。 时间复杂度$\\Theta(n\\log n)$。