---
title: " DTOJ4052Tiny Counting\t\t"
tags:
  - 无标签
url: 5496.html
id: 5496
categories:
  - Solution
date: 2018-12-14 13:53:50
---

注意到对于$a<b$，$c>d$的数量都很好求。考虑扣掉相等的情况。 于是对于每个位置，分别统计大于$i$和小于$i$，逆序与顺序对的数量。 然后最后扣掉$a=c,a=d,b=c,b=d$的时候相应对数就好了。