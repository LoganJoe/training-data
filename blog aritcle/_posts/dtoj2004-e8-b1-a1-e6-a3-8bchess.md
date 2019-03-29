---
title: " DTOJ2004象棋Chess\t\t"
tags:
  - dp
url: 3422.html
id: 3422
categories:
  - DTOJ
  - Solution
date: 2018-08-12 17:33:01
---

题意就是每行每列至多两个炮的方案数。 我们考虑dp：记$f\[i\]\[j\]\[k\]$为前$i$行，有$j$列已经有一个炮，有$k$列是空的方案数。 考虑当前列要放几个，要放在空列还是已经放了一个炮的列，然后乘上方案数转移。 具体地，转移有 $$f\[i\]\[j\]\[k\]\\Rightarrow f\[i+1\]\[j\]\[k\]$$ $$f\[i\]\[j\]\[k\]\\times j\\Rightarrow f\[i+1\]\[j-1\]\[k\]$$ $$f\[i\]\[j\]\[k\]\\times k\\Rightarrow f\[i+1\]\[j+1\]\[k-1\]$$ $$f\[i\]\[j\]\[k\]\\times \\frac{j(j-1)}{2}\\Rightarrow f\[i+1\]\[j-2\]\[k\]$$ $$f\[i\]\[j\]\[k\]\\times \\frac{k(k-1)}{2}\\Rightarrow f\[i+1\]\[j+2\]\[k-2\]$$ $$f\[i\]\[j\]\[k\]\\times j\\times k\\Rightarrow f\[i+1\]\[j\]\[k-1\]$$