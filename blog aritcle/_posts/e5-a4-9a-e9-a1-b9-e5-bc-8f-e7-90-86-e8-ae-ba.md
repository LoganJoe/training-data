---
title: " 多项式理论\t\t"
tags:
  - 多项式
url: 6081.html
id: 6081
categories:
  - Algorithm
date: 2019-01-17 19:01:13
---

### 泰勒展开

$$  
\\begin{split} f(x)&=f(x\_0)+f'(x\_0)(x-x\_0)+f''(x\_0)\\int_{x\_0}^x (x-x\_0){\\rm d}x+f'''(x\_0)\\iint\_{x\_0}^x (x-x\_0) {\\rm d}x + \\ldots \\\ &=f(x\_0)+f'(x\_0)(x-x\_0) + f''(x\_0)\\cdot \\frac{1}{2} (x-x\_0)^2 + f'''(x\_0)\\cdot \\frac{1}{2}\\cdot \\frac{1}{3} (x-x\_0)^3 + \\ldots \\\ &=f^{(0)}(x\_0)\\frac{1}{0!}(x-x\_0)^0+f'(x\_0)\\frac{1}{1!}(x-x\_0)^1 + f''(x\_0)\\frac{1}{2!} (x-x\_0)^2 + f'''(x\_0)\\frac{1}{3!}(x-x\_0)^3 + \\ldots \\\ &=\\sum\_{i=0}^{+\\infty} f^{(i)}(x\_0)\\frac{1}{i!}(x-x\_0)^i \\end{split}  
$$

其中,$f^{(i)}(x)$表示$f(x)$的$i$阶导。

**泰勒展开式就是基于对线性逼近的无限次运用而得到的。**

### 形式导数

对于$A(x)=\\sum_{i \\ge 0}a\_ix\_i$,定义$A(x)$的形式导数为  
$$  
A'(x)=\\sum_{i \\ge 1}ia\_ix\_{i-1}  
$$  
容易验证  
$$  
\\begin{aligned}  
(cA(x))'&=cA'(x)\\newline  
(A(x) \\pm B(x))'&=A'(x)\\pm B'(x)\\newline  
(A(x)B(x))'&=A'(x)B(x)+A(x)B'(x)\\newline  
\\left(\\frac{1}{A(x)}\\right)&=-\\frac{A'(x)}{A^2(x)}\\newline  
(A(B(x)))'&=A'(B(x))B'(x)  
\\end{aligned}  
$$  
这些求导法则仍然可以推广到多项式中。

### 多项式求逆

考虑乘法逆元在多项式下的定义。对于两个多项式$A(x),B(x)$，当$A(x)B(x)=1$时，称$A(x),B(x)$互为多项式意义下的乘法逆元。那么除以一个形式幂级数，就相当于乘上它的乘法逆元。假设有  
$$  
\\frac{1}{x}=1+x+x^2+x^3+…+\\Lambda  
$$  
那么假设${a\_n}$的OGF为$A(x)$，令$s\_n=\\sum_{i=0}^{n}a\_i$，那么$s\_0,s_1,\\dots,$的OGF为$A(x)/(1-x)$。

那么有  
$$  
\\frac{1}{(1−x)^{n+1}}  
=\\sum_{i=0}^{\\infty}\\binom{n + i}{ n}x^i  
$$  
考虑给出多项式$A(x)$，求多项式$B(x)$，使得$ A(x)B(x) \\equiv 1 \\mod{x^n} $

首先令$a\_0b\_0 \\equiv 1 \\mod {x},n=1$  
$$  
\\begin{aligned}  
A(x)B(x) &\\equiv 1 \\mod {x^n} \\newline  
A(x)B(x)-1&\\equiv0 \\mod {x^n} \\newline  
(A(x)B(x)-1)^2 &\\equiv 0 \\mod{x^{2n}}\\newline  
A^2(x)B^2(x) −2A(x)B(x) &\\equiv 1 \\mod x^{2n} \\newline  
A(x)(A(x)B^2(x) −2B(x)) &\\equiv 1 \\mod x^{2n}  
\\end{aligned}  
$$  
那么$A(x)B^2(x) −2B(x)$就是在$\\mod {x^{2n}}$下新的逆元。

那么我们每次在$\\Theta(n \\log n)$下计算出在$2$倍次数界上的新乘法逆元，并且将其进行下一轮迭代。那么一直迭代下去就可以得到$N=n$下的逆元了。时间复杂度应用master定理分析为$\\Theta(n \\log n)$。一个多项式有没有逆元完全取决于其常数项是否有逆元。

**例题**

对于所有$i\\in \[0,n-1\]$求出Bernoulli数$B_i$。

Bernoulli数$B\_0,B\_1,\\dots$的EGF为  
$$  
\\begin{aligned}  
B(x) &=\\sum_{i=0}^{\\infty}Bi\\frac{x_i}{i!}\\newline  
&=\\frac{x}{e^x-1}\\newline  
&=(\\sum_{i=0}^{\\infty}\\frac{x^i}{(i+1)!})^{-1}  
\\end{aligned}  
$$

对其中这个东西求多项式逆元就可以快速求bernouii数了。

### 多项式ln

首先有  
$$  
\\ln(1−A(x)) = −\\sum_{i\\ge 1} A^i(x)  
$$

这个是关于形式幂级数的对应麦克劳林级数的复合。

对于给出的多项式$A(x)=1+\\sum_{i\\ge 1}a\_ix\_i$求$B(x)$满足  
$$  
B(x)=\\ln(A(x))  
$$  
我们考虑对于所求的$B(x)$求导，那么会有  
$$  
(\\ln(A(x)))'=\\frac{A'(x)}{A(x)}  
$$

