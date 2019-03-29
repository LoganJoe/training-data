---
title: " Codeforces Round #429 (Div. 1)（Codeforces840）\t\t"
tags:
  - dp
  - 分块
  - 可持久化线段树
  - 容斥
  - 思路
  - 数学
  - 期望
  - 贪心
url: 3260.html
id: 3260
categories:
  - Codeforces
  - Solution
date: 2018-08-03 22:29:46
---

[A:Leha and Function](https://codeforc.es/contest/840/problem/A)
----------------------------------------------------------------

### 题意

定义函数$F(n,k)$为在$1\\sim n$的集合里选出$k$个数最小值的期望。 给你两个长度为$n$的数列A和B，保证A中的数都比B中的数大。 重新排列A得到A'，使得$\\sum_{i=1}^{n}F(A'\_i,B\_i)$最大。输出A'。

### 题解

感觉这个题很奇怪，求期望却只输出方案。 于是我就先去看了一发样例。发现A大的配B小的，然后我就直接找规律A了…… 提供两种正常的推导…考虑如何求$F(n,k)$。 **第一种** 记我们选出来的$k$个数从小到大分别为$a\_1,a\_2,…,a\_k$，并令$a\_0=0,a_{k+1}=n+1$。 记$d$为$a$的差分，即有$d\_i=a\_i-a_{i-1}$。 那么显然有$\\sum_{i=1}^{n+1}d\_i=n+1$，即$E(\\sum\_{i=1}^{n+1}d\_i)=n+1$。 我们要求的就是$E(a\_1)$，即$E(d\_1)$。 我们发现，对于每个$i$，$E(d\_i)$都是相等的。这个可以意会一下，相当于把$n+1$分成$k+1$，每份的期望大小是一样的。 那么由于期望的线性性，有$E(x+y)=E(x)+E(y)$，那么我们得到 $$\\sum_{i=1}^{k+1}E(d\_i)=E(\\sum\_{i=1}^{n+1}d\_i)$$ 即 $$(k+1)E(d\_1)=n+1$$ 所以有 $$F(n,k)=E(a\_1)=E(d\_1)=\\frac{n+1}{k+1}$$ 那么我们贪心地想，$n,k$肯定差越多越好。因此就是把A中大的分给B中小的。 **第二种** 枚举选出来最小的数$i$，那么我们可以得到 $$ \\begin{aligned} F(n,k)&=\\frac{\\sum_{i=1}^{n-k+1}i\\binom{n-i}{k-1}}{\\binom{n}{k}}\\newline &=\\frac{\\sum_{i=1}^{n-k+1}i\\binom{n-i+1}{k}-\\sum_{i=1}^{n-k}i\\binom{n-i}{k}}{\\binom{n}{k}}\\newline &=\\frac{\\sum_{i=0}^{n-k}\\binom{n-i}{k}}{\\binom{n}{k}}\\newline &=\\frac{\\sum_{i=k}^{n}\\binom{i}{k}}{\\binom{n}{k}}\\newline &=\\frac{\\binom{n+1}{k+1}}{\\binom{n}{k}}\\newline &=\\frac{n+1}{k+1} \\end{aligned} $$ 剩下就和第一种一样了。  

