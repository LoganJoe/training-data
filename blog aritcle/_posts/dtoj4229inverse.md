---
title: " DTOJ4229Inverse\t\t"
tags:
  - 思路
  - 概率dp
url: 6967.html
id: 6967
categories:
  - DTOJ
  - Solution
date: 2019-03-14 07:46:51
---

考虑dp。 记$f(i,j,k)$为经过$k$次操作后，第$i$个位置上的数小于第$j$个位置上的数的概率。 假设最后一次操作翻转的区间$\[l,r\]$，根据$l,r$和$i,j$的相对关系有四种情况。 第一种是$i<l\\leq r<j$或$l\\leq r<i$或$j<l\\leq r$，这样不会影响位置$i,j$上的数，这样的$l,r$有$\\frac{i(i-1)+(j-i)(j-i-1)+(n-j)(n-j+1)}{2}$对，可以计算出$f(i,j,k)$由$f(i,j,k-1)$转移来的概率。 第二种是$l\\leq i\\leq r<j$，此时$f(i,j,k)$由$f(l+r-i,j,k-1)$转移而来。 记$S\_1(i,j,k)=\\sum\\limits\_{s=1}^i f(s,j,k),S\_2(i,j,k)=\\sum\\limits\_{s=1}^iS\_1(s,j,k)$。 写出转移的式子并化简： $$ \\begin{aligned} f(i,j,k)&=\\sum\_{l=1}^i\\sum_{r=i}^{j-1}f(l+r-i,j,k-1)\\newline &=\\sum_{l=1}^iS\_1(l+j-1-i,j,k-1)-S\_1(l-1,j,k-1)\\newline &=\\sum_{l=1}^iS\_1(l+j-1-i,j,k-1)-\\sum\_{l=1}^iS\_1(l-1,j,k-1)\\newline &=S\_2(i+j-1-i,j,k-1)-S\_2(j-1-i,j,k-1)-S\_2(i-1,j,k-1)+S\_2(-1,j,k-1)\\newline &=S\_2(j-1,j,k-1)-S\_2(j-1-i,j,k-1)-S\_2(i-1,j,k-1) \\end{aligned} $$ 第三种是$i<l\\leq j\\leq r$，此时$f(i,j,k)$由$f(i,l+r-j,k-1)$转移而来。 记$S\_3(i,j,k)=\\sum\\limits\_{s=1}^j f(i,s,k),S\_4=\\sum\_{s=1}^jS\_3(i,s,k)$。 同样化简式子： $$ \\begin{aligned} f(i,j,k)&=\\sum\_{l=i+1}^j\\sum_{r=j}^{n}f(i,l+r-j,k-1)\\newline &=\\sum_{l=i+1}^j S\_3(i,l+n-j,k-1)-S\_3(i,l+j-1-j,k-1)\\newline &=\\sum_{l=i+1}^j S\_3(i,l+n-j,k-1)-\\sum\_{l=i+1}^jS\_3(i,l-1,k-1)\\newline &=S\_4(i,j+n-j,k-1)-S\_4(i,i+n-j,k-1)-S\_4(i,j-1,k-1)+S\_4(i,i-1,k-1)\\newline &=S\_4(i,n,k-1)-S\_4(i,i+n-j,k-1)-S\_4(i,j-1,k-1)+S\_4(i,i-1,k-1) \\end{aligned} $$ 第四种是$l\\leq i< j\\leq r$，此时$f(i,j,k)$由$f(l+r-i,l+r-j,k-1)$转移而来。这一种的化简就有点巧妙了。 记$g(i,j)=f(i+j,j)$，即$f(i,j)=g(i-j,j)$。记$S\_5(i,j,k)=\\sum\\limits _{s=1}^j g(i,s,k),S\_6(i,j,k)=\\sum\_{s=1}^j S\_5(i,s,k)$。 $$ \\begin{aligned} f(i,j,k)&=\\sum\_{l=1}^i\\sum_{r=j}^{n}f(l+r-i,l+r-j,k-1)\\newline &=\\sum_{l=1}^i\\sum_{r=j}^ng(j-i,l+r-j,k-1)\\newline &=\\sum_{l=1}^iS\_5(j-i,l+n-j,k-1)-S\_5(j-i,l+j-1-j,k-1)\\newline &=\\sum_{l=1}^iS\_5(j-i,l+n-j,k-1)-\\sum\_{l=1}^iS\_5(j-i,l-1,k-1)\\newline &=S\_6(j-i,i+n-j,k-1)-S\_6(j-i,n-j,k-1)-S\_6(j-i,i-1,k-1)+S\_6(j-i,-1,k-1)\\newline &=S\_6(j-i,i+n-j,k-1)-S\_6(j-i,n-j,k-1)-S\_6(j-i,i-1,k-1) \\end{aligned} $$ 时间复杂度$\\Theta(n^2k)$。