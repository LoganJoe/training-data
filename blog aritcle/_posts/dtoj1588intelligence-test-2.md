---
title: " DTOJ1588Intelligence test\t\t"
tags:
  - 无标签
url: 3960.html
id: 3960
categories:
  - Solution
date: 2018-09-15 22:52:07
---

直接对于每个数，保存在序列中出现的所有位置。对于一个序列，依次处理每一位，然后对于每个数，找到比当前位置大的第一个数贪心的跳过去。直接判断是否合法。