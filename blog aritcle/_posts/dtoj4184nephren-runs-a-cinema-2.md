---
title: " DTOJ4184Nephren Runs a Cinema\t\t"
tags:
  - 数学
  - 计数
url: 6932.html
id: 6932
categories:
  - Solution
date: 2019-03-10 21:26:05
---

将$50$看成$1$，$100$看成$-1$。那么就是要求一个合法的$01$序列，其前缀和时时刻刻$>0$，且最后和在$\[L,R\]$之间。 那么惯用转化：从$(0,0)$出发，$1$向右走，$0$向上走，不能走过$y=x+1$这条线。 假设走了$x$个$1$，那么合法方案数就是$\\binom{n}{x}-\\binom{n}{x+1}$。 因为$x-y\\in\[L,R\], x+y=n$，所以$2x\\in \[L+n,R+n\] \\to x\\in\\left \[\\left \\lceil \\frac{L+n}{2}\\right \\rceil,\\left \\lfloor \\frac{R+n}{2}\\right \\rfloor \\right\]$。那么现在我们就是要求 $$\\sum_{\\left \\lceil \\frac{L+n}{2}\\right \\rceil}^{\\left \\lfloor \\frac{R+n}{2}\\right \\rfloor}\\binom{n}{x}-\\binom{n}{x+1}$$ 拆开组合数化简一下： $$\\binom{n}{\\left \\lceil \\frac{L+n}{2}\\right \\rceil}-\\binom{n}{\\left \\lfloor \\frac{R+n}{2}\\right \\rfloor+1}$$ 直接枚举走了几个刷卡的计算答案。 至于取模的问题，我们对于模数分解质因数，然后计算阶乘关于这些质因数的幂，除的时候减去幂次即可。