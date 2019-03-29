---
title: " DTOJ3702月读\t\t"
tags:
  - hash
  - 奇技淫巧
url: 2576.html
id: 2576
categories:
  - Solution
date: 2018-06-18 20:50:53
---

（惊了竟然忘记这题是啥了...) 大概就是对于一条路径要问是不是一条回文串。 要是一个回文串，只能有一个数出现奇数次。否则绝不会是回文串。 于是我们将路径用异或hash起来，然后对于询问的起点和终点，直接用树上异或前缀和即可得到这条路径上的异或和。对于这个异或和，如果为0则表示所有数出现奇数次，否则判断剩下是否只有一个数。 我们可以把每个值hash起来，然后用hash值在树上异或。对与链上异或和，我们查询是否有这样的点值即可。这样出错的可能性很小，约为$\\frac{1}{2^{60}}$。