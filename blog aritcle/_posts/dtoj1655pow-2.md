---
title: " DTOJ1655Pow\t\t"
tags:
  - 定理
url: 3127.html
id: 3127
categories:
  - DTOJ
  - Solution
date: 2018-07-28 14:34:58
---

求幂大法：拓展欧拉定理。

*   当$a,p$互质时，有$a^b\\equiv a^{b\\%\\varphi(p)}(mod\\space p)$
*   当$a,p$不互质时，有$a^b\\equiv a^{b\\%\\varphi(p)+\\varphi(p)}(mod\\space p)(b \\geqslant \\varphi(p))$

预处理出每个数的$\\varphi$，然后从里到外一层一层求即可。 判断$b\\geqslant \\varphi(p)$时在快速幂过程中判一下。