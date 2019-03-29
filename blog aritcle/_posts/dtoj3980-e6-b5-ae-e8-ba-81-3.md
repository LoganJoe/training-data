---
title: " DTOJ3980浮躁\t\t"
tags:
  - 容斥
url: 4989.html
id: 4989
categories:
  - DTOJ
  - Solution
date: 2018-11-01 22:39:14
---

根据容斥原理，至少参加一门竞赛的人数，等于每门竞赛的人数减去每两门竞赛共同的人数加上每三门竞赛共同的人数…… 具体来说，答案就是 $$\\sum_{i=1}^{n}(-1)^{i+1}\\binom{n}{i}a\_i$$ 但是$n$很大，我们直接算肯定存不下。 如果有取模我们就可以算组合数了，但这题没有。 注意到题目保证了$a\_1\\times n\\leq 10^9$，那么答案一定$\\leq 10^9$。 那我们可以选择一个$>10^9$的模数，在模意义下计算答案。 因为答案$\\leq 10^9$，所以模意义下的答案就是真正的答案。