---
title: " 生成函数基础\t\t"
tags:
  - 生成函数
url: 5343.html
id: 5343
categories:
  - Algorithm
date: 2019-01-01 23:51:12
---

### 生成函数

生成函数也叫发生函数或者母函数。生成函数可以为数列找出一个显式表示式，以方便对于序列找出其他优秀的统计性质。生成函数是lzx的最爱。在学习生成函数前，强烈建议首先了解导函数、定积分、多重积分、泰勒展开的有关内容。浅显的表示，导函数是函数在某一点上取得的切线的斜率，定积分是函数在关于x轴围成的面积，多重积分是对于单函数积分在多函数下而言的，不定积分可以用来方便的求出定积分。

我们首先定义两个东西。对于一个数列${a\_n}\_0^{\\infty}$,其普通形式幂级数为

$$  
f(x)=a\_0+a\_1x+a\_2x^2+…=\\sum\_{i=0}^{\\infty}a_nx^n  
$$

其指数型幂级数为

$$  
f(x)=a\_0+\\frac{a\_1}{1!}x+\\frac{a\_2}{2!}x^2+…=\\sum\_{i=0}^{\\infty}\\frac{a_n}{n!}x^n  
$$

我们称第一种为普通生成函数，第二种为指数生成函数，这是生成函数最一般的两种定义，其他在OI中接触较少，按下不表。

那么生成函数的实质，就是把组合问题的加法法则和幂级数的乘幂对应起来。生成函数的思想很简单 ：就是把离散数列和幂级数一 一对应起来，把离散数列间的相互结合关系对应成为幂级数间的运算关系，最后由幂级数形式来确定离散数列的构造. “

#### 普通生成函数（OGF）

对于一个数列 $f$ ，构造形式幂级数  
$$  
F(x) = \\sum_{i=0}^{\\infty}f_ix^i  
$$

称为数列$f$的普通型生成函数（ordinary generating function, 下简称OGF）。

举个栗子，当$A$表示不同的01串个数时，$A(x)=1+2x+4x^2+8x^3+…=\\frac{1}{1−2x}$

一些常见的OGF有：

数列

OGF

$<1,0,0,\\dots>$

$1$

$<1,1,1,\\dots>$

$\\frac1{1-x}$

$<1,2,3,\\dots>$

$\\frac1{(1-x)^2}$

$<1,-1,1,-1,\\dots>$

$\\frac1{1+x}$

$<1,2,1,0,0,\\dots>$

$(1+x)^2$

$<1,4,6,4,1,0,0,\\dots>$

$(1+x)^4$

首先了解一下生成函数的一些运算。设${a\_k}，{b\_k}，{c_k}$是已知的序列，它们的普通型生成函数分别为$A(x)，B(x)，C(x)$。

1.  若$b\_k=αa\_k$，$α$为常数，则$B(x)=\\alpha A(x)$称为$A(x)$的常数倍。
2.  若$c\_k=a\_k+b_k$，则$C(x)=A(x)+B(x)$称为$A(x)$与$B(x)$的和。
3.  若$c\_k=\\sum \_{i=0}^{k}a\_ib\_{k−i}$，则$C(x)=A(x)B(x)$称为$A(x)$与$B(x)$的积。

这一部分的运算与多项式十分类似。对于积，我们可以用FFT优化多项式乘法的方式来解决。

那么我们也可以通过上面三条定理得到如下引理：  
$$  
\\begin{aligned} \\alpha F(x)+\\beta G(x)&=\\sum\_n(\\alpha f\_n+\\beta g\_n)x^n\\newline x^mF(x)&=\\sum\_n\[n\\geq m\]f_{n-m}x^n\\newline \\frac{F(x)-\\sum_{i=0}^{m-1}f\_ix^i}{x^m}&=\\sum\_nf_{n+m}x^n\\newline F(cx)&=\\sum\_nc^nf\_nx^n\\newline F^\\prime(x)&=\\sum\_n(n+1)f\_{n+1}x^n\\newline \\int\_0^xF(x)\\mathrm{d}x&=\\sum\_n\[n>0\]\\frac{f_{n-1}}nx^n\\newline F(x)G(x)&=\\sum\_n\\left(\\sum\_{i=0}^nf\_ig\_{n-i}\\right)x^n \\end{aligned}  
$$  
上面均有$n \\in \[0,\\infty\]$。  
其中不难发现，多项式运算与OGF的紧密联系。于是我们可以得到下面的式子：

数列

OGF

$<1,c,c^2,c^3,\\dots>$

$\\frac1{1-cx}$

$<1,n,\\binom n2,\\binom n3,\\dots>$

$(1+x)^n$

$<1,n+1,\\binom{n+1}2,\\binom{n+1}3,\\dots>$

$(1-x)^{-n}$

