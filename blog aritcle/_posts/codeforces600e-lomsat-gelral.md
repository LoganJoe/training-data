---
title: " Codeforces600E Lomsat gelral\t\t"
tags:
  - Dsu on tree
url: 966.html
id: 966
categories:
  - Codeforces
  - Solution
date: 2018-03-08 12:59:21
---

Dsu on tree裸题。 技巧暴力。 由于重儿子维护的信息不能重新添加，因此在遍历子树的时候要注意不能访问重儿子。 重儿子的信息也不能清空，因此求完当前点的答案时也要注意如果是轻儿子才清空数组。