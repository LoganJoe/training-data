---
title: " DTOJ2871 Zbox loves graph\t\t"
tags:
  - tarjan
url: 1281.html
id: 1281
categories:
  - Solution
date: 2018-03-29 19:41:52
---

首先，将所有的联通分量缩起来。很明显在一个连通分量内是可以互相到达的。 那么我们大胆猜测一发，联通分量个数不会超过8万。 我们用bitset，维护所有联通分量到其他联通分量的联通性质。假设一个联通分量**u**可以到达另外一个联通分量**v**，那么所有**v**可以到达的连通分量**u**也可以到达。