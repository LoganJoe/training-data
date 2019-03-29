---
title: " DTOJ2237The Forest of Fangorn\t\t"
tags:
  - 计算几何
url: 3859.html
id: 3859
categories:
  - DTOJ
  - Solution
date: 2018-09-08 15:25:37
---

考虑在位置$A$的树和位置$B$的树会使得哪些位置不能被走到。显然是直线$AB$除掉线段$AB$的部分。 我们枚举其中一个位置的树，那么剩下的树就能画出$n-1$条同起点的射线，显然我们不能跨过这条线。 那么这$n-1$条线会将平面划分成$n-1$个部分，显然我们只能走到和起点同一部分的营地。 按线的斜率排序，即可找到起点所属的部分。 只有一直和起点在同一部分营地才是可以走到的。 附上样例画出来的图。 ![](http://www.dtenomde.com/wp-content/uploads/2018/09/DTOJ2237.jpg)