---
title: " DTOJ1420[VIOLET 3]天使玩偶\t\t"
tags:
  - CDQ分治
url: 225.html
id: 225
categories:
  - DTOJ
  - Solution
date: 2018-01-11 15:10:19
---

注意到题目求的是曼哈顿距离最小。 曼哈顿距离的定义为

$dist(A,B)=\\left | Ax-Bx \\right |+\\left | Ay-By \\right |$

若$Ax\\geqslant Bx$且$Ay\\geqslant By$，则式子可以化简为

$dist(A,B)=(Ax-Bx)+(Ay-By)=(Ax+Ay)-(Bx+By)$

所以在$(x,y)$左下方距离它最近的点就是$x+y$最大的点。 同理我们可以求出左上方，右下方和右上方距离$(x,y)$最近的点。 这样就是一个三维偏序的问题了，CDQ分治解决。