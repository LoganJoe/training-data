---
title: " DTOJ3953Badania naukowe\t\t"
tags:
  - dp
url: 4437.html
id: 4437
categories:
  - Solution
date: 2018-10-23 20:05:25
---

主要考虑中间那个限制。

那么我们就强制取那段$C$，再在前后各取子序列就好了。

记$t1\[i\]$为$A$串从$i$位置开始，匹配到一个$C$串后的最小位置。$t2\[i\]$对$B$串同理。那么我们分别正着和倒着对$A$和$B$求一下LCS，则

$$ ans = \\max_{i,j \\in \[1,n\]} \\{f\[i - 1\]\[j - 1\] + g\[t1\[i\] + 1\]\[t2\[j\] + 1\] + k \\} $$