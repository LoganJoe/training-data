---
title: " DTOJ3959count\t\t"
tags:
  - NTT
  - 斯特林数
url: 4089.html
id: 4089
categories:
  - iftest614
date: 2018-10-06 19:21:54
---

化一下就是$\\frac{i\\varphi(i)}{2}\\times \\frac{1}{\\varphi(i)}\\times 2=i$。

那么要求$\\sum_{i=1}^{n} i^k$。

首先想到自然数幂和。由自然数幂和，即：  

> 考虑计算$S_{n,k}=\\sum_{i=0}^{n}i^k$  
> $$\\begin{aligned} S_{n,k}&=\\sum_{i=0}^ni^k=\\sum_{i=0}^n\\sum_{j=0}^k\\big\\{^k\_j\\big\\}\[i\]\_j \\newline &=\\sum_{j=0}^k\\big\\{^k\_j\\big\\}\\sum\_{i=0}^n\[i\]\_j \\newline &=\\sum\_{j=0}^k\\big\\{^k\_j\\big\\}j!\\sum\_{i=0}^n\\big(^i\_j\\big) \\newline &=\\sum\_{j=0}^k\\big\\{^k\_j\\big\\}j!\\big(^{n+1}\_{j+1}\\big) \\newline \\end{aligned} $$

然后你就可以得到一个在$O(k)$复杂度内计算自然数幂和的公式。

考虑里面那个斯特林数怎么计算。想到：

>   
> 那么，我们单纯考虑第二类斯特林数的组合意义：  
> 假设存在空盒，那么有一个答案就是$m^n$。但是由于不能存在空盒，于是我们枚举空盒个数$k$，然后$(-1)^k$容斥，此时我们$m$个盒子中选出$k$个空盒，然后将$n$个球划分进$m-k$个盒子里，然后消序。因此，我们可以得到另外一个定义等式：  
> $$S(n,m)=\\frac{1}{m!}\\sum_{k=0}^{m}(-1)^k \\binom{m}{k} (m-k)^n$$  
> 另外也有$$S(n,m)=\\frac{1}{m!} \\sum_{k=m}^{n}(-1)^{n-k}S(n,k)k!\\binom{k-1}{m-1}$$
> 
> $$\\begin{aligned}S(n,m)&=\\frac{1}{m!}\\sum_{k=0}^{m}(-1)^k \\binom{m}{k} (m-k)^n \\newline &=\\frac{1}{m!}\\sum_{k=0}^{m}(-1)^k\\frac{m!}{k!(m-k)!}(m-k)^n \\newline &= \\sum_{k=0}^{m}\\frac{(-1)^k}{k!}\\frac{(m-k)^n}{(m-k)!} \\end{aligned}$$

于是就可以用NTT加速多项式乘法在$O(k \\log\ k)$的效率内计算出第二类斯特林数。于是自然数幂和就可以在$O(k\ log \ k)$的时间复杂度内解决了。

坑点是$\\varphi(1)=1$，于是$f(1)=2$，这导致了你需要特判一下十分狗屎。

挂分30。

还有NTT自带大常数所以，对于标程那个同样复杂度的算法这玩意会被大力卡常。

然后我就过了。