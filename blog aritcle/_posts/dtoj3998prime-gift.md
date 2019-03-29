---
title: " DTOJ3998Prime Gift\t\t"
tags:
  - 二分
url: 5213.html
id: 5213
categories:
  - Solution
date: 2018-11-21 21:38:18
---

可以愉快的meet in middle。我们爆搜每个质数的出现次数。由于所有的乘积不会超过$10^18$，所以拆成两半分别做可以跑过去。 然后考虑二分答案再在之前搜出来的方案里two_pointers就可以判定这个答案合不合法了。 注意乘在一起可能会爆。要用除的特判一下。