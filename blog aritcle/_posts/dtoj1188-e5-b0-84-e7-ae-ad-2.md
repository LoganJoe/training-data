---
title: " DTOJ1188射箭\t\t"
tags:
  - 半平面交
url: 1882.html
id: 1882
categories:
  - Solution
date: 2018-05-06 21:28:19
---

对于每一关，即是要求a,b,c,使得满足尽量多的形如$ax^2+bx>y\_1,ax^2+bx<y\_2$的一组要求。既然对于每个询问已知x,y1,y2，则 $$ax^2+bx\\geqslant y1$$ $$bx\\geqslant y1-ax^2$$ $$b\\geqslant \\frac{y1}{x}-ax$$ 这样我们就可以把每组拆成两个半平面。那么我们二分一个答案$ans$，我们只需要每次判断1--ans组成的半平面是否存在即可。