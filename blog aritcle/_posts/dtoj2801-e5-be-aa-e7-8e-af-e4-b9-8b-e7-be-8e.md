---
title: " DTOJ2801循环之美\t\t"
tags:
  - 奇技淫巧
  - 数论
url: 6204.html
id: 6204
categories:
  - Solution
date: 2019-01-26 14:47:16
---

我们考虑一个小数，在什么情况下是循环的。显然，就是要在$k$进制下，出现一个重复的余数。对于纯循环小数，就是该重复的余数是第一个。也就是说： $$ \\exists l\\in \\mathbb{N^*}\ ,\ xk^l\\equiv x\\mod y $$ 又因为改分式要为最简分式才有值不重复，那么有 $$ k^l\\equiv 1 \\mod y $$ $$ (k,y)=1 $$ 于是，我们要求的式子就很明确了： $$ \\begin{aligned} &\\sum_{x=1}^{n}\\sum_{y=1}^{m}\[(x,y)=1\]\[(y,k)=1\] \\\ =&\\sum_{y=1}^{m}\[(y,k)=1\]\\sum_{x=1}^{n}\[(x,y)=1\]\\\ =&\\sum_{y=1}^{n}\[(y,k)=1\]\\sum_{x=1}^{n}\\sum_{d|(x,y)}\\mu(d) \\\ =&\\sum_{y=1}^{m}\[(y,k)=1\]\\sum_{d|y}\\mu(d)\\left\\lfloor\\frac{n}{d}\\right\\rfloor\\\ =&\\sum_{d=1}^{n}\\mu(d)\\left\\lfloor\\frac{n}{d}\\right\\rfloor\\sum_{d|y}^{m}\[(y,k)=1\]\\\ =&\\sum_{d=1}^{n}\\mu(d)\\left\\lfloor\\frac{n}{d}\\right\\rfloor\\sum_{i=1}^{\\lfloor\\frac{m}{d}\\rfloor} (k,id)=1\\\ =&\\sum_{d=1}^{n}\[(d,k)=1\]\\mu(d)\\left\\lfloor\\frac{n}{d}\\right\\rfloor\\sum_{i=1}^{\\lfloor\\frac{m}{d}\\rfloor} (k,i)=1 \\end{aligned} $$ 设$f(n,k)=\\sum_{i=1}^{n}\[(i,k)=1\]​$: $$ f(n,k)=\\left\\lfloor\\frac{n}{k}\\right\\rfloor f(k,k)+f(n \\% k,k) $$ 很明显，$(a,b)=(a\\% b,b)​$。 考虑数论分块。按照$\\left\\lfloor\\frac{n}{d}\\right\\rfloor$分块。设$g(n,k)=\\sum_{i=1}^{n}\[(i,k)=1\]\\mu(i)$。考虑枚举$k$的一个质因数$p$，设$p=p^cq$。 显然有 $$ \\begin{aligned} g(n,k)&=\\sum_{i=1}^n\[i\\perp q\]\\mu(i)-\\sum_{y=1}^{\\lfloor\\frac{n}{p}\\rfloor}\[py\\perp q\]\\mu(py) \\\&=g(n,q)- \\sum_{y=1}^{\\lfloor\\frac{n}{p}\\rfloor}\[y\\perp q\]\\mu(py)\\\ &=g(n,q)- \\sum_{y=1}^{\\lfloor\\frac{n}{p}\\rfloor}\[y\\perp p\]\[y\\perp q\]\\mu(p)\\mu(y)\\\&=g(n,q)-\\mu(p)\\sum_{y=1}^{\\lfloor\\frac{n}{p}\\rfloor}\[y\\perp k\]\\mu(y)\\\&=g(n,q)+g(\\lfloor\\frac{n}{p}\\rfloor,k) \\end{aligned} $$ 可以递归求解。$k=1$的时候就是mobius函数前缀和。