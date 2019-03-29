---
title: " DTOJ2696图森破\t\t"
tags:
  - 数论
url: 795.html
id: 795
categories:
  - DTOJ
  - Solution
date: 2018-02-26 20:22:14
---

设$f\[i\]$为$n$位置（可以有前导$0$）中所有满足条件的数字$X$个数。 那么所求的就是$\\sum_{i=1}^{n}i^2f\[i\]$。 考虑求$f\[i\]$。 如果一个数字$X$的循环节不为自身，那么这个数字一定不满足条件。因为当第二个循环节作为开头时数字大小一定$\\leqslant X$。若循环节为自身，那么从任意位置开始循环这个数字一圈得到的结果都不一样。一定只有以最小的为开头才满足条件。因此只要求循环节为自身的数字个数，然后$\\div i$即可。 循环节为自身的数字个数可以通过容斥计算，我们枚举循环节长度$d$，然后有 $$f\[i\]=\\frac{\\sum_{d|i}10^dμ(\\frac{i}{d})}{i}$$ 那么要求的 $$\\sum_{i=1}^{n}i^2f\[i\]=\\sum_{i=1}^{n}i\\sum_{d|i}10^dμ(\\frac{i}{d})=\\sum_{d=1}^{n}dμ(d)\\sum_{i-1}^{\\lfloor \\frac{n}{d}\\rfloor}i10^i$$ 其中$\\sum_{i=1}^{\\lfloor \\frac{n}{d}\\rfloor}i10^i$，变形一下是等比数列求和，可以快速求出。 因为$\\lfloor \\frac{n}{d}\\rfloor$只有$n^{\\frac{1}{2}}$个，我们可以把相同的放在一起算。 设$g\[i\]=\\sum_{j=1}^{i}jμ(j)$。我们只要求出所有的$g\[\\lfloor \\frac{n}{d}\\rfloor\]$即可。 先预处理出$n^{\\frac{2}{3}}$内的$g$，剩下的我们可以用类似杜教筛的方法求出。 令 $$G\[n\]=\\sum_{i=1}^{n}i\\sum_{d|i}μ(d)=\\sum_{d=1}^{n}μ(d)\\sum_{i=1}^{\\lfloor \\frac{n}{d}\\rfloor}id=\\sum_{d=1}^{n}dμ(d)\\sum_{i=1}^{\\lfloor \\frac{n}{d}\\rfloor}i$$ 考虑每个$i$贡献的$dμ(d)$。显然只有满足$\\lfloor \\frac{n}{d}\\rfloor\\leqslant i$的$d$才会被$i$贡献到，即$d\\leqslant \\lfloor \\frac{n}{i}\\rfloor$。 因此有 $$原式=\\sum_{i=1}^{n}i\\sum_{d=1}^{\\lfloor \\frac{n}{i}\\rfloor}dμ(d)=\\sum_{i=1}^{n}ig\[\\lfloor \\frac{n}{i}\\rfloor\]$$ 由于$\\sum_{d|x}μ(d)$只有当$x=1$时为$1$，其余时候为$0$。所以我们显然有$G\[i\]=1$。 所以有 $$g\[n\]=G\[n\]-\\sum_{i=2}^{n}ig\[\\lfloor \\frac{n}{i}\\rfloor\]=1-\\sum_{i=2}^{n}ig\[\\lfloor \\frac{n}{i}\\rfloor\]$$ 对于$\\lfloor \\frac{n}{i}\\rfloor$相同的我们同样可以放在一起算，就能求出$g\[n\]$。 时间复杂度O($n^{\\frac{2}{3}}$)。