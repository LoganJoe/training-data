---
title: " BZOJ4115[Wf2015]Tile Cutting\t\t"
tags:
  - FFT
  - 卷积
url: 2525.html
id: 2525
categories:
  - BZOJ
  - Solution
date: 2018-06-16 22:45:22
---

我们考虑把平行四边形的面积表示出来。 ![](http://www.dtenomde.com/wp-content/uploads/2018/06/258DA562-672A-424C-AA0E-CF82EDA4FFF8.jpg) 记面积为$S$。那么有 $$S=(a+d)(b+c)-ab-cd=ac+bd$$ 令$x=ac,y=bd$，那么面积为$S$的平行四边形个数就是 $$\\sum_{x=1}^{S}d(x)\\cdot d(S-x)$$ 其中，$d(x)$是$x$的约数个数。 显然是个卷积的形式。用线性筛预处理出$d(x)$，FFT一下即可求出所有答案。 询问就是求一下区间最大值就可以了。