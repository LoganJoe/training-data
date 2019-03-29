---
title: " DTOJ3825shop\t\t"
tags:
  - 思路
url: 3418.html
id: 3418
categories:
  - Solution
date: 2018-08-12 17:03:38
---

cf搬运题啊...一个大惊从早到晚失色。

其实这题打打表就可以找出规律。但是证明没那么好证就是了。

然后全场A掉这一题我就一脸懵逼。

先考虑只用$1,5,10$那么每$9$个$5$可以用$5$个$1$和$4$个$10$等价替换。那么$5$最多用$8$个就好了。我们枚举$5$用了几个算出方案。

考虑只用$5,10,50$那么每$9$个$10$可以用$1$个$50$和$8$个$5$等价替换。那么$10$最多用$8$个就好了。我们枚举$10$用了几个算出方案。

都用的话，$1$个$5$和$5$个$10$可以用$1$个$50$和$5$个$1$换掉，所以$10$的个数会$<5$。枚举$5$与$10$用了几个算出方案。

然后

**Another solution**: if you examine the solution above precisely, you will notice that starting some reasonable $n$ (you can easy proof a lowerbound like $50$ or$ 100$, but it is, in fact,$ 12$), the function grows **linearly**.

So if $n≤12$ you count the answer in any stupid way, and otherwise, simply approximate it linearly using $answer(12)$and$answer(13)$。

**linearly**.
=============

fuck。