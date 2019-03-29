---
title: " DTOJ1699仓库建设\t\t"
tags:
  - 斜率dp
url: 476.html
id: 476
categories:
  - Solution
date: 2018-02-04 13:41:39
---

我们考虑当前第i个仓库及之前所需要的费用。

${f\[i\]=min(f\[j\]+Xi*{\\sum_{k=j+1}^{i}P\[k\]} - \\sum_{k=j+1}^{i}Xk*Pk } )+ Ci$

这个式子的计算是n^2的。我们考虑如何加速计算。 利用前缀和思想，我们设：${Si=\\sum_{k=1}^{i}X\[k\]\*P\[k\]} $，${SPi=\\sum_{k=1}^{i}P\[k\]}$ 那么原式子改写为： ${f\[i\]=min(f\[j\]+Xi\*(SPi-SPj)- (Si-Sj) )+ Ci}$ 假设存在k<j，且j的决策比k优，即${f\[j\]-f\[k\]+Sj-Sk < Xi*(SPj-SPk) }$ 可以使用斜率优化解决。 我们维护一个单调队列，队列中有一个斜率单增的凸壳。之后就可以O(n）解决问题。答案为f\[n\]。