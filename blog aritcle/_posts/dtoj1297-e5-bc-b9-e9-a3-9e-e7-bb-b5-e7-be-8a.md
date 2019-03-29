---
title: " DTOJ1297弹飞绵羊\t\t"
tags:
  - Link-Cut Tree
url: 1544.html
id: 1544
categories:
  - DTOJ
  - Solution
date: 2018-04-17 07:59:12
---

将第$i$个点向第$i+k_i$个点连边，被弹飞的话就向第$n+1$个点连边。 那么询问就变成了询问一个点到根的长度。 同时要维护删边和加边的操作。 Link-Cut-Tree板子题。