$<0,1,\\frac12.\\frac13,\\dots>$

$\\ln\\frac1{1-x}$

$<0,1,-\\frac12.\\frac13,-\\frac14,\\dots>$

$\\ln(1+x)$

$<1,1,\\frac12,\\frac16,\\frac1{24},\\dots>$

$e^x$

#### 指数生成函数（EGF）

对于带标号对象组成的集合$A$，定义其指数型生成函数（exponential generating function，简称EGF）：

$$  
F(x)=\\sum_{n=0}^{\\infty}f_n\\frac{x^n}{n!}  
$$

然后我们发现，这个玩意就比上面的OGF多了一个$\\frac{1}{n!}$。这个多出来的东西有什么用呢？  
其其他运算都和OGF大致类似，但是其乘法运算：  
$$  
F(x)G(x)=\\sum\_n\\left(\\sum\_{i=0}^n\\binom nif\_ig\_{n-i}\\right)\\frac{x^n}{n!}  
$$  
其中那个二项式系数是考虑两个卷积相乘与$n!$凑出来的结果。如果$x^n$上的系数表示的是选择$n$个该物品的方案数，那么$F(x) G(x)$的$x^n$的系数表示的就是从$a$和$b$中选出$n$个物品的排列数。

同样的对于EGF，有如下运算法则：  
$$  
\\begin{aligned} \\alpha F(x)+\\beta G(x)&=\\sum\_n(\\alpha f\_n+\\beta g\_n)\\frac{x^n}{n!}\\newline x^mF(x)&=\\sum\_n\[n\\geq m\]n^{\\underline m}f_{n-m}\\frac{x^n}{n!}\\newline \\frac{F(x)-\\sum_{i=0}^{m-1}f\_ix^i}{x^m}&=\\sum\_n\\frac1{(n+m)^{\\underline m}}f_{n+m}\\frac{x^n}{n!}\\newline F(cx)&=\\sum\_nc^nf\_n\\frac{x^n}{n!}\\newline F^\\prime(x)&=\\sum\_nf\_{n+1}\\frac{x^n}{n!}\\newline \\int\_0^xF(t)\\mathrm{d}t&=\\sum\_n\[n>0\]f_{n-1}\\frac{x^n}{n!}\\newline F(x)G(x)&=\\sum\_n\\left(\\sum\_{i=0}^n\\binom nif\_ig\_{n-i}\\right)\\frac{x^n}{n!} \\end{aligned}  
$$  
同样有一些基本的EGF：

数列

EGF

$<1,1,1,\\dots>$

$e^x$

$<0,1,2,\\dots>$

$xe^x$

$<1,c,c^2,\\dots>$

$e^{cx}$

$\\dots$

$\\dots$

### 生成函数的应用

#### Fibonacci

$$  
f\_n=\\begin{cases}n&n=1\\\ f\_{n-1}+f_{n-2}&n>1\\end{cases}  
$$

简单的Fibonacci数列。其OGF有

$$  
\\begin{aligned} F(x)&=\\sum\_nf\_nx^n\\\ &=\\sum\_n(f\_n+f_{n-1}+\[n=1\])x^n\\\ &=F(x)+xF(x)+x \\end{aligned}  
$$  
从中我们解出  
$$  
F(x)=\\frac{x}{1-x-x^2}  
$$  
我们令$\\varphi=\\frac{1+\\sqrt5}{2},\\varphi^{-1}=\\frac{1-\\sqrt5}2$，可以计算出$F(x)=\\frac{1}{\\sqrt5}\\left(\\frac1{1-\\varphi x}-\\frac1{1+\\varphi^{-1} x}\\right)$

根据$\\frac1{1-cx}=\\sum\_nc^nx^n$，我们可以知道$f\_n=\\frac1{\\sqrt5}\\left(\\varphi^n-\\hat\\varphi ^n\\right)$。

#### Catalan

以下是一个我不会的生成函数的例子。

众所周知的Catalan数列的生成函数如何呢？  
$$  
f\_n=\\begin{cases}1&n=0\\\sum\_{i=0}^{n-1}f\_if\_{n-i-1}&n>0\\end{cases}  
$$  
则  
$$  
\\begin{aligned} F(x)&=\\sum\_n\\left(\[n=0\]+\\sum\_{i=0}^{n-1}f\_if\_{n-i-1}\\right)x^n\\\ &=1+x\\sum\_n\\left(\\sum\_{i=0}^{n-1}f\_if\_{n-1-i}\\right)x^{n-1}\\\ &=1+xF^2(x) \\end{aligned}  
$$  
亦即知$xF^2-F+1=0$。代入二次方程求根公式，我们可以得到  
$$  
F(x)=\\frac{1\\pm\\sqrt{1-4x}}{2x}  
$$  
然而$\\pm$取哪一个呢？我们发现一个数列f的生成函数$F$一定满足$F(0)=f\_0$（某些情况下或许应该写成$\\lim\_{x\\to0}F(x)=f\_0$）。然而$f\_0=1$，这意味着$F(0)=1$。而如果我们令$\\pm$取$+$，那么$F(0)=\\frac20$是未定义的，这显然不是一个多项式应有的表现。

