---
title: " DTOJ3536polynomial\t\t"
tags:
  - 无标签
url: 1191.html
id: 1191
categories:
  - Solution
date: 2018-03-22 16:30:37
---

对于一些情况可以判定无解： 当a=1： 1 1 1, infinity 1 1 n，n>1 : 0 1 b b^n, b>1,n>0: 1 对于其他，明显a>b或b>c是无解的。 由于是正整系数多项式，排掉上述特殊情况后，b必然大于所有系数。 那么p的一个唯一多项式一定是c在b进制下的一个展开的各个位作为系数。 那么只需要检验p(a)是否等于b即可。