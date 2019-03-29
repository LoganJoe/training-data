---
title: " BZOJ1228[SDOI2009]E&D\t\t"
tags:
  - 博弈
  - 找规律
url: 6192.html
id: 6192
categories:
  - BZOJ
  - Solution
date: 2019-01-25 23:24:19
---

显然每组游戏是独立的，我们可以分别求出每组游戏的$SG$值然后再异或合并起来。 先打出二维的$SG$函数的表…… 然后就可以开始找规律了…… 我们发现奇数行奇数列都是$0$。 奇数行偶数列等于下方的数，偶数行奇数列等于右边的数。 我们把表缩小一半，继续观察。 发现奇数行奇数列变成了$1$。 奇数行偶数列还是等于下方的数，偶数行奇数列还是等于右边的数。 再缩小一半，还是同样的规律。 因此我们就找出了规律: $$ SG(i,j)=\\begin{cases} 0 & i,j为奇数 \\newline SG(\\lceil \\frac{i}{2} \\rceil,\\lceil \\frac{j}{2}\\rceil)+1 & otherwise \\end{cases} $$ 这样求一次$SG$是$\\Theta(\\log )$的。 总时间复杂度$\\Theta(Tn\\log S_i)$。