---
title: " DTOJ3848Bajtman i Okrągły Robin\t\t"
tags:
  - 线段树
  - 费用流
url: 3849.html
id: 3849
categories:
  - Solution
date: 2018-09-08 13:54:46
---

考虑最小割。

两排点，每个强盗向$l\_i-r\_i$间的点连边。强盗和时刻分别向原点和汇点连边。跑出最小费用最大流即是答案。

建边效率有点奇妙，于是我们线段树优化建图。

然后这题会卡你时间。。。