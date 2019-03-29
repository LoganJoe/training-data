---
title: " DTOJ3922str\t\t"
tags:
  - 数学
url: 4024.html
id: 4024
categories:
  - Solution
date: 2018-09-23 12:07:50
---

容易发现，最小串长一定是$\\lfloor \\log\_2 n\\rfloor +1$。因为这样子，长度为$\\lfloor \\log\_2 n\\rfloor +1$的所有字符串就有超过n种方案。

而一定不会有小于$\\lfloor \\log\_2 n\\rfloor$串长的方案，因为这样肯定不满足题意。那么我们就是确定了$2^{\\lfloor \\log\_2 n\\rfloor}$个前缀，要在后面选择$n-2^{\\lfloor \\log_2 n\\rfloor}$个位置再插入一个$0/1$使得满足条件，这样排列的最小方案数。

那么这个就是$\\binom{2^{\\lfloor \\log\_2 n\\rfloor}}{n-2^{\\lfloor \\log\_2 n\\rfloor}}$。