---
title: " DTOJ2926Solar panel\t\t"
tags:
  - 数学
url: 4151.html
id: 4151
categories:
  - Solution
date: 2018-10-16 13:09:20
---

首先枚举答案$ans$。

在其中要存在两个数$a,b$，其$GCD=ans$,那么一定要有$a|ans,b|ans$。

那么在$\[1,r\]$中，$a|ans$的$a$的个数显然为$\\left\\lfloor \\frac{r}{ans}\\right\\rfloor$。

那么本题就变成了枚举$ans$，判定$\\left\\lfloor \\frac{A-1}{ans}\\right\\rfloor < \\left\\lfloor \\frac{B}{ans}\\right\\rfloor , \\left\\lfloor \\frac{C-1}{ans}\\right\\rfloor < \\left\\lfloor \\frac{D}{ans}\\right\\rfloor$是否有解。