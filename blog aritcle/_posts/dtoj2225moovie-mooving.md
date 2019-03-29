---
title: " DTOJ2225Moovie Mooving\t\t"
tags:
  - 状压dp
url: 2109.html
id: 2109
categories:
  - Solution
date: 2018-05-27 19:24:11
---

看那个N那么小。 我们想一个状压dp。把每个电影，看或未看压成一位，对于当前一个状态S，枚举一种没看过的电影，然后二分找出最早的时间。这样转移以后对于大于L的状态，计算了一下看了几场电影就好了。