---
title: " DTOJ2808Ice Hockey World Championship\t\t"
tags:
  - 折半搜索
url: 775.html
id: 775
categories:
  - Solution
date: 2018-02-25 21:17:17
---

折半搜索。 我们先搜前一半比赛的方案，再搜后一半比赛的方案。然后分别将两个数组排序。对于前一半的一个方案i花费fi的金钱，维护一个具有单调性的指针j表示在1-j中的所有后半段方案的总花费小于M.