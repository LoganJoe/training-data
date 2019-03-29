---
title: " DTOJ3954Cięcie\t\t"
tags:
  - 无标签
url: 4439.html
id: 4439
categories:
  - Solution
date: 2018-10-23 20:15:10
---

注意到当$sum|r$，那么$sum*10|r$。

于是我们记下这个数在%p下前缀和，在%p,%r下后缀和,分别为$sum1,sum2,sum3$。

然后我们对于每个$%r$下$sum3=0$的地方统计一下$sum2$每个值的个数。

于是我们就可以爆推一个$pq$的分界点，然后直接算出后面有多少个$qr$分界点满足题意。