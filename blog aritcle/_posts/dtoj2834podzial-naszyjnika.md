---
title: " DTOJ2834Podział naszyjnika\t\t"
tags:
  - hash
url: 4501.html
id: 4501
categories:
  - Solution
date: 2018-10-24 20:22:45
---

一个相对好想到的思路是，我们可以用hash来判断一段中是否仅会出现某种颜色的所有珠子。 首先我们将每种珠子的颜色hash出来。然后考虑维护一个hash前缀和。 对于已经出现所有次数的珠子，我们在hash前缀和里将这种颜色的hash值减为初始值。此时假设一段珠子$\[l::r\]$满足条件，一定存在$ha\[r\]=ha\[l-1\]$。这样就可以方便的判断一段区间是否满足条件了。 于是我们将所有hash值通过排序找出所有相同的段。然后找出一段hash相同的，这段长度就是切点可以选的所有端点了。那么其中任选两个都可以计入方案数。 考虑现在求第二问。即两段之差绝对值的最小值。我们考虑这个用$two\\_{}pointer$求出。 设两个切点分别在$l,r$两珠子之后。那么令$|(r-l)-(n-r+l)|$最小，化简可得，实际上要令$|n-2l+2r|$最小。先让$l<r$，那么当$r$单调后移的时候，$l$也会单调后移。那么枚举$r$，就可以在$O(n)$线性推出$l$的位置。这样对于每段hash相同的，求得答案的效率是$O(len)$，算上排序，总时间复杂度$O(n \\log n)$。