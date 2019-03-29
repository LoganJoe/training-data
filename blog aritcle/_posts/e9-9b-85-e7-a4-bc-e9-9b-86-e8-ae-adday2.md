---
title: " 雅礼集训Day2\t\t"
url: 1223.html
id: 1223
categories:
  - 笔记
date: 2018-03-24 23:31:38
tags:
---

数论
--

### 常见积性函数

*   $\\epsilon(n)=\[n=1\]$
*   $\\mathrm 1(n)=1$（完全积性）
*   $\\mathrm{Id}(n)=n$（完全积性）
*   $\\mathrm{Id}_k(n)=n^k$（完全积性）
*   $\\mu(n)$
*   $\\varphi(n)=n\\prod_{d|n}(1-\\frac{1}{d})$
*   $\\mathrm d(n)=\\sum_{d|n}1$
*   $\\sigma(n)=\\sum_{d|n}d$
*   $\\lambda(n)=(-1)^k$（$k$为$n$的质因子个数）

### 狄利克雷卷积

$$(f\\ast g)(n)=\\sum_{d|n}f(d)g(\\frac{n}{d})$$

*   $\\mu \\ast \\mathrm 1=\\epsilon$（莫比乌斯反演）
*   $\\mathrm {Id}=φ\\ast \\mathrm 1\\Rightarrow φ=\\mu \\ast \\mathrm{Id}$
*   $\\mathrm d=\\mathrm 1\\ast \\mathrm 1\\Rightarrow \\mathrm 1=\\mu \\ast \\mathrm d$
*   $\\sigma=\\mathrm{Id}\\ast \\mathrm 1\\Rightarrow \\mathrm{Id}=\\mu\\ast \\sigma$
*   $\\sigma=φ\\ast \\mathrm d$

### 一些性质

*   $gcd(a^k-1,b^k-1)=x^{gcd(a,b)}-1$
*   $a^{φ(p)}\\equiv 1(mod\\space p)$
*   $gcd(Fib(a),Fib(b))=Fib(gcd(a,b))$
*   $\\mathrm d(ij)=\\sum_{p|i}\\sum_{q|j}\[gcd(p,q)=1\]$
*   $\\sigma(ij)=\\sum_{p|i}\\sum_{q|j}\[gcd(p,q)=1\]\\frac{i}{p}q$
*   $\\sum_{i=1}^{n}\\mu^2(i)=\\sum_{i\\geqslant 1}\\mu(i)\\lfloor \\frac{n}{i^2}\\rfloor$

### 组合数的性质

*   $\\binom{n}{k}=\\frac{n}{k}\\binom{n-1}{k-1}$
*   $\\binom{n}{k}=\\frac{n-k+1}{k}\\binom{n}{k-1}$
*   $\\binom{n}{k}=\\sum_{i=0}^{k}\\binom{n-k-1+i}{i}$
*   $\\binom{n}{k}=\\sum_{i=0}^{n-1}\\binom{i}{k-1}$