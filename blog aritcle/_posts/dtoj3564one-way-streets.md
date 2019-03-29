---
title: " DTOJ3564One-Way Streets\t\t"
tags:
  - tarjan
  - 并查集
url: 2038.html
id: 2038
categories:
  - DTOJ
  - Solution
date: 2018-05-22 12:52:35
---

显然不是割边的边答案一定是B，因此我们可以把图缩成一棵树。 那么就变成了树的定向问题。 对于要从$a$走到$b$的限制，我们可以给$a$到$b$的路径的边打上对应方向的标记。然后用并查集把打过标记的点压在一起避免复杂度爆炸。