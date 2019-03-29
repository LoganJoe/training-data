---
title: " DTOJ1507Theresa与数据结构\t\t"
tags:
  - CDQ分治
url: 3718.html
id: 3718
categories:
  - Solution
date: 2018-08-28 16:28:23
---

很明显的一个四维偏序嘛。

对于每个询问，我们将询问拆成八个询问做就可以了。

撤销的话就用栈保存所有操作，撤销的时候就把操作从栈中取出来然后做反操作。