于是我们得到：Catalan数的生成函数是$\\frac{1-\\sqrt{1-4x}}{2x}$。这个生成函数令人有点难以置信，我们可以尝试展开它Warning!!!。

展开它的方式是$(x+y)^c=\\sum_i\\binom cix^iy^{c-i}$在等式右端收敛的情况下得到等号。然而生成函数是**形式**幂级数，这意味着我们**不需要考虑收敛性**。

于是 $$\\sqrt{1-4x}=\\sum\_n\\binom{\\frac12}{n}(-4x)^n$$ $$\\begin{aligned}\\because\\binom{\\frac{1}{2}}n&=\\frac{\\frac12(\\frac12-1)\\dots(\\frac12-n+1)}{n!} \\newline &=\\frac{(-1)^{n-1}1\\times1\\times3\\times\\dots\\times(2n-3)}{2^nn!}\\newline &=\\frac{(-1)^{n-1}(2n-2)!}{2^{2n-1}n!(n-1)!}\\end{aligned}$$ $$\\therefore\\sqrt{1-4x}=\\sum\_n\\binom{\\frac{1}{2}}{n}(-4x)^n=-2\\sum_n\\frac{(2n-2)!}{n!(n-1)!}x^n $$

  
这意味着$\\frac{1-\\sqrt{1-4x}}{2x}=\\sum_n\\frac{(2n)!}{n!(n+1)!}x^n$，正是Catalan数的通项公式。

#### Bell

以下又是一个我不会的生成函数的例子。

贝尔数$\\omega_n$是把大小为$n$的子集分割成若干非空不相交子集的方案数。

通过枚举第一个元素所在的子集大小$i$，我们可以得到  
$$  
\\omega\_n=\[n=0\]+\\sum\_{i=1}^n\\binom{n-1}{i-1}\\omega_{n-i}  
$$  
于是其EGF满足  
$$  
F(x)=1+\\int_0^xe^tF(t)\\mathrm{d}t  
$$  
两边求导  
$$  
\\begin{aligned} F^\\prime(x)&=e^xF(x)\\newline \\frac{\\mathrm{d}F}{\\mathrm{d}x}&=e^xF(x)\\newline \\frac{\\mathrm{d}F}F&=e^x\\mathrm{d}x\\newline \\int\\frac{\\mathrm{d}F}F&=\\int e^x\\mathrm{d}x\\newline \\ln F&=e^x+C\\newline F&=e^{e^x+C}\\newline \\end{aligned}  
$$  
把$F(0)=\\omega\_0=1$代入即得$F(x)=e^{e^x-1}$。这个多项式的系数可以利用$e^g=\\sum\_n\\frac{g^n}{n!}$计算。

$F(x)=e^{e^x-1}$也可以这样理解：$g(x)=e^x-1$的$n$次项系数是“$n$个数组成一个非空集合”的方案数（显然），而$g^c(x)$的$n$次项系数（由于EGF对应排列）就是“$n$个数划分成$c$个非空集合”的方案数。而由于这$c$个集合是不可区分的，所以要乘上$\\frac1{c!}$。于是我们得到  
$$  
F(x)=\\sum_n\\frac{g^n(x)}{n!}=e^{g(x)}=e^{e^x-1}  
$$

#### 多重集组合问题

考虑如下的经典问题：对于非负整数$x\_1,x\_2,x\_3,…x\_k$,求$x\_1+x\_2+x\_3+..+x\_k=n$有多少组非负整数解。  
我们可以为每个变量构造一个生成函数，这里每个的权值都是1，所以每个变量得到的生成函数均为$1+x+x^2+…+x^n+…$(不选为$1$，选$i$个为$x^i$，这里变量的取值没有限制，所以生成函数有无穷多项)，变量的组合相加对应于生成函数的乘积，这样我们将这些多项式相乘得到$f(x)=(1+x+x^2+…+x^n+..)^k$，将$f(x)$展开，则其中$xn$这一项的系数即为此方程解的个数。

那么有$\\sum_{i=0}^{\\infty}x^{ki}=\\frac{1}{1−x^k}$

广义二项式反演，可得

$f(x) = (1-x)^{-k}=\\sum_{n=0}^{\\infty}{n+k-1 \\choose k-1}x^n$

这和我们隔板法得到的是一致的。

如果没办法像上面的例子一样通过公式化简怎么办？那么我们可以考虑使用背包dp来计数。