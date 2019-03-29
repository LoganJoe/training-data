---
title: " DTOJ3734Circle selection\t\t"
tags:
  - CDQ分治
url: 6781.html
id: 6781
categories:
  - Solution
date: 2019-03-03 14:56:52
---

很直接的思路是，枚举当前圆，再找出与其有交的圆并删除。 可以用砍大树来维护这个东西。 “没有什么K-D Tree问题是不能用CDQ分治解决的”。 我们来换个思路。枚举每个圆，我们仅找到与这个圆相交并且半径最大的圆。 在之前作为最大圆被删掉的圆肯定是两两不相交的，且半径大于$c\_i$。于是我们维护扫描线，每个圆和在直线上可以形成一个类似于括号序列的东西。并且括号序列的相对位置是不会改变的（这个圆括过去真的好像括号啊喂！） 另外，由于前面的圆半径都比它大，因此和它有交的圆必然经过 $x=x\_i+r\_i$或 $x=x\_i−r\_i$ 或 $y=y\_i−r\_i$ 或 $y=y\_i+r_i$中至少一位。 于是我们排个序，动态维护扫描线就好了。其间对于删掉哪个圆，我们可以按照相交弦讨论，对于上述四条扫描线分别维护4个set，每次直接在set中查询前驱和后继即是答案。 由于要处理多个圆，那么我们按照当前位置做CDQ分治，时间效率是加了set特技的$O(n \\log^2 n)$。比砍大树满了好多....