$$  
\\ln(A(x))=\\int \\frac{A'(x)}{A(x)}  
$$

那么其不定积分就很好求了。

### 多项式exp

$$  
exp(A(x)) = e^{A(x)} =\\sum_{i=0}^{\\infty} \\frac{A^i(x)}{ i!}  
$$  
这个展开可以由泰勒展开得来。

给出多项式 $A(x)$，求多项式 $B(x) \\equiv e^{A(x)} \\mod {x^n}$ 。

考虑对于多项式$f(x)$的函数$g(f(x))=\\ln f(x)-A(x)=0$,以及设$C(x)\\equiv e^{A(x)} \\mod x^n$。应用泰勒展开一次，有

$$  
\\begin{aligned}  
g(B(x))&=g(C(x))+g'(C(x))(B(x)-C(x))+\\frac{g''(C(x))(B(x)-C(x))^2}{2!}+… \\newline  
&\\equiv g(C(x))+g'(C(x))(B(x)-C(x)) \\mod{x^{2n}}  
\\end{aligned}  
$$  
带入前设定义，有

$$  
\\begin{aligned}  
B(x)&\\equiv C(x)-\\frac{g(C(x))}{g'C(x)} \\newline &\\equiv C(x)+\\frac{A(x)-\\ln C(x)}{\\frac{1}{C(x)}} \\newline &\\equiv C(x)(1-\\ln C(x)+A(x))  
\\end{aligned}  
$$

### 计算任意次幂

给出一个多项式 $A(x)$，你现在要计算 $A^k(x), k \\in \\mathbb Q$

对于 $k \\in \\mathbb N$ 的部分，可以直接使用快速幂来计算，这样复杂度是 $\\Theta(n\\log n\\log k)$

现在有了求指数和求对数的运算，那么$A^k(x) = e^{k \\ln A(x)}$

这样就可以在 $\\Theta(n\\log n)$ 的时间内计算出 $A^k(x)$，包括开方等也可以这样来计算。

### 多项式开根

像多项式求逆那样考虑倍增：

同样地，假设我们已经求出$G(x)$使得$G^2(x)\\equiv{A(x)}\\mod x^{n}$，则有：

$$  
\\begin{aligned}  
G^2(x)-B^2(x) &\\equiv 0\\mod x^{n} \\newline  
(G(x)+B(x))(G(x)-B(x))&\\equiv 0 \\mod x^n  
\\end{aligned}  
$$  
因为是平方，所以会有两个解。我们不妨令$G(x)-B(x)\\equiv0\\mod x^n$，平方后则有：  
$$  
G^2(x)+B^2(x)-2G(x)B(x)\\equiv0 \\mod x^{2n}  
$$  
因为$B^2(x)\\equiv{A(x)} \\mod x^{2n}$，所以：  
$$  
B(x)\\equiv{\\frac{A(x)+G^2(x)}{2G(x)}} \\mod x^{2n}  
$$  
那么后面那个东西就是倍增一次次数界后的$B(x)$了。 每次需要一次多项式求逆和多项式卷积，相当于一个$\\Theta(n \\log n)=T(14 n \\log n)$。算上常数离$T(n^2)$不远了…

### 牛顿迭代

不会…。

好，现在问题是这样的，已经知道了一个函数 $A(x)$，求一个多项式 $B(x) \\bmod {x^n}$，满足方程  
$$  
A(B(x)) \\equiv 0 \\mod {x^n}  
$$  
首先 $n = 1$ 的时候，$A(B(x)) \\equiv 0 \\bmod z$，这是要单独求出来的

现在假设已经求出了  
$$  
A(B_0(x)) \\equiv 0 \\mod {x^{\\lceil \\frac{n}{2} \\rceil}}  
$$  
考虑如何扩展到 $\\bmod x^n$ 下，可以把 $A(B(x))$ 在 $B_0(x)$ 这里进行泰勒展开  
$$  
\\begin{aligned} A(B(x)) & = A(B\_0(x)) \\newline & + \\frac{A'(B\_0(x))}{1!}\\left(B(x) - B\_0(x)\\right) \\newline & + \\frac{A''(B\_0(x))}{2!}\\left(B(x) - B_0(x)\\right)^2 \\newline & + \\cdots \\end{aligned}  
$$

因为 $B(x)$ 和 $B\_0(x)$ 的最后 $\\lceil \\frac{n}{2} \\rceil$ 项相同，所以 $\\left(F(x) - F\_0(x)\\right)^2$ 的最低的非 $0$ 项次数大于 $2\\lceil \\frac{n}{2} \\rceil$，所以可以得到  
$$  
A(B(x)) \\equiv A(B\_0(x)) + A'(B\_0(x))\\left(B(x) - B_0(x)\\right) \\mod {x^n}  
$$  
然后因为 $A(B(x)) \\equiv 0 \\mod {x^n}$，可以得到  
$$  
B(x) \\equiv B\_0(x) - \\frac{A(B\_0(x))}{A'(B_0(x))} \\mod {x^n}  
$$

### 复合与复合逆

定义两个形式幂级数的复合。

设$A(x)=\\sum_{i=0}^{\\infty}a\_ix^i,B(x)=\\sum\_{i=1}^{\\infty}b_ix^i$

我们定义$A(x)$对于$B(x)$的复合：

$$  
C ( x ) = A \\circ B ( x ) = A ( B ( x ) ) = \\sum _ { i = 0}^{\\infty} a _ { i } B^i ( x )  
$$  
可以将其整理为$C(x)=\\sum_{i=0}^{\\infty}c_ix^i$的形式，也就是说，$A(B(x))$的复合，相当于多项式幂的复合，其最后得到的是另外一个形式幂级数。

注意到，在上边关于$B(x)$的定义中，幂级数是不具有非零项的。这样的话，无论$A(x)$具有多少非零项，我们仍然可以写出$B(x)$关于$A(x)$的复合。

接下来考虑复合逆。同样我们考虑上列两个形式幂级数。假设对于$A(x)$对于$B(x)$的复合有$A(B(x))=x$,那么我们认为$A(x),B(x)$是互为复合逆的。即$A(x),B(x)$互为反函数。这样，我们将求逆运算拓展到了复合领域。

对于多项式的复合，我们注意到其中有应用到求$B^i(x)$的部分。回顾前面的关于对数与指数函数的麦克劳林复合定义，那么我们可以用多项式取$exp$算出这个这个部分。也就是说，我们可以对于$A(x)$取ln后与$B(x)$对应项复合再exp来得到两个多项式的复合逆。

### 拉格朗日反演

若$f(w)$是$g(x)$的复合逆：  
$$  
\\left\[ x ^ { n } \\right\] g ( x ) = \\frac { 1 } { n } \\left\[ w ^ { n - 1 } \\right\] \\left( \\frac { w } { f ( w ) } \\right) ^ { n }  
$$  
它具有一个推广形式：  
$$  
\\left\[ x ^ { n } \\right\] h ( g ( x ) ) = \\frac { 1 } { n } \\left\[ w ^ { n - 1 } \\right\] h ^ { \\prime } ( w ) \\left( \\frac { w } { f ( w ) } \\right) ^ { n }  
$$  
可以在$O(n \\log n)$内求出某一项的系数。

### 多项式除法与多项式求模

考虑给出一个$n$次多项式$A(x)$和一个$m$次多项式$B(x)$。其中满足$m \\leq n$。要求其在模意义下的余多项式$R(x)$与商多项式$D(x)$。即：求得两个多项式$D(x),R(x)$，满足  
$$  
A(x)=D(x)B(x)+R(x)  
$$  
其中，一定会有$degD\\leq degA-degB=n-m,degR<m$。

考虑先行消去$R(x)$的影响，方便求出$D(x)。我们记一个$n$次多项式$A(x)$的系数翻转$A^R(x)$:

$$  
A^R(x)=x^nA(\\frac{1}{x})  
$$

系数反转可以用如下例子理解：  
$$  
\\begin{aligned}  
A(x)&=x^3+2x^2+4x+6\\newline  
A^R(x)&=x^3A\\left(\\frac{1}{x}\\right)\\newline&=1+2x+4x^2+6x^3  
\\end{aligned}  
$$  
回过头来考虑我们要满足的式子，对于所有的多项式均进行$\[x^n\]$系数翻转：  
$$  
\\begin{aligned}  
x^n A(\\frac{1}{x}) &= x^{n - m}D(\\frac{1}{x}) x^mB(\\frac{1}{x}) + x^{n - m + 1}x^{m - 1}R(\\frac{1}{x}) \\newline A^R(x) &= D^R(x)B^R(x) + x^{n - m + 1}R^R(x)  
\\end{aligned}  
$$  
考虑$D(x)$的最高次数仍然不高于$n-m$,而$x^{n-m+1}R(x)$的最低此项就高于$n-m$了。这个式子在$\\mod x^{n-m+1}$下，$R(x)$就被消去了。并且由于前面所述的性质，$D(x)$并没有高于$n-m$的项，因此，我们要求$D(x)$，即是直接求

$$  
A^R(x)=D^R(x)B^R(x) \\mod x^{n-m+1}  
$$

那么

$$  
D^R(x)=\\frac{A^R(x)}{B^{R}(x)} \\mod x^{n-m+1}  
$$

于是就可以在$O(n \\log n)$内得到$D(x)$了。

$R(x)$即余多项式的求法，只需要将$B(x)$与$D(x)$做一次多项式卷积，然后从$A(x)$中减去就可以得到$R(x)$了。同样的效率也是$O(n \\log n)$。

### 多项式的多点求值与快速插值

考虑一个多项式$A(x)$

其求值，就是对于$x=x\_0$求出对应的$A(x\_0)$的值。那么对于一个多项式的点值，可以表示为$(x\_0,f(x\_0))$。

而其多点求值，就是对于$n$个点$x\_0,x\_1,…,x\_n$，求出$A(x\_0),A(x\_1),..,A(x\_n)$。

而其插值，就是利用几个点值，去找到一个多项式，使得这些点都在多项式。

可以知道的是，对于给出的$n+1$个点$(x\_0, y\_0), (x\_1, y\_1), \\cdots, (x\_n, y\_n)$，可以唯一的确定出一个$n$次多项式$A(x),deg(A(x)=n)$。

可以很容易发现，多点求值和插值互为逆运算。

### 多项式的多点求值

考虑暴力进行多点求值，这个效率显然是$O(n^2)$的。

一个很好的方法是求出$B\_i(x)=x-x\_i,C\_i(x)=A(x) \\mod B\_i(x)$。那么此时，显然有$B\_i(x\_i)=0$，可以推得：$A(x\_i)=C\_i(x\_i)$。这里可以用多项式求模来求处$C\_i(x)$进而计算$A(x_i)$。但这对于效率并没有什么优化。

FFT利用$n$次单位根的性质来优化插值，使得插值具备折半与消去的性质。但这里我们没办法利用这个。但是仍然我们可以用分治来减少问题规模。

考虑当前要求$A(x)$以及$n$个点$x\_0,x\_1,…,x_{n-1}$。将所要求的值分成两半：  
$$  
\\begin{aligned} \\mathbb{X}^{\[0\]} &= {x\_0, x\_1, \\cdots, x_{\\lfloor \\frac{n}{2} \\rfloor}} \ \\mathbb{X}^{\[1\]} &= {x_{\\lfloor \\frac{n}{2} \\rfloor+1},x_{\\lfloor \\frac{n}{2} \\rfloor+2}, \\cdots, x_{n-1}} \\end{aligned}  
$$  
在这里我们将要求的值分成两半。考虑通知将系数分成两半。

假设我们已经利用$\\mathbb{X}^{\[0\]},\\mathbb{X}^{\[1\]}$插值得到了两个多项式$A^{\[0\]}(x),A^{\[1\]}(x)$。

考虑直接做构造  
$$  
\\begin{aligned} P^{\[0\]}(x) &= \\prod_{i=0}^{\\lfloor \\frac{n}{2} \\rfloor} (x-x\_i) \\newline P^{\[1\]}(x) &= \\prod\_{i=\\lfloor \\frac{n}{2} \\rfloor+1}^{n-1} (x-x_i) \\end{aligned}  
$$  
显然，$P^{\[0\]}(x)$与$P^{\[1\]}(x)$分别在$x\\in \\mathbb{X}^{\[0\]},x\\in \\mathbb{X}^{\[1\]}$的时候为$0$。并且这个多项式整理后的次数也是$\\lfloor \\frac{n}{2}\\rfloor$.

那么可以构造  
$$  
\\begin{aligned}  
A(x) &=D_0(x)P^{\[0\]}(x)+A^{\[0\]}(x)\\newline  
A(x) &=D_1(x)P^{\[1\]}(x)+A^{\[1\]}(x)  
\\end{aligned}  
$$  
也即  
$$  
\\begin{aligned}  
A^{\[0\]}(x)\\equiv A(x) \\mod P^{\[0\]}(x)\\newline  
A^{\[1\]}(x)\\equiv A(x) \\mod P^{\[1\]}(x)  
\\end{aligned}  
$$  
那么我们分治处理。每次分治到两边求出$\\lfloor \\frac{n}{2}\\rfloor$次数界下的$A^{\[0\]}(x),A^{\[1\]}(x)$，然后就可以用多项式求模，求出$deg(n)$下的$A(x)$。

那么 此时就可以得到多点的值了。时间复杂度显然是$O(n \\log^2 n)$的。

### 多项式的快速插值

有直接分治解决快速插值问题的方法，其效率为$O(n \\log^2 n)$。下面讲述关于用$FFT$优化拉格朗日插值的方法。

考虑拉格朗日插值法求多项式的插值：  
$$  
A(x)=\\sum_{i=1}^{n}y\_i\\prod\_{j=1,j\\neq i}^{n}\\frac{x-x\_j}{x\_i-x_j}  
$$

不妨设  
$$  
B(x)=\\prod_{i=1}^{n}(x-x\_i)，C\_i(x)=y\_i\\prod\_{j=1,i \\neq j}^{n} \\frac{1}{x\_i-x\_j}  
$$

$B(x)$是一个所谓的对称轮换多项式。那么重点考虑$ C_i(x)$怎么求。

可以看出，$C\_i(x)$实际上就是$y\_i\\frac{B(x)}{x-x\_i}$。其取$x=x\_i$时，分子分母都为0。应用洛必达法则可知，这个时候其即等于$B'(x)$。那么我们对于$x=x\_1,x\_2,…,x\_n$在$B'(x)$做多点求值即可求出每个$\\prod\_{j=1,i \\neq j}^{n}x\_i-x\_j$。进而$C_i(x)$就可求了。

那么要求  
$$  
A(x)=B(x)\\sum_{i=1}^{n}\\frac{C\_i(x)}{x-x\_i}  
$$  
考虑分治。对于当前的分治区间$\[l:r\]$,我们需要求出当前区间的$A(x),B(x)$。假设左右区间的答案分别为$A^{\[0\]}(x),A^{\[1\]}(x)$,其对称轮换式分别为$B^{\[0\]}(x),B^{\[1\]}(x)$。那么有  
$$  
\\begin{aligned}  
A(x)&=B^{\[0\]}(x)B^{\[1\]}(x)\\left(\\sum_{i=l}^{mid}\\frac{C\_i(x)}{x-x\_i}+\\sum_{i=mid+1}^{r}\\frac{C\_i(x)}{x-x\_i}\\right) \\newline  
&=B^{\[0\]}(x)\\sum_{i=l}^{mid}\\frac{C\_i(x)}{x-x\_i}B^{\[1\]}(x)+B^{\[1\]}(x)\\sum_{i=mid+1}^{r}\\frac{C\_i(x)}{x-x\_i}B^{\[0\]}(x)\\newline  
&=A^{\[0\]}(x)B^{\[1\]}(x)+A^{\[1\]}(x)B^{\[0\]}(x)\\newline \\newline  
B(x)&=B^{\[0\]}(x)B^{\[1\]}(x)  
\\end{aligned}  
$$  
这个东西显然可以用分治FFT实现。