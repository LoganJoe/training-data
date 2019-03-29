---
title: " Codeforces438E The Child and Binary Tree\t\t"
tags:
  - FFT
  - 多项式开根
  - 多项式求逆
  - 生成函数
url: 5522.html
id: 5522
categories:
  - Codeforces
  - Solution
date: 2018-12-15 22:59:14
---

设$A(x)=\\sum_{i=0}^{\\infty}a\_ix^i$，其中$a\_i$为权值为$i$的答案。 设$B(x)=\\sum_{i=1}^n b_{c\[i\]}x^{c\[i\]}=\\sum_{i=0}^{\\infty}b\_ix^i$即点权值的生成函数。 那么我们有 $$ a\_i=\\sum_{j=0}^ib\_j\\sum\_{k=0}^{i-j}a\_ka\_{i-j-k}(i>0) $$ 特殊地，$a_0=1$。那么我们有 $$ A(x)=A^2(x)B(x)+1 $$ 解方程可得 $$ A(x)=\\frac{1\\pm \\sqrt{1-4B(x)}}{2B(x)}=\\frac{2}{1\\pm \\sqrt{1-4B(x)}} $$ 由于$x$可以为任何值。我们将$x=0$代入，发现其中一个解为$\\frac{2}{1-1}=\\frac 2 0$没有意义。 那么就有 $$ A(x)=\\frac{2}{1+ \\sqrt{1-4B(x)}} $$ 多项式开根+多项式求逆即可。