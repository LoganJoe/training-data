---
title: " DTOJ4049ZYB玩字符串\t\t"
tags:
  - 区间dp
  - 思路
url: 5444.html
id: 5444
categories:
  - Solution
date: 2018-12-11 22:44:58
---

考虑枚举一段可能的字符串，然后判定这个是否合法。首先，这个子串长度要可以整除$n$，并且其中每种字母的出现次数都要能整除总出现次数。 那么可以发现，这样的字符串不会超过$O(n \\log n)$个，并且实际可以减小非常非常多。就是从O(勉强跑得过)变成了O(肯定跑得过)$。 接下来考虑如何判定合法。考虑可以区间dp求解。$f\[l\]\[r\]$表示$\[l,r\]$内字符串能否被完整作出。我们枚举分界点，可以在$O(n^2len)$内求解。注意到前面$len$的衰减是调和级数的效率，与前面合并效率是$O(n^3 \\log n)$，并且还会小很多。