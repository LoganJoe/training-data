---
title: " DTOJ3873Game\t\t"
tags:
  - 博弈
url: 3800.html
id: 3800
categories:
  - Solution
date: 2018-09-03 16:56:53
---

这题跟之前的一题博弈很像。那么我们按照类似的方法定义SG函数，记第i个是白的后面全是黑的SG值。然后每次记SG的后缀和，对一个左端点枚举所有在左端点是这个位置的区间更新SG，效率$O(N)$。