---
title: " DTOJ2924necklace\t\t"
tags:
  - 二分图
url: 5752.html
id: 5752
categories:
  - Solution
date: 2018-12-23 15:14:31
---

注意到$n \\leq 9$。 那这就很有意思了。 我们首先枚举$n$个阳珠子的排列顺序。然后考虑要怎么在其中插入阴珠子。 由于得到了所有阳珠子的顺序，那么我们就可以知道在这个位置放置哪些阴珠子会使得阳珠子暗淡。 将不会使得当前阳珠子暗淡的珠子与位置之间连一条边。那么等价于求最大匹配数目。 可以用garham解决。 为了避免环的重复计数，我们可以固定第一个珠子的位置。