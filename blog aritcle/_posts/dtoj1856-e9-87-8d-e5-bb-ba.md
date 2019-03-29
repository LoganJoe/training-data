---
title: " DTOJ1856重建\t\t"
tags:
  - 概率
  - 矩阵树
url: 3425.html
id: 3425
categories:
  - DTOJ
  - Solution
date: 2018-08-12 18:20:10
---

大概能看出这题是矩阵树定理。 但我们用矩阵树算出来的会是这个 $$\\sum \\prod_{(u,v)\\in T}P_{u,v}$$ 而我们要的应该是这个 $$\\sum \\prod_{(u,v)\\in T}P_{u,v}\\prod_{(u,v)\\not \\in T}(1-P_{u,v})$$ 我们可以手动乘上$\\prod_{(u,v)\\in E} P_{u,v}$，那么就得到了 $$\\sum \\prod_{(u,v)\\in T}P_{u,v}(1-P_{u,v})\\prod_{(u,v)\\not \\in T}(1-P_{u,v})$$ 和答案就差一点了。 我们把边权改成$\\frac{P_{u,v}}{1-P_{u,v}}$即可。 注意当$P_{u,v}=1$时我们令$P_{u,v}=1-eps$，否则答案会变成nan。