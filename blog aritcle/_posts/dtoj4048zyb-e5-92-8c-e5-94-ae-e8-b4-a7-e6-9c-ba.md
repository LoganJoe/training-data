---
title: " DTOJ4048ZYB和售货机\t\t"
tags:
  - 思路
url: 5488.html
id: 5488
categories:
  - Solution
date: 2018-12-14 11:21:38
---

我们考虑转化一下问题的模型。 将指向的边连出来，发现这其实形成了多个基环树。树上的边一定可以全部取到，取不到的部分就是环上的部分。 那就让我们挑一个不取。假设某个贡献为负我们肯定从此处将环断开，其他就可以全部取了。否则，我们可以在环上跑一遍，找出贡献最小的那个然后从这个地方断开。 细节很多，很多，很多。