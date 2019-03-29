---
title: " DTOJ1507Theresa与数据结构\t\t"
tags:
  - CDQ分治
url: 3477.html
id: 3477
categories:
  - DTOJ
  - Solution
date: 2018-08-17 22:05:38
---

四维偏序模板题，差不多类似[DTOJ1477抓企鹅](http://www.dtenomde.com/author=jiangyutong/article=1650/)。 （然后发现这题我题解也直接水过了… 这题就是需要把询问通过三维前缀和拆成$8$个子询问。 写一个CDQ套CDQ即可。 用归并维护某一维有序常数比sort小很多。 但我还是不清楚是谁给出题人的勇气让他觉得$\\Theta(n\\log ^3 n)$能过$10^5$。