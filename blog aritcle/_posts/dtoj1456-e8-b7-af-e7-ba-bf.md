---
title: " DTOJ1456路线\t\t"
tags:
  - 树形dp
url: 6184.html
id: 6184
categories:
  - DTOJ
  - Solution
date: 2019-01-24 21:57:57
---

考虑树形dp。 记$f\[i\]\[j\]$为$i$个点深度为$j$的树的个数。 我们可以枚举左右子树的大小和最深的深度转移。 具体地，有 $$ f\[i\]\[d\_1\]\\times f\[j\]\[d\_2\]\\Rightarrow f\[i+j+1\]\[\\max(d\_1,d\_2)+1\] $$ 考虑改写成主动转移的形式。 $$ \\begin{aligned} f\[i\]\[j\]&=2f\[i-1\]\[j-1\]\\newline &+\\sum_{k=1}^{i-2}f\[k\]\[j-1\]\\sum_{s=0}^{j-1}f\[i-k-1\]\[s\]\\newline &+\\sum_{k=1}^{i-2}f\[i-k-1\]\[j-1\]\\sum_{s=0}^{j-2}f\[k\]\[s\] \\end{aligned} $$ 这样是$\\Theta(n^4)$的。 容易发现可以用前缀和优化到$\\Theta(n^3)$。不是很满，可以过。