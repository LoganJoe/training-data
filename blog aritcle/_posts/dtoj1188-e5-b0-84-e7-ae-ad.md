---
title: " DTOJ1188射箭\t\t"
tags:
  - 二分
  - 半平面交
url: 452.html
id: 452
categories:
  - DTOJ
  - Solution
date: 2018-02-04 13:07:57
---

显然可以二分答案，接下来就是判断$ans$是否可行。 设抛物线为$y=ax^2+bx$。要通过一关显然要有$y1\\leqslant ax^2+bx\\leqslant y2$。 分开化简

$ax^2+bx\\geqslant y1$

$bx\\geqslant y1-ax^2$

$b\\geqslant \\frac{y1}{x}-ax$

把$b$看作$y$，$a$看做$x$，式子就代表了一个半平面。 由于$a\\leqslant 0$，$b\\geqslant 0$，所以外面要手动加上一个大方框限制。由于不能$=0$，所以直线还要手动移动一点点（比如eps）。 有解即半平面的交不为空。 BZOJ这题精度简直玄学，换一种二分居然也能WA？？？还要我怎样？