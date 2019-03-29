---
title: " DTOJ3961biology\t\t"
tags:
  - hash
  - 二分
url: 4582.html
id: 4582
categories:
  - DTOJ
  - Solution
date: 2018-10-25 21:34:02
---

题意就是每次询问$T$个字符串的最长公共后缀，要求支持加入字符串。 发现$T\\leq 10$。 我们可以每次二分最长公共后缀的长度，然后判断。 预处理每个字符串的前缀hash值就可以$\\Theta(T)$判断了。 时间复杂度$\\Theta(Tm\\log )$。