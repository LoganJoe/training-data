---
title: " BZOJ4059[Cerc2012]Non-boring sequences\t\t"
tags:
  - 奇技淫巧
url: 5857.html
id: 5857
categories:
  - BZOJ
  - Solution
date: 2018-12-29 15:05:52
---

和[BZOJ5200\[NWERC2017\]Factor-Free Tree](http://www.dtenomde.com/author=jiangyutong/article=5852/)类似。 记$L\_i$为$i$左边第一个与$i$相同的数的位置，$R\_i$为$i$右边第一个与$i$相同的数的位置。那么第$i$个数在区间$(L\_i,R\_i)$中是独一无二的。 考虑分治。记$Solve(l,r)$为判断区间$\[l,r\]$是不是无聊的。 我们每次在$\[l,r\]$中找到一个满足$L\_i< l$且$R\_i> r$的位置$i$，那么如果$\[l,i)$和$(i,r\]$都不是无聊的，区间$\[l,r\]$就不是无聊的。那么我们就将$Solve(l,r)$分成了$Solve(l,i-1)$和$Solve(i+1,r)$两个相同的子问题，可以递归完成。 可以证明，如果有多个合法的$i$存在，选哪一个是不会影响合法方案的存在。可以用反证法证明，在此略过。 这样最坏情况下时间复杂度是$\\Theta(n^2)$的。 我们考虑优化。 我们每次取所有合法的$i$中，离$l$或者$r$最近的那个。 这样时间复杂度是$\\Theta(n\\log n)$的。证明可以将这个分裂操作看作合并的逆操作，那么这个效率就是启发式合并的效率。 因此这种算法叫启发式分裂。