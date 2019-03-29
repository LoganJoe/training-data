---
title: " BZOJ2219数论之神\t\t"
tags:
  - BSGS
  - 定理
  - 数学
url: 6321.html
id: 6321
categories:
  - BZOJ
  - Solution
date: 2019-02-04 12:20:33
---

神仙题。 题意相当于让我们求$x^A\\equiv B \\pmod P$的解的个数。（默认解在$\[0,P)$中） 记$P=\\prod_{i=1}^np\_i^{k\_i}$，那么原方程的解的个数是每个形如$x^A\\equiv B \\pmod {p\_i^{k\_i}}$的解的个数的乘积。 因为原方程的每一个$x$都唯一地对应着一组新方程的解，而一组新方程的解根据中国剩余定理也只对应着一个原方程的解$x$。 那么问题就变成了，求$x^A\\equiv B \\pmod {p^k}$的解的个数。 开始分类讨论。这里认为$B\\in\[0,p^k)​$。

1.  $B=0$ 那么$x^A\\equiv 0 \\pmod {p^k}$。$x​$一定形如$a\\cdot p^b​$，要满足$A\\cdot b\\geq k​$。最小的合法的$b=\\left \\lceil \\frac{k}{A}\\right \\rceil​$。 那么方程的解的个数为$p^{k-\\left \\lceil \\frac{k}{A}\\right \\rceil}$。
2.  $gcd(B,p^k)=1$ 这算是很经典的问题了。我们取离散对数，也就是指标。 具体地，$ind(x)$表示在模$p$意义下以$p$的原根$g$为底，$x$的对数，即 $$g^{ind(x)}\\equiv x \\pmod p$$ 可以利用BSGS算法求出$ind(x)$。 那么原方程相当于 $$A\\cdot ind(x)\\equiv ind(B) \\pmod {\\varphi(p)}$$ 记$G=gcd(A,\\varphi(p))$，根据同余的只是，若$ind(B)\\% G\\neq 0$时无解，否则解的个数为$G$。（每隔$\\frac{\\varphi(p)}{G}$有一个解，一共就有$\\frac{\\varphi(p)}{\\frac{\\varphi(p)}{G}} =G$个解）
3.  $gcd(B,p^k)>1$ 设$B=a\\cdot p^b$，那么 $$x^A\\equiv a\\cdot p^b \\pmod{p^k}$$ 如果$b\\% A\\neq 0$，那么方程无解。 否则方程可以转换成 $$\\left (\\frac{x}{p^{\\frac b A}}\\right)^A\\equiv a \\pmod {p^{k-b}}$$ 此时$gcd(a,p^{k-b})=1$，变成了第二种情况。 但是这样还有点问题。 原式中$x\\in\[0,p^k)$，那么$\\frac{x}{p^{\\frac b A}}\\in\[0,p^{k-\\frac b A})$。 但是在最后一个式子中，$\\frac{x}{p^{\\frac b A}}\\in\[0,p^{k-b})$。 因此最后还要把方程的解的个数$\\times p^{b-\\frac b A}$。