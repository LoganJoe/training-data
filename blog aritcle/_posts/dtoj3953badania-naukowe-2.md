---
title: " DTOJ3953Badania naukowe\t\t"
tags:
  - dp
url: 4467.html
id: 4467
categories:
  - DTOJ
  - Solution
date: 2018-10-23 23:33:09
---

串C在LCS中出现，即串C是串A和串B的子序列。 记$pos1\[i\]$为从串A第$i$位开始匹配串C结束的位置，即串C作为串A的子序列出现过的最早结束位置。$pos2\[i\]$同理，只是变成在$B$串中匹配。如果无论无何都无法匹配就$=0$。 记$f\[i\]\[j\]$为串A的前$i$位和串B的前$j$位的LCS的长度，$g\[i\]\[j\]$为串$A$的后$n-i+1$位和串$B$的后$m-j+1$位的LCS的长度。这两个很容易在$\\Theta(nm)$内求出。 那么答案就是 $$\\max_{1\\leq i\\leq n,1\\leq j\\leq m} \\{f\[i-1\]\[j-1\]+k+g\[pos1\[i\]+1\]\[pos2\[j\]+1\]|pos1\[i\]\\&\\&pos2\[j\]\\} $$ 要注意判断无解的情况。