---
title: " DTOJ2696图森破\t\t"
tags:
  - 数论
url: 923.html
id: 923
categories:
  - Solution
date: 2018-03-05 20:16:10
---

设$f\[i\]$为长度为n的数字（可以有前导$0$）中所有满足条件的数字$X$个数。 那么我们只需要思考如何求值$\\sum_{i=1}^{n}i^2f\[i\]$。 首先是对于f\[i\]的求值。 假设对于一个数字，数字有循环节的情况显然不可取。而对于不存在循环的情况，可以找到一个字典序最小的成为开头。那么由容斥原理可以得到F\[i\]的求值： $$f\[i\]=\\frac{\\sum_{d|i}10^d \\mu(\\frac{i}{d})}{i}$$ 由上，我们可以将所求的式子化为 $$sum_{i=1}^{n}i\\sum_{d|i}10^dμ(\\frac{i}{d})$$ $$=\\sum_{d=1}^{n}dμ(d)\\sum_{i-1}^{\\lfloor \\frac{n}{d}\\rfloor}i10^i$$ 其中的$\\sum_{i-1}^{\\lfloor \\frac{n}{d}\\rfloor}i10^i$可以通过差分化成等比数列的形式。 至于剩下的部分，我们设$g\[d\]=\\sum_{i=1}^{d}i \\mu (i)$，则 $$1=\\sum_{i=1}^{n}i\\sum_{d|i}\\mu(d)=\\sum_{d=1}^{n}\\mu(d)\\sum_{i=1}^{\\lfloor \\frac{n}{d}\\rfloor}id=\\sum_{d=1}^{n}d \\mu (d)\\sum_{i=1}^{\\lfloor \\frac{n}{d}\\rfloor}i$$ 考虑每个$i$贡献的$d\\mu(d)$。显然只有满足$\\lfloor \\frac{n}{d}\\rfloor\\leqslant i$的$d$才会被$i$贡献到，即$d\\leqslant \\lfloor \\frac{n}{i}\\rfloor$。 因此有 $$原式=\\sum_{i=1}^{n}i\\sum_{d=1}^{\\lfloor \\frac{n}{i}\\rfloor}d \\mu (d)=\\sum_{i=1}^{n}ig\[\\lfloor \\frac{n}{i}\\rfloor\]$$ 则$g\[n\]=1-\\sum_{i=2}^{n}ig\[\\lfloor \\frac{n}{i}\\rfloor\]$ 那么我们就可以快速求得答案。 时间复杂度$O(n^{\\frac{2}{3}})$.