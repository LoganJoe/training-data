---
title: " DTOJ3588yja\t\t"
tags:
  - 二分
  - 凸包
  - 数学
url: 1318.html
id: 1318
categories:
  - DTOJ
  - Solution
  - 不会证
date: 2018-04-04 16:14:25
---

枚举在凸包上的点，记$r\_i$为凸包上第$i$个点所在圆的半径，$\\theta\_i$为第$i$和点和第$i+1$个点之间的角度（$\\theta\_n$表示第$n$个点和第$1$个点之间的角度）。 那么凸包的面积就是 $$\\frac{1}{2}(\\sum\_{i=1}^{n-1}r\_ir\_{i+1}sin(\\theta\_i)+r\_nr\_1sin(\\theta\_n))$$ 要求满足 $$\\sum_{i=1}^{n}\\theta\_i=2\\pi$$ 根据一个叫拉格朗日乘子数的东西，有 $$\\lambda=r\_1r\_2cos(\\theta\_1)=r\_2r\_3cos(\\theta\_2)=…=r\_nr\_1cos(\\theta\_n)$$ $\\theta\_1,\\theta\_2,…,\\theta\_n$关于$\\lambda$单调减。 因此可以二分$\\lambda$，然后算出$\\theta\_1,\\theta\_2,…,\\theta\_n$，检验是否满足$\\sum_{i=1}^{n}\\theta_i=2\\pi$。