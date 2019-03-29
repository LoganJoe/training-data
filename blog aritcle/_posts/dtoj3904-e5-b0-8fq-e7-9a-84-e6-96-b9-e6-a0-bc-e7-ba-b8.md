---
title: " DTOJ3904小Q的方格纸\t\t"
tags:
  - 思路
url: 3863.html
id: 3863
categories:
  - DTOJ
  - Solution
date: 2018-09-08 16:19:13
---

对于一个询问，我们可以用割补法将它拆开。 如下图 ![](http://www.dtenomde.com/wp-content/uploads/2018/09/DTOJ3904.png) 正方形就是简单的二维前缀和。 再维护一下直角在边界上的三角形的和即可。