---
title: " DTOJ3587xiz\t\t"
tags:
  - hash
  - KMP
url: 3571.html
id: 3571
categories:
  - Solution
date: 2018-08-25 21:16:15
---

我们发现，对于$S$串的一个字符映射，与$T$的匹配也算。于是我们换一个思路，我们记$pre_i$，为位置$i$字符的上一个出现位置。那么我们将$pre$拿去作为特征做kmp就好了。