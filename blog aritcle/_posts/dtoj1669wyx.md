---
title: " DTOJ1669wyx\t\t"
tags:
  - 数论
  - 莫比乌斯反演
url: 1419.html
id: 1419
categories:
  - DTOJ
  - Solution
date: 2018-04-14 14:33:55
---

考虑枚举$gcd(a,b)=g$。那么就变成了求 $$\\sum_{g=1}^{min(n,m)}f(g)\\sum_{i=1}^{\\lfloor \\frac{n}{i}\\rfloor}\\sum_{j=1}^{\\lfloor \\frac{m}{j}\\rfloor}\[gcd(i,j)=1\]$$ $$\\sum_{g=1}^{min(n,m)}f(g)\\sum_{i=1}^{\\lfloor \\frac{n}{i}\\rfloor}\\sum_{j=1}^{\\lfloor \\frac{m}{j}\\rfloor}\\sum_{d|i,d|j}\\mu(d)$$ $$\\sum_{g=1}^{min(n,m)}f(g)\\sum_{d=1}^{min(\\lfloor \\frac{n}{i}\\rfloor,\\lfloor \\frac{m}{i}\\rfloor)}\\lfloor \\frac{n}{dg}\\rfloor\\lfloor \\frac{m}{dg}\\rfloor$$ 分块算感觉效率已经很优秀了，但因为有多组数据，还是过不了。 然而这已经是我数论的极限了…所以我还是看了题解。 记$k=dg$，那么$d=\\frac{k}{g}$，那我们可以枚举$k$和$g$。那么有 $$\\sum_{k=1}^{min(a,b)}\\lfloor \\frac{n}{k}\\rfloor \\lfloor \\frac{m}{k}\\rfloor\\sum_{g|k}f(g)\\mu(\\frac{k}{g})$$ 这样后面的$\\sum$就和$n,m$无关了。考虑如何预处理出后面的前缀和。 记$g(x)=\\sum_{d|x}f(d)\\mu(\\frac{x}{d})$，那么就是要求出这个函数的前缀和。 观察一下这个函数，我们考虑使$\\mu(\\frac{x}{d})\\neq 0$的$d$对$g(x)$的贡献。 令$x=p\_1^{a\_1}\\times p\_2^{a\_2}\\times … \\times p\_k^{a\_k},d=p\_1^{b\_1}\\times p\_2^{b\_2}\\times … \\times p\_k^{b\_k}$。由于$\\mu(\\frac{x}{d})\\neq 0$，那么有$\\forall i\\in\[1,k\]$，有$0\\leqslant a\_i-b\_i\\leqslant 1$，也就是说$b\_i=a\_i$或$=a_i-1$。 分两类情况讨论。

1.  存在$\\forall i,j\\in\[1,k\]$，有$a\_i\\neq a\_j$。记$a\_x=max\\{a\_i\\}$，那么对于$x$的所有质因子，按照$a\_i=a\_x$和$a\_i<a\_x$分为$A,B$两个集合。那么在集合$A$中选一些$p\_i^{a\_i}$作为$d$的因子，集合$A$剩下的$p\_i$和集合$B$任选的一些$p\_i$作为$\\frac{x}{d}$。$f(d)$的值由集合$A$中的选取决定（有选就是$a\_x$，没选就是$a\_x-1$），而$\\mu(\\frac{x}{d})$的值由质因子个数奇偶性决定。无论集合$A$怎么选，在集合$B$选奇数个和偶数个的方案数都一样，也就是说所有$\\mu$的贡献相互抵消了。因此这种情况的$g(x)=0$。
2.  所有$a\_i$都相等。那么就是选一些$p\_i$作为$\\frac{x}{d}$。如果选的个数$\\neq k$，那么$f(d)=a$，否则$f(d)=a-1$。选奇数个和偶数个的方案是相同的，$\\mu$的贡献抵消后，只剩下了一个$\\pm 1$。考虑$\\mu$的符号后，有$g(x)=(-1)^{k+1}$。

写的很乱… 那么就可以在线性筛的时候求出$\\Theta(n)$求出所有的$g(x)$。具体地，可以看[这里](http://www.cnblogs.com/Hallmeow/p/8006177.html)。