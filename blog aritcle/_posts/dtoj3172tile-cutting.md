---
title: " DTOJ3172Tile Cutting\t\t"
tags:
  - FFT
  - 生成函数
url: 3545.html
id: 3545
categories:
  - Solution
date: 2018-08-24 19:53:40
---

服。真的服。

既然是在网格的边界上考虑嵌入一个四边形。那么我们发现，只要用四个变量就可以描述一个四边形了。为了方便，我们用下图说明：

[258DA562-672A-424C-AA0E-CF82EDA4FFF8](http://www.dtenomde.com/wp-content/uploads/2018/06/258DA562-672A-424C-AA0E-CF82EDA4FFF8.jpg)[Download](http://www.dtenomde.com/wp-content/uploads/2018/06/258DA562-672A-424C-AA0E-CF82EDA4FFF8.jpg)

然后，割补可知，平行四边形的面积为$S=(a+d)(b+c)-ab-cd=ac+bd$。

那么答案，面积为S的四边形个数就是$$\\sum_{x=1}^{S}d(x) \\times d(S-x)$$

这是一个卷积的性质，可以用$FFT$优化多项式乘法。