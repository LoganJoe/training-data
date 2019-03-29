---
title: " DTOJ2937Sum of LCM\t\t"
tags:
  - 数论
  - 莫比乌斯反演
url: 1814.html
id: 1814
categories:
  - DTOJ
  - Solution
date: 2018-04-30 11:30:21
---

看到lcm，套路化简一波 $$\\sum_{i=1}^{n}\\sum_{j=1}^{n}lcm(A\_i,A\_j)$$ $$\\sum_{i=1}^{n}\\sum_{j=1}^{n}\\frac{A\_iA\_j}{gcd(A\_i,A\_j)}$$ 记$f(x)$为$gcd$为$x$的数对乘积和。即 $$f(x)=\\sum_{i=1}^{n}\\sum_{j=1}^{n}\[gcd(A\_i,A\_j)=x\]A\_iA\_j$$ 那么答案为 $$\\sum_{x=1}^{n}\\frac{f(x)}{x}$$ 直接求$gcd=x$的不太好求，考虑莫比乌斯反演，这也是套路了。 记$g(x)$为$gcd$为$x$倍数的数对乘积和。即 $$g(x)=\\sum_{i=1}^{n}\\sum_{j=1}^{n}\[x|gcd(A\_i,A\_j)\]A\_iA\_j$$ 化简一下，有 $$g(x)=\\sum_{i=1}^{n}\\sum_{j=1}^{n}\[x|A\_i\]\[x|A\_j\]A\_iA\_j$$ $$g(x)=\\sum_{i=1}^{n}\[x|A\_i\]A\_i\\sum_{j=1}^{n}\[x|A\_j\]A\_j$$ $$g(x)=(\\sum_{i=1}^{n}\[x|A\_i\]A\_i)^2$$ 所有$g(x)$可以在$\\Theta(nlog\\space n)$的时间内算出来。 莫比乌斯反演一下，有 $$f(x)=\\sum_{x|d}\\mu(\\frac{d}{x})g(d)$$ 那么所有的$f(x)$也可以在$\\Theta(nlog\\space n)$的时间内算出来了。