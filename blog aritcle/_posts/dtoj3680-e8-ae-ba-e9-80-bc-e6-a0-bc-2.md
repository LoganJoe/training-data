---
title: " DTOJ3680论逼格\t\t"
tags:
  - 数学
url: 2378.html
id: 2378
categories:
  - Solution
date: 2018-06-13 21:11:58
---

很容易想到的，$s\_i=10 s\_{i-2}$,即$s\_i=10^{\\frac{i-1}{2}}$ 那么我们就是要求$9\\sum\_{i=0}^{\\frac{i+1}{2}}(2i-1)10^{i-1}$ 设$$S=\\sum_{i=0}^{\\lfloor \\frac{n-1}{2}\\rfloor}i\\times 10^i$$ 则$$10S=\\sum_{i=0}^{\\lfloor \\frac{n-1}{2}\\rfloor}i\\times 10^{i+1}$$ $$9S=\\lfloor \\frac{n+1}{2}\\rfloor 10^{\\lfloor \\frac{n+1}{2}\\rfloor+1}-\\sum_{i=1}^{\\lfloor \\frac{n-1}{2}\\rfloor}10^i$$ 原式就可以求了。 9在mod 233333下的逆元是25926。