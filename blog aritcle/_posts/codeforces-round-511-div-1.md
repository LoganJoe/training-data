---
title: " Codeforces Round #511 (Div. 1)\t\t"
url: 5225.html
id: 5225
categories:
  - Solution
date: 2018-11-22 15:46:27
tags:
---

#### [原题链接](http://codeforces.com/contest/1034)

#

Name

题意

题解

[A](http://codeforces.com/contest/1034/problem/A)

[Enlarge GCD](http://codeforces.com/contest/1034/problem/A)

删掉最少的数，使得全部数的gcd变大。

考虑使得gcd变大，肯定是对于至少有一个不在原gcd中的质因子，在剩下的每个数中全部出现。那么对于每个数，除掉gcd后我们统计一下每个质因子在多少个数中出现了。那么​最大出现次数 就是最小答案。

[B](http://codeforces.com/contest/1034/problem/B)

[Little C Loves 3 II](http://codeforces.com/contest/1034/problem/B)

​的格子，每次可以选两个曼哈顿距离为3的格子填数，问最多可以填多少格子。

考虑最多可以填​的数。观察一下发现貌似多数情况下都是可以填满的..?但是还是有很多情况需要特判的。以下考虑​,首先就是​,当​的时候，有一些格子是取不到的。还有​的时候，也是有一排格子是取不到的...打出​的表，再特判​的情况就够了。关于这个东西为什么是对的，所有的$m$都等于若干个$4,5,6$的和，而$m=4,5,6$时都能放满，因此拼起来也能放满。那么这个就是对的了。

[C](http://codeforces.com/contest/1034/problem/C)

[Region Separation](http://codeforces.com/contest/1034/problem/C)

[D](http://codeforces.com/contest/1034/problem/D)

[Intervals of Intervals](http://codeforces.com/contest/1034/problem/D)

[E](http://codeforces.com/contest/1034/problem/E)

[Little C Loves 3 III](http://codeforces.com/contest/1034/problem/E)