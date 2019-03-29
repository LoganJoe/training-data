---
title: " DTOJ3527红绿灯\t\t"
tags:
  - dp
  - 线段树
url: 555.html
id: 555
categories:
  - DTOJ
  - Solution
date: 2018-02-15 19:50:38
---

同DTOJ2539BRT。 发现在某个路口遇到红灯后，等完后就等于从这个路口第$0$秒开始出发。 令$f\[i\]$为从第$i$个路口第$0$秒开始走到终点需要的时间。如果能找到之后第一个遇到红灯的路口就能进行转移。 记$Sum\[i\]$为前$i$段距离的前缀和。 若$j$为从$i$出发遇到的第一个红灯，则$j$为满足$(Sum\[j\]-Sum\[i\])\\%(g+r)\\geqslant g$最小的解。 记$Sum'\[i\]=Sum\[i\]\\%(g+r)$。

1.  若$Sum'\[i\]\\leqslant Sum'\[j\]$，则有$Sum'\[j\]-Sum'\[i\]\\geqslant g$，即$Sum'\[j\]\\geqslant Sum'\[i\]+g$。
2.  若$Sum'\[i\]>Sum'\[j\]$，则有$Sum'\[j\]-Sum'\[i\]+g+r\\geqslant g$，即$Sum'\[j\]\\geqslant Sum'\[i\]-r$。

这就是区间查询，单点修改的问题了。离散化$Sum'\[i\]$后线段树维护即可。 至于询问，我们同样只要找到第一个遇到的红灯即可。 若我们从第$x$秒出发，$i$为我们遇到的第一个红灯，则$i$为满足$(Sum\[i\]+x)\\%(g+r)\\geqslant g$最小的解。

1.  若$Sum'\[i\]+x<g+r$，则有$Sum'\[i\]+x\\geqslant g$，即$Sum'\[i\]\\geqslant g-x$。
2.  若$Sum'\[i\]+x\\geqslant g+r$，则有$Sum'\[i\]+x-g-r\\geqslant g$，即$Sum'\[i\]\\geqslant 2g+r-x$。

同样在线段树上区间查询即可。