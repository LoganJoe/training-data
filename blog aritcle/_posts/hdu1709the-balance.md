---
title: " HDU1709The Balance\t\t"
tags:
  - 生成函数
url: 265.html
id: 265
categories:
  - Solution
  - 其他OJ
date: 2018-01-17 16:06:34
---

将单独砝码能称的重量用多项式表示。 注意由于砝码能在天平两边放，所以$x^i\\times x^j$的结果不仅可以更新到$x^{i+j}$的系数，也可以更新到$x^\\left|i-j\\right |$的系数。 最后看一下所有多项式的乘积有哪几项系数为$0$就好了。