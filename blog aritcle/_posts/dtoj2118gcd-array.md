---
title: " DTOJ2118GCD Array\t\t"
tags:
  - 思路
  - 数论
url: 3380.html
id: 3380
categories:
  - DTOJ
  - Solution
date: 2018-08-12 15:46:11
---

给所有满足$gcd(x,n)=d$的位置$x$加上$v$，相当于给所有满足$d|x,gcd(\\frac{x}{d},\\frac{n}{d})=1$的位置$x$加上$v$，那么也可以看成给所有$d|x$的位置加上 $$ \\sum_{a|gcd(\\frac{x}{d},\\frac{n}{d})}\\mu(a)v $$ 也就是说，对于每个$a$，给$ad,2ad,3ad,…,kad,k\\in \\mathbb{Z}$加上$\\mu(a)v$。 每个位置都加肯定不行，我们考虑只加$ad$这个位置。 那么询问$a\_1\\sim a\_x$时，我们考虑每个位置的贡献实际上被算了几次。显然，位置$i$的贡献被算了$\\lfloor \\frac{x}{i}\\rfloor$次。 显然$\\lfloor \\frac{x}{i}\\rfloor $只有$\\sqrt{x}$个取值。 那么用树状数组维护每个位置的贡献，询问的时候整除分块优化即可。