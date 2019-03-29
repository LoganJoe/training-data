---
title: " BZOJ4259残缺的字符串\t\t"
tags:
  - FFT
url: 2515.html
id: 2515
categories:
  - Solution
date: 2018-06-16 22:23:38
---

两个字符相等，一定有$(a-b)\[a \\neq *\]\[b \\neq *\]=0$ 令通配符为0。则会有$(a-b)\[a \\neq 0\]\[b \\neq 0\]=0$ 设对于串a,b的函数$dist(a,b)=\\sum_{i=1}{n}(a\_i-b\_i)\[a\_i  \\neq 0\]\[b\_i \\neq 0\]$。两个串完全匹配，则会有$dist(a,b)=0$ 设f\[i\]为串A与串B在i-m+1位置是否完全匹配，那么会有 $$f\[i\]=\\sum_{j=0}^{m-1}(A\[j\]-B\[i-m+1+j\])^2A\[j\]B\[i-m+1+j\]=0$$ 将A串翻转，那么 $$ \\begin{eqnarray*} f\[i\]&=&\\sum_{j=0}^i(A\[j\]-B\[i-j\])^2A\[j\]B\[i-j\]\\\ &=&\\sum_{j=0}^i(A\[j\]^2-2A\[j\]B\[i-j\]+B\[i-j\]^2)A\[j\]B\[i-j\]\\\ &=&\\sum_{j=0}^iA\[j\]^3B\[i-j\]-2\\sum_{j=0}^iA\[j\]^2B\[i-j\]^2+\\sum_{j=0}^iA\[j\]B\[i-j\]^3 \\end{eqnarray*} $$ 明显都是卷积的形式。将字符串看作是一个多项式，三遍FFT求出f的值即可。