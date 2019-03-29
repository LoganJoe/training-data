---
title: " JZOJ6002Permutation\t\t"
tags:
  - 思路
  - 数学
url: 6076.html
id: 6076
categories:
  - Solution
  - 不会证
  - 其他OJ
date: 2019-01-16 23:35:09
---

考虑暴力。 我们枚举第$y$个位置上的值$i$，那么有 $$ ans=(y-2)!(n-y)!\\sum_{i=y}^{n}\\binom{i-2}{y-2}\\left \\lfloor \\frac{i-1}2\\right \\rfloor $$ 其中$(y-2)!$和$(n-y)!$是第$y$位前面除了第$x$位随便排的方案数和第$y$位后面随便排的方案数。$\\binom{i-2}{y-2}$是选出除了第$x$位的前$y-1$位，$\\left \\lfloor \\frac{i-1}2\\right \\rfloor$是第$x$位合法的取值数量。 这样时间复杂度是$\\Theta(NQ)$的。 题解的思路就很奇特了。 我们先考虑满足第一个条件的排列数，共有$\\frac{n!}{y}$。可以理解为前$y$位的最大值可能出现在$1\\sim y$中的任意一位，并且概率相等，因此方案数就是总方案数$\\div k$。 我们将所有满足第一个条件的排列分成三类：

1.  $2P\_x<P\_y$
2.  $2P\_x=P\_y$
3.  $2P\_x>P\_y$

题解说根据对称性可知第一类和第三类的方案数是一样的，然而我不知道对称性是啥，只好感性理解了。 因此我们只要求出第二类的方案数即可。 记$y=i$时第二类的方案数为$f\[i\]$，那么答案就是$\\frac{\\frac{n!}{y}-f\[y\]}{2}$。 不妨枚举$P\_x=j$，那么$P\_y=2j$，那么有 $$ f\[i\]=(y-2)!(n-y)!\\sum_{j=1}^{\\left \\lfloor \\frac{n}{2}\\right \\rfloor}\\binom{2j-2}{i-2} $$ 设$g\[i\]=\\sum_{j=0}^{\\left \\lfloor \\frac{n}{2}\\right \\rfloor-1}\\binom{2j}{i}​$，那么$f\[i\]=(y-2)!(n-y)!g\[i-2\]​$ 发现$g\[i\]​$实际上是组合数中某一列的第偶数行的前缀和。 根据组合数的性质，我们可以得到 $$ g\[i-1\]+2g\[i\]=\\binom{2\\left \\lfloor \\frac{n}{2}\\right \\rfloor}{i+1} $$ $g\[i-1\]+2g\[i\]$实际上是组合数第$i$列前$2\\left \\lfloor \\frac{n}{2}\\right \\rfloor-1$行的和。 这样我们就可以$\\Theta(n)$递推出所有的$g\[i\]$了。 时间复杂度$\\Theta(n)$。