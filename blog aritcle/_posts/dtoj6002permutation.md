---
title: " DTOJ6002permutation\t\t"
tags:
  - NTT
  - 思路
  - 数学
url: 6055.html
id: 6055
categories:
  - Solution
date: 2019-01-16 18:25:56
---

很容易推出$60pts$的dp：我们枚举第$y$个选了那个数，显然$x$是没有用的，并且$P\_y \\in\[y,n\]$。 $$ ans=\\sum\_{i=y}^{N}\\binom{i-2}{y-2}\\left\\lfloor\\frac{i-1}{2}\\right\\rfloor(n-y)!(y-2)! $$ 分别是选$i-2$个数放到前面，第$x$位有$\\left\\lfloor\\frac{i-1}{2}\\right\\rfloor$个选法，然后前面后面的排列各有$(n-y)!,(y-2)!$。 那么我们拆开这个式子：首先将$(n-y)!,(y-2)!$放到最前面去；那么里面再拆开，就是 $$ \\begin{aligned} ans&=(n-y)!\\sum_{i=y}^{n}\\left\\lfloor\\frac{i-1}{2}\\right\\rfloor\\times \\frac{(i-2)!}{(i-y)!} \\newline &=(n-y)!\\sum_{i=0}^{n-y}\\left\\lfloor\\frac{i+y-1}{2}\\right\\rfloor\\times\\frac{(i+y-2)!}{i!}\\\ \\\define \ A(x)&=(k-2)!\\left\\lfloor\\frac{k-1}{2}\\right\\rfloor x^k \\\B(x)&=\\frac{1}{(n-k)!}x^k\\\ \\\ \\Rightarrow ans&=(n-y)! \\times \[x^{n+y}\](A(x)\\otimes B(x)) \\end{aligned} $$ NTT解决，时间复杂度$O(n \\log n)$。 有$O(n)$做法，下面是题解： 考虑所有满足$𝑝_𝑦$是前$𝑦$项值中最大值全排列，共$\\frac{𝑛!}{y}$个，对于$𝑝_𝑥$的值，可以分为三类： 1. $2𝑝_𝑥 ≤ 𝑝_𝑦$ 2. $2 𝑝_𝑥 = 𝑝_𝑦$ 3. $2 𝑝_𝑥 ≥ 𝑝_𝑦$ 根据对称性，第$(1)$类和第$(3)$类的全排列个数是相等的，所以我们计算第二类全排 列的个数$𝑓_𝑦$，答案即为 $$ \\frac{\\frac{n!}{y}-f\_y}{2} $$ 考虑$𝑝\_𝑦 = 2𝑘, 𝑝_𝑥 = 𝑘$的情况，$𝑦$之前除$𝑥$外剩余$𝑦 − 2$个位置需要在$2𝑘 − 2$个数中 选取$𝑦 − 2$个，方案数 $$ \\frac{2k-2}{y-2} (𝑦 − 2)! (𝑛 − 𝑦)! $$ 第二类全排列的总个数 $$ \\sum_{k=1}^{n/2}\\binom{2k-2}{y-2}(𝑦 − 2)! (𝑛 − 𝑦)! $$ 现在只需对于每个$𝑦$，求解 $$ \\sum_{k=1}^{n/2}\\binom{2k-2}{y-2} $$ 设 $$ m = \\left\\lfloor\\frac{𝑛}{2}\\right\\rfloor,𝑔_𝑥 =\\sum_{k=0}^{m-1}\\binom{2k}{x} $$ 根据组合数学，可以推出 $$ g_{𝑥−1} +2𝑔_{𝑥} = \\binom{2m}{x+1} $$ 故可以按顺序求解$𝑔_𝑖$ 的值。 最后，$𝑓_𝑦 = 𝑔_{𝑦−2} · (𝑦 − 2)! · (𝑛 − 𝑦)!$ 时间复杂度$𝑂(𝑛)$，期望得分100分。