---
title: " BZOJ4652[Noi2016]循环之美\t\t"
tags:
  - 思路
  - 数论
  - 杜教筛
url: 6007.html
id: 6007
categories:
  - BZOJ
  - Solution
date: 2019-02-02 17:51:04
---

真是道神题。 我们先搞清楚它题目要让我们求什么…… 相同的分数只算一次，我们不妨将分数化至最简。 考虑$\\frac x y$，它是最简的条件是$gcd(x,y)=1$。 接下来我们考虑如何判断$\\frac x y$是不是纯循环的。 显然纯循环只和分母$y$有关，因为一个纯循环的分数的若干倍仍然是纯循环的。 不妨先考虑十进制的情况。 举了几个例子后我们发现都有$gcd(y,10)=1$。 不妨大胆猜想：在$k$进制下分数$\\frac x y$是纯循环的当且仅当$gcd(y,k)=1$。 证明请看[这](https://www.cnblogs.com/lcf-2000/p/6250330.html)。 那我们就可以开始推式子了。 $$ \\begin{aligned} &=\\sum_{i=1}^n \\sum_{j=1}^m\[gcd(i,j)=1\]\[gcd(j,k)=1\]\\newline &=\\sum_{j=1}^m \[gcd(j,k)=1\]\\sum_{i=1}^n \[gcd(i,j)=1\]\\newline &=\\sum_{j=1}^m \[gcd(j,k)=1\]\\sum_{i=1}^n\\sum_{d|i,d|j}\\mu(d)\\newline &=\\sum_{j=1}^m \[gcd(j,k)=1\]\\sum_{d|j}\\mu(d)\\left \\lfloor \\frac{n}{d}\\right \\rfloor \\newline &=\\sum_{d=1}^{\\min(n,m)}\\mu(d)\\left \\lfloor \\frac{n}{d}\\right \\rfloor \\sum_{j=1}^{\\left \\lfloor \\frac m d \\right \\rfloor}\[gcd(jd,k)=1\]\\newline &=\\sum_{d=1}^{\\min(n,m)}\[gcd(d,k)=1\]\\mu(d)\\left \\lfloor \\frac{n}{d} \\right \\rfloor \\sum_{j=1}^{\\left \\lfloor \\frac m d \\right \\rfloor}\[gcd(j,k)=1\] \\end {aligned} $$ 最后一步用到了互质的一个性质：$gcd(ab,c)=1$等价于$gcd(a,c)=1$且$gcd(b,c)=1$。应该比较好理解，不证明了。 设$F(x)=\\sum_{i=1}^{x}\[gcd(i,k)=1\],S(x,k)=\\sum_{i=1}^x \[gcd(i,k)=1\]\\mu(i)$。 知道了$F(x)$后面那个$\\sum$就可以$\\Theta(1)$算，知道了$S(x,k)$前面就可以用整除分块优化到$\\Theta(\\sqrt n)$。 先考虑$F(x)$。 根据$gcd$的性质，如果有$gcd(a,b)=1$，那么$gcd(a+tb,b)=1,t\\in \\mathbb{Z}$。 那么有 $$ F(x)=\\left \\lfloor \\frac{x}{k}\\right \\rfloor F(k)+F(x\\%k) $$ 那么只要预处理出$<k$的$F(x)$就可以$\\Theta(1)$算了。 再考虑$S(x,k)$。有 $$ \\begin{aligned} S(x,k)&=\\sum_{i=1}^x\[gcd(i,k)=1\]\\mu(i)\\newline &=\\sum_{i=1}^x\\mu(i)\\sum_{d|i,d|k}\\mu(d)\\newline &=\\sum_{d|k}\\mu(d)\\sum_{i=1}^{\\left \\lfloor \\frac{x}{d}\\right \\rfloor}\\mu(id) \\end{aligned} $$ 如果$gcd(i,j)\\neq 1$，那么$\\mu(id)=0$，对答案没有贡献。 如果$gcd(i,j)=1$，由于$\\mu(x)$是积性函数，那么有$\\mu(id)=\\mu(i)\\mu(d)$。 我们继续化简 $$ \\begin{aligned} S(x,k)&=\\sum_{d|k}\\mu(d)^2\\sum_{i=1}^{\\left \\lfloor \\frac{x}{d}\\right\\rfloor}\[gcd(i,d)=1\]\\mu(i) \\end{aligned} $$ 这个东西是不是有点似曾相识？ 看一看$S(x,k)$的定义，发现 $$ S(x,k)=\\sum_{d|k}\\mu(d)^2S(\\left \\lfloor \\frac{x}{d}\\right \\rfloor,d) $$ 当$k=1$的时候，就是求$\\mu(i)$的前缀和，那么杜教筛一下即可。 时间复杂度是多少我也不知道……不过前面放的链接的题解有证，对不对我也不知道。