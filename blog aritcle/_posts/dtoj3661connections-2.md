---
title: " DTOJ3661connections\t\t"
tags:
  - tarjan
url: 5978.html
id: 5978
categories:
  - Solution
date: 2019-01-04 11:39:54
---

观察到既然原图强联通，那么我们可以用tarjan求出强联通分量。 考虑所有的强联通分量，其在tarjan中就是跑出去的树边与更新low的非树边。 这个边数一定小于$2n$。最后随便选几条凑到$2n$就得了。