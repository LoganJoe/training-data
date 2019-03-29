---
title: " DTOJ1434Brunhilda的生日\t\t"
tags:
  - 思路
url: 2048.html
id: 2048
categories:
  - DTOJ
  - Solution
date: 2018-05-23 21:08:35
---

说数字$x$可以使人数从$\[kx,kx+x-1\],k\\in \\mathbb{Z}$变成$kx$。因此如果我们知道了$kx$的答案，就可以推出$\[kx,kx+x-1\],k\\in \\mathbb{Z}$的答案。因此我们对于所有的$kx$，从小到大去求后面的答案即可。 如果不是无解，答案一定是单调不减的。因此我们用一个队列维护现在可以用来推答案的位置，每次取出最前面的，去求后面未知的答案即可。