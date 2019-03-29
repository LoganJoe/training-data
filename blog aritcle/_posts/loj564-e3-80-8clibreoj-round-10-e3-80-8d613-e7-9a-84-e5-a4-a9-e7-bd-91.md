---
title: " LOJ564「LibreOJ Round #10」613 的天网\t\t"
tags:
  - 思路
url: 6414.html
id: 6414
categories:
  - Solution
date: 2019-02-08 11:24:07
---

可以发现，用三个互相垂直的平面（无厚度）把 $n\\times n\\times n$ 的矩形分成 $8$ 份，如果选择处于对角的两份，且能构造方案使得这两个区域中每行、列、纵列都有摄像头，即可得一组合法方案。 构造 $n\\times n\\times n$ 的矩形中 $n\\times n$ 个摄像头使得其每一行列纵都有摄像头做法很多，一种简单的方法为：对于 $z=z0$ 的平面，在 $y=x+z0​$ 上的点放置摄像头。