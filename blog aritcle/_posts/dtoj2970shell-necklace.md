---
title: " DTOJ2970Shell Necklace\t\t"
tags:
  - FFT
  - 分治
url: 5599.html
id: 5599
categories:
  - DTOJ
  - Solution
date: 2018-12-16 22:48:56
---

记$A(x)=\\sum_{i=1}a\[i\]x^i$，我们要求的就是多项式$\\sum_{i=1}^{n}A^i(x)$中$x^n$的系数。 我们可以用等比数列求和公式求出$\\sum_{i=1}^{\\infty}A^i(x)$，即求出$\\frac 1{1-A(x)}$。可以使用多项式求逆，但容易被卡精度。 记$f\[n\]$为多项式$\\sum_{i=1}^{n}A^i(x)$中$x^n$的系数。 那么有$f\[n\]=\\sum_{i=1}^{n}a\[i\]\\times f\[n-i\]$。 这是一个卷积的形式，但是我们必须算出前面的$f\[i\]$才能计算后面的$f\[i\]$。 我们考虑分治。每次用左半段的$f$计算出对右半段的$f$的贡献。那么直接FFT即可。 实际上这个形式就是分治FFT的板子形式。 时间复杂度$\\Theta(n\\log ^2n)$。