---
title: " DTOJ3531字符串\t\t"
tags:
  - 思路
url: 605.html
id: 605
categories:
  - DTOJ
  - Solution
date: 2018-02-16 20:57:44
---

如果循环节长度$>6$，那么出现次数最多的字母的出现次数$\\geqslant 3$。此时单独把这个字母当循环节不比原本劣。 因此搜出所有长度$\\leqslant 6$可能的循环节，再求出对应这个循环节最长的子序列算价值即可。