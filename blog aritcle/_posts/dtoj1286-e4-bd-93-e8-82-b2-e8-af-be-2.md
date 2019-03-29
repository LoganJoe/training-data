---
title: " DTOJ1286体育课\t\t"
tags:
  - 凸包
  - 分块
url: 6889.html
id: 6889
categories:
  - Solution
date: 2019-03-08 16:26:28
---

**[DTOJ4212小X爱旅行](http://www.dtenomde.com/wp-admin/post.php?post=6885&action=edit&classic-editor)** 考虑这和上面那题很像。不同的是多了一个交换的操作。 正常块交换，只需要将直线直接update下去，然后交换两个位置重构凸壳就好了。 考虑与$1$交换的情况。首先要消掉对于后面的影响，然后再行交换。具体地相当于加上$0x+A_1$的直线，然后交换再消去。 复杂度仍然是$O(n \\sqrt n \\log n)$。