---
title: " DTOJ3410splay.one\t\t"
tags:
  - 线段树
url: 6926.html
id: 6926
categories:
  - Solution
date: 2019-03-10 20:48:34
---

题面太傻吊了。 大概就是能不能用集合内的数凑出$x$。 当$gcd(a,b)=1$的时候，显然可以凑出1，那么也就可以用$a,b$凑出任何数。否则能凑出的最小正整数是$gcd(a,b)$。 那么我们开一个权值线段树，然后维护全局gcd即可。