[B:Leha and another game about graph](https://codeforc.es/contest/840/problem/B)
--------------------------------------------------------------------------------

### 题意

$n$个点$m$条边的无向图，有重边但无自环。对于每个点有三种情况：限制度数为奇数/偶数/无限制。 保留边的一个子集，使得满足所有限制。输出选择了哪些边。

### 题解

显然所有点的度数和一定是偶数。所以如果度数奇数的点有奇数个，且没有无限制的点，那么一定无解。 如果度数奇数的点有奇数个，我们随便选一个无限制的点，然后将它变成度数为奇数的点。 我们将度数为奇数的点任意两两配对，然后将两点路径上的边的状态全部取反。 显然这样只会改变路径的两个端点的度数的奇偶性。 具体实现可以在树上打差分标记，或者直接dfs一遍看子树内度数为奇数点的个数。  

[C:On the Bench](https://codeforc.es/contest/840/problem/C)
-----------------------------------------------------------

### 题意

重新排列$n$个数，求任意相邻两个数的乘积都不是平方数的方案数。

### 题解

有一个小结论：如果$ab$和$ac$是平方数，那么$bc$也是平方数。这个可以大概意会一下，证明略了，反正举不出反例233 那么我们可以把$n$个数分成若干组，同一组任选两个数乘积都是平方数，而不在同一组的两个数乘积都不是平方数。 记共有$m$组，第$i$组有$cnt_i$个数。 那么这个就和[DTOJ3745序列排列](http://www.dtenomde.com/2018/06/author=jiangyutong/article=2317/)是相同的了。里面有$\\Theta(n^3)$的做法。 这里再讲一下$\\Theta(n^2)$的写法。 记$f\[i\]\[j\]$为前$i$组，把连续的同组的数当作一块，共有$j$块的方案数。 那我们一组一组地放数，枚举每次放数增加了几块。 那么有 $$ f\[i\]\[j\]\\times \\binom{cnt_{i+1}-1}{k-1}\\times \\binom{j+k}{k}\\times cnt_{i+1}!\\Rightarrow f\[i+1\]\[j+k\] $$ 其中，$\\binom{cnt_{i+1}-1}{k-1}$是将$cnt_{i+1}$个数分成$k$块的方案数，$\\binom{j+k}{k}$是在共$j+k$块中选$k$块作为新增的块，$cnt_{i+1}!$是给这组数定下相对顺序。 最后答案是$f\[m\]\[n\]$。 但我们这样实际求出来的$f\[i\]\[j\]$是块数$\\leqslant j$块的方案数，因为我们选$k$块作为新增的块时，选出的位置也有可能相邻，所以有些块又合并成一块了。 因此我们还需要一个容斥来求出真正的$f\[m\]\[n\]$。 记$g\[i\]$为块数为$i$的方案数。 那么有 $$ g\[i\]=f\[m\]\[i\]-\\sum_{j=1}^{i-1}g\[j\]\\times \\binom{n-j}{i-j} $$ 因为对于块数为$j$的每个方案，不是每块开头的共有$n-j$个位置，这$n-j$个位置每个都可能被当做新的一块的开头算一次贡献，因此要减去。 最后答案就是$g\[n\]$。 时间复杂度看上去是$\\Theta(n^3)$，实际是$\\Theta(n^2)$的。  

[D:Destiny](https://codeforc.es/contest/840/problem/D)
------------------------------------------------------

### 题意

$n$个数$q$次询问，每次询问区间$\[l,r\]$中满足出现次数$>\\frac{r-l+1}{k}$最小的数。

### 题解

发现$k\\leqslant 5$，说明一个区间内只有出现次数最多的五个数才有可能成为答案。 维护区间某个数的出现次数可以用主席树。 但主席树不能维护出现次数最多的数。因为最大值不满足加减的性质。 注意到我们要找的数出现次数很多，且最多只有可能有五个。 我们还是用主席树维护区间某个数的出现次数，对于非叶节点维护的是区间某些数的出现次数和。 那么我们可以每次在主席树上暴力找到合法的叶子节点。 具体地，在主席树上，先往左儿子走，如果找不到合法解就往右儿子走。中途如果这段区间所有数的出现次数和都小于我们要的出现次数，那么就直接return。 这样我们一次询问最多会访问$k$个叶子节点。那么时间复杂度就是$\\Theta(qk\\log n)$  

[E:In a Trap](https://codeforc.es/contest/840/problem/E)
--------------------------------------------------------

### 题意

一棵有$n$个点的树，点$i$的点权为$a\_i$。有$q$次询问，每次询问在$u$到$v$的路径上任选一点$i$，最大的$a\_i\\oplus dist(i,v)$是多少。 其中，$\\oplus$是异或，$dist$是两点之间的边数。保证$u$是$v$的祖先。

### 题解

倍增好像不是很好做。而且效率也很臭。 我们考虑分块。由于效率和路径长度有关，我们把每个点和它上面的$255$个点当成一块，得到了$n$个块。 那么一次询问的路径就能被拆成很多个完整块和一个不完整块。 我们可以暴力求选的点在不完整块中的情况。 现在考虑选的点在完整块中的情况。 显然能表示成$a\_x\\oplus d\\oplus 256k$的形式。其中，$x$是选择的点，$d$是选择的点到块底部的距离，$k$是代表这个块是从下往上第几个块（从$0$开始）。 那么我们只用预处理每个块中对于每个$k$，$a\_x\\oplus d\\oplus 256k$的最大值即可。 记$f\[i\]\[j\]$为块底部是点$i$，当$k=j$时异或的最大值是多少。 我们可以先求出块中所有的$a\_x\\oplus d$，记$a\_x\\oplus d$前面八个二进制位为$v1$，后面八个二进制位为$v2$，那么显然有$f\[i\]\[v1\\oplus 255\]=v2|(255\\times 2^8)$。 对于剩下的情况，可以通过不断取反$j$某一位的状态来实现。具体地，有 $$f\[i\]\[j\]=max(f\[i\]\[j\],f\[i\]\[j\\oplus 2^k\]\\oplus 2^{k+8})$$ 注意要先枚举$k$再枚举$j$，也要注意保证转移是合法的。 那么对于每个询问，选的点在完整块中的答案就是某个$f\[i\]\[j\]$的值，所有的取个max即可。 时间复杂度$\\Theta(256\\times 8q)$。