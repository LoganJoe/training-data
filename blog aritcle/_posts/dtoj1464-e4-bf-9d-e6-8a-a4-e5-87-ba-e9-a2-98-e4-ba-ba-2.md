---
title: " DTOJ1464保护出题人\t\t"
tags:
  - dp
  - 三分
url: 1856.html
id: 1856
categories:
  - Solution
date: 2018-05-01 18:33:34
---

我们首先计$Sum\_i=\\sum\_{j=1}^{i}a\_i$。那么每一关就是要让$max\\{\\frac{Sum\_i-Sum_{j-1}}{x\_i+(i-j)d},j\\leqslant i\\}$这个东西可以看做是一条直线的斜率，就是经过两点$(x\_i+i\*d,Sum\_i)$和$(j\*d,Sum\_j−1)$的斜率。那么最大的ans就是在所求得的下凸壳上取最大。对于每个点只要维护出凸壳然后三分找出最大值即可。