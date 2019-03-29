---
title: " DTOJ2152Madoka Magica\t\t"
tags:
  - 博弈
url: 3431.html
id: 3431
categories:
  - DTOJ
  - Solution
date: 2018-08-12 21:12:36
---

博弈论…果断跪了。 据说和分裂游戏是一样的，然而我还是不会。 每颗熄灭的宝石是一个子游戏。 考虑SG函数。我们定义$sg\_i$为当前只有第$i$颗宝石是熄灭的，后面宝石都是亮着的SG值。 那么我们可以通过枚举所有可能的操作来得到下一个状态的SG值，然后就能求出$sg\_i$。 把所有子游戏的SG值异或起来就能知道是否先手必胜了。 比较麻烦的是如何输出方案。 同样枚举一次操作，然后求出新的状态的SG值，如果SG值为$0$就说明新的状态必败，那么我们输出这步操作后的局面即可。