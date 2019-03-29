---
title: " DTOJ3824servant\t\t"
tags:
  - 树形dp
url: 2846.html
id: 2846
categories:
  - DTOJ
  - Solution
date: 2018-07-19 22:09:27
---

算是很裸的树形dp的题目了，但是我这种题特别容易写错…不知道为啥…而且还跑的贼慢… 然后测试的时候把$n,m$看成$2e5$，以为有比$\\Theta(nm)$更优的做法一直没写…… 记$f\[x\]\[i\]\[j\]$为以$x$根的子树内，共选了$i$个点，选的点到$x$不经过任何其他被选的点的最大距离为$j$，最大的权值和是多少。 那么我们可以考虑$x$这个点选不选，进行对应的转移。 $x$不选的情况可以一边枚举子树dfs一边转移。 $x$选的情况（可能）要先预处理出最大值（即不管距离限制做树上背包）然后最后手动多选一个点转移。 觉得挺简单的就不具体讲了。 注意答案是所有的$f\[x\]\[i\]\[j\]$而不是$f\[1\]\[i\]\[j\]$，因为儿子的信息并不能传到根。