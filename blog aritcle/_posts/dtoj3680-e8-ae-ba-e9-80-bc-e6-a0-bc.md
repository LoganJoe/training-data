---
title: " DTOJ3680论逼格\t\t"
tags:
  - 数学
url: 1890.html
id: 1890
categories:
  - DTOJ
  - Solution
date: 2018-05-06 22:01:19
---

发现$s\[i\]$其实很好求，对于$i$为奇数的时候，$s\[i\]=9\\times 10^{\\lfloor \\frac {i}{2}\\rfloor}$。 那么所求的就变成了 $$\\sum_{i=0}^{\\lfloor \\frac{n-1}{2}\\rfloor}(2i+1)\\times 9\\times 10^i$$ 即 $$18\\sum_{i=0}^{\\lfloor \\frac{n-1}{2}\\rfloor}i\\times 10^i+9\\sum_{i=0}^{\\lfloor \\frac{n-1}{2}\\rfloor}10^i$$ 后面的显然是一个等比数列，前面的也可以通过化简成为等比数列。 具体地，记 $$S=\\sum_{i=0}^{\\lfloor \\frac{n-1}{2}\\rfloor}i\\times 10^i$$ 那么有 $$10S=\\sum_{i=0}^{\\lfloor \\frac{n-1}{2}\\rfloor}i\\times 10^{i+1}$$ 两式相减，有 $$9S=\\lfloor \\frac{n-1}{2}\\rfloor 10^{\\lfloor \\frac{n-1}{2}\\rfloor+1}-\\sum_{i=1}^{\\lfloor \\frac{n-1}{2}\\rfloor}10^i$$ $$S=\\frac{\\lfloor \\frac{n-1}{2}\\rfloor 10^{\\lfloor \\frac{n-1}{2}\\rfloor+1}-\\sum_{i=1}^{\\lfloor \\frac{n-1}{2}\\rfloor}10^i}{9}$$ 那么$S$就是个等比数列了。 现在问题就是求出$9$的逆元。 由于$233333$不是质数，可以用exgcd，也可以暴力枚举逆元。当然也可以机智的发现$233333+1$是$9$的倍数。