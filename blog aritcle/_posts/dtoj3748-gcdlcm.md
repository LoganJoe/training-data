---
title: " DTOJ3748 GCDLCM\t\t"
tags:
  - 数论
  - 莫比乌斯反演
url: 6865.html
id: 6865
categories:
  - DTOJ
  - Solution
date: 2019-03-08 16:54:16
---

不妨假设$n\\leq m,a\\leq n$。 $$ \\begin{aligned} ans&=\\sum_{i=1}^n\\sum_{j=1}^m\[\\gcd(i,j)\\leq a\]\\mathrm{lcm}(i,j)\\newline &=\\sum_{i=1}^n\\sum_{j=1}^m\[\\gcd(i,j)\\leq a\]\\frac{ij}{\\mathrm{gcd}(i,j)}\\newline &=\\sum_{g=1}^a\\sum_{i=1}^{\\left \\lfloor \\frac{n}{g}\\right \\rfloor}\\sum_{j=1}^{\\left \\lfloor \\frac{m}{g}\\right \\rfloor}\[\\gcd(i,j)=1\]ijg\\newline &=\\sum_{g=1}^g g\\sum_{i=1}^{\\left \\lfloor \\frac{n}{g}\\right \\rfloor}\\sum_{j=1}^{\\left \\lfloor \\frac{m}{g}\\right \\rfloor}ij\\sum_{d|i,d|j}\\mu(d)\\newline &=\\sum_{g=1}g\\sum_{d=1}^{\\left \\lfloor \\frac{n}{g}\\right \\rfloor }\\mu(d)d^2\\sum_{i=1}^{\\left \\lfloor \\frac{n}{dg}\\right \\rfloor}\\sum_{j=1}^{\\left \\lfloor \\frac{m}{dg}\\right \\rfloor}ij \\end{aligned} $$ 记$Sum(i)=\\sum_{i=1}^x i$，则有 $$ ans=\\sum_{g=1}g\\sum_{d=1}^{\\left \\lfloor \\frac{n}{g}\\right \\rfloor }\\mu(d)d^2\\cdot Sum(\\left \\lfloor \\frac{n}{dg}\\right \\rfloor)\\cdot Sum(\\left \\lfloor \\frac{m}{dg}\\right \\rfloor) $$ 设$T=dg$，原式为 $$ \\begin{aligned} ans&=\\sum_{T=1}^nSum(\\left \\lfloor \\frac{n}{T}\\right \\rfloor)\\cdot Sum(\\left \\lfloor \\frac{m}{T}\\right \\rfloor)\\sum_{g|T}\[g\\leq a\]g\\cdot (\\frac T g)^2\\cdot \\mu(\\frac T g)\\newline &=\\sum_{T=1}^nSum(\\left \\lfloor \\frac{n}{T}\\right \\rfloor)\\cdot Sum(\\left \\lfloor \\frac{m}{T}\\right \\rfloor)\\sum_{g|T}\[g\\leq a\]\\frac {T^2} g\\cdot \\mu(\\frac T g) \\end{aligned} $$ 我们将询问离线，并按$a$从小到大排序，然后依次处理。 这样我们就可以动态添加合法的$g$的贡献，对于每一个$g$，我们枚举它能影响到的$T$，然后在对应位置上加$\\frac {T^2} g\\cdot \\mu(\\frac T g)$。 对于一次询问，我们可以整除分块，然后就是要查询一段区间的$T$的和。 单点修改区间查询，可以用树状数组实现。 时间复杂度$\\Theta(q\\sqrt{n}\\log n+n\\log ^2 n)$。