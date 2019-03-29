---
title: " 数论函数，杜教筛，洲阁筛，Min_25筛\t\t"
tags:
  - 数论
url: 5370.html
id: 5370
categories:
  - Algorithm
date: 2018-12-06 12:54:37
---

### 数论函数与积性函数

1.  定义域为正整数域，函数陪域为复数域，即 $ f:\\mathbb{Z}^+\\to\\mathbb{C} $ 的函数称为**数论函数**。
2.  对于数论函数 $ f(x) $ ，满足对于 $ \\forall a,b,(a,b)=1 $ ，有 $ f(ab)=f(a)f(b) $ ，那么 $ f(x) $ 为**积性函数**。
3.  对于数论函数 $ f(x) $ ，满足对于 $ \\forall a,b $ ，有 $ f(ab)=f(a)f(b) $ ，那么 $ f(x) $ 为**完全积性函数**。
4.  对于一个正整数 $ n,\\forall i \\in\[1,n\] $ ， $ \\left\\lfloor\\frac ni \\right\\rfloor $ 的取值只有 $ O(\\sqrt{n}) $ 种。

考虑一下基本的积性函数：

1.  除数函数： $ \\sigma\_k(n)=\\sum\_{d|n}{d^k} $ ，表示 $ n $ 的约数的 $ k $ 次幂和，注意 $ \\sigma_k(n)与\\sigma^k(n) $ 是不同的。一般情况下，在没有标明下标情况下 $ k=1 $ 。
2.  约数个数函数： $ \\tau(n)=\\sigma\_0(n)=\\sum\_{d|n}{1} $ ，表示 $ n $ 的约数个数，一般也写为 $ \\mathrm{d}(n) $ 。
3.  欧拉函数： $ \\varphi(n)=\\sum_{i=1}^{n}{\[(n,i)=1\]} $ ，表示不大于 $ n $ 且与 $ n $ 互质的正整数个数，另外 $ \\sum_{i=1}^{n}{\[(n,i)=1\]i}=\\frac{n\\varphi(n)+\[n=1\]}{2} $ ，且对于正整数 $ n>2 $ 来说 $ \\varphi(n) $ 是偶数。
4.  莫比乌斯函数： $ \\mu(n) $ ，在狄利克雷卷积的乘法中与恒等函数互为逆元， $ \\mu(1)=1 $ ，对于无平方因子数 $ n=\\prod_{i=1}^{t}p_i $ 有 $ \\mu(n)=(-1)^t $ ，对于有平方因子数 $ n $ 有 $ \\mu(n)=0 $ 。
5.  元函数： $ e(n)=\[n=1\] $ ，狄利克雷卷积的乘法单位元，完全积性。
6.  恒等函数： $ I(n)=1 $ ，完全积性。
7.  单位函数： $ \\epsilon (n)=n $ ，完全积性。
8.  幂函数： $ Id^k(n)=n^k $ ，完全积性。

### Dirichlet卷积

### Mobius反演

如果存在两个数论函数 $ f,g $ 满足 $ f(n)=\\sum_{d|n}g(d) $ ，那么  
$$  
g(x)=\\sum_{d|n}\\mu(d)f\\left(\\frac nd\\right)  
$$  
即有：  
$$  
f=g\*1 \\Leftrightarrow g=\\mu \* f  
$$  
由上可以引出如下引理：

1.  $ \[n=1\]=\\sum_{d|n}{\\mu(d)} $ ，将 $ \\mu(d) $ 看作是容斥的系数即可证明。
2.  $ n=\\sum_{d|n}{\\varphi(d)} $ ，将 $ \\frac{i}{n}(1\\le i\\le n) $ 化为最简分数统计个数即可证明。
3.  设正整数 $ x,y,a,b $ , $ a,b \\le x,y=\\left\\lfloor\\frac xa\\right\\rfloor $ ，那么有 $ \\left\\lfloor\\frac yb\\right\\rfloor=\\left\\lfloor\\frac {x}{ab}\\right\\rfloor $
4.  $ f,g $ 为两个数论函数， $ t $ 为一个完全积性函数，且 $ t(1)=1 $ ，那么有 $ $

$$  
f(n)=\\sum_{k=1}^{n}t(k)g\\left(\\left\\lfloor\\frac nk\\right\\rfloor\\right) \\Leftrightarrow g(n)=\\sum_{k=1}^{n}\\mu(k)t(k)f\\left(\\left\\lfloor\\frac nk\\right\\rfloor\\right)  
$$

具体Mobius反演的其他内容在此不过多赘述。

### 杜教筛

通俗的名字是“利用Dirichlet卷积构造“。最初由`xudyh`引入国内。

对于数论函数 $ f(n) $ ，要求 $ S(n)=\\sum_{i=1}^{n}f(i) $ 。

我们考虑构造一个积性函数 $ g(n) $ ，显然对于积性函数：  
$$  
\\begin{aligned}  
\\sum_{i=1}^{n}(gf)(i)&=\\sum_{i=1}^{n}\\sum_{d|i}g(d)f\\left(\\frac{i}{d}\\right)\\\&=\\sum_{d=1}^{n}g(d)\\sum_{i=1}^{\\left\\lfloor\\frac{n}{d}\\right\\rfloor}f(i)\\\&=\\sum_{d=1}^{n}g(d)S\\left(\\left\\lfloor\\frac nd \\right\\rfloor\\right)\\end{aligned}$$

然后可以发现，有

$$\\begin{aligned}g(1)S(n)&=\\sum_{i=1}^{n}g(i)S\\left(\\left\\lfloor\\frac ni \\right\\rfloor\\right)-\\sum_{i=2}^{n}g(i)S\\left(\\left\\lfloor\\frac ni \\right\\rfloor\\right) \\\&=\\sum_{i=1}^{n}(gf)(i)-\\sum_{i=2}^{n}g(i)S\\left(\\left\\lfloor\\frac ni \\right\\rfloor\\right)  
\\end{aligned}  
$$  
那么考虑当前要求的前缀和函数，我们选取一个 $ g(n) $ 来辅助计算，**使得前面那个可以快速得出**。然后对于后面的部分只需要数论分块，然后递归做更小部分的就好了。实现**记忆化**才能实现正确的复杂度。

当要求出Mobius函数的前缀和时，可以用 $ (I*\\mu)=e $ 来求。

对于 $ \\varphi $ 的前缀和，有 $ \\sum_{d|i}\\varphi(d)=i=\\epsilon(i) $ ，那么有 $ S(n)=(\\varphi * \\epsilon)(i)-\\sum_{i=2}^{n}iS\\left(\\left\\lfloor\\frac ni \\right\\rfloor\\right) $ 。

考虑以下常见的 $f(n)$，有如下对应的积性函数 $g(n)$：

1.  $f(i)=\\mu(i),g(i)=I(i),(f*g)(i)=1$。
2.  $f(i)=\\varphi(i),g(i)=I(i),(f*g)(i)=\\frac{n(n+1)}{2}$
3.  $f(i)=i\\varphi(i),g(i)=Id(i),(f*g)(i)=\\sum i^2$

对于一般的杜教筛，可以证明其渐进上界时间复杂度为 $ \\Theta(n^{\\frac 23}) $ 。

### 洲阁筛

洲阁筛的应用范围在于，对于一个无法找出合适的 $ g(n) $ 去做构造的时候，有更为普适的低于线性时间复杂度的求法。

洲阁筛的前置要求是： **$ F(p) $是一个低阶多项式，也就是说，$ F(p^c) $可以快速算出**。

以下，我们设质数集为 $ \\mathbb{P},p \\in \\mathbb{P} $ 。

对于 $ n $ 的质因子分解：  
$$  
n=\\prod_{i=1}^{k}p\_i^{c\_i}  
$$  
考虑积性函数 $ f(n) $ :

1.  $ n \\in \\mathbb{P} $ ，有 $ n=p,F(p)=G(p) $ 。
2.  $ n \\in \\mathbb{P}^{k} $ ，有 $ n=p^k,k >1 $ ， $ f(p^c)=T(p^c) $ 。
3.  $ n \\not \\in \\mathbb{P}^{c} $ ， $ f(n)=\\prod_{i=1}^{k}f(p\_i^{c\_i}) $ 。

例如：

*   对于 $ \\varphi(n) $ , $ G(p)=p-1,T(p^c)=(p-1)p^{c-1} $ 。
*   对于 $ \\mu(n) $ , $ G(p)=-1,T(p^c)=0 $ 。

仍然考虑求 $ S(n)=\\sum_{i=1}^{n}F(i) $ 。考虑对于 $ n $ ：  
$$  
S(n)=\\sum_{x \\in\[1,\\sqrt{n}\]}F(x)\\sum_{p \\in\[\\sqrt{n},\\lfloor\\frac{n}{x}\\rfloor\],p \\in \\mathbb{P}}F(p)+\\sum_{i\\in \[1,n\],\\mathbb{P}\\cap \\sqrt{N}' \\not \\in p_x^i}F(x)  
$$  
其中， $ \\mathbb{P}\\cap \\sqrt{N}' \\not \\in p_x^i $ 表示 $ x $ 中没有大于 $ \\sqrt{n} $ 的质因子。

考虑将这个式子拆开计算：

1.  $ \\sum_{x \\in \[1,\\sqrt{n}\]}F(x) $ 可以在 $ O(\\sqrt{n}) $ 内暴力线性筛求出。
2.  考虑对于所有可以取到的 $ \\left\\lfloor\\frac ni \\right\\rfloor $ ，求 $ \\sum_{p \\in\[\\sqrt{n},\\lfloor\\frac{n}{x}\\rfloor\],p \\in \\mathbb{P}}F(p) $
3.  求 $ \\sum_{i\\in \[1,n\],\\mathbb{P}\\cap \\sqrt{N}' \\not \\in p_x^i}F(x) $

#### 考虑求 $ F(p) $

我们筛掉 $ \\sqrt{n} $ 内的所有质数的贡献，剩下的就是我们要考虑的。

注意到前置要求： $ f(p) $ 是一个低阶的多项式。于是我们可以对于每一项都求出 $ \\sum p^k $ 然后就可以求回多项式对应的和了。

我们设在 $ \[1,\\sqrt{n}\] $ 中的质数有 $ m $ 个，依次升序为 $ p\_1,\\dots,p\_m $ 。

考虑 $ g\_k(i,j) $ 为 $ \[i,j\] $ 中，与前 $ i $ 个质数互质的数的 $ k $ 次幂和。我们要求的就是 $ g\_k(m,j) $ 。

对于 $ i=0 $ ,那么就是所有的数均被计入答案，这就是一个自然数幂和。

而对于 $ i > 0 $ ，显然有  
$$  
g\_k(i,j)=g\_k(i-1,j)-p\_i^kg\_k(i-1,\\left\\lfloor \\frac {j}{p_i}\\right\\rfloor)  
$$  
其中 $ i $ 的取值有 $ O(\\frac{\\sqrt{n}}{\\ln {n}}) $ 种， $ j $ 的取值有 $ O(\\sqrt{n}) $ 种。总效率是 $ O(\\frac{n}{\\ln n}) $ 。

考虑优化。

注意到，当 $ p_{i+1}>j $ 时， $ g_k(i,j)=1 $ 。因为这个时候，除了 $ 1 $ 以外，其他所有数都被筛掉了。

然后就有，当 $ p\_i > \\lfloor \\frac{j}{p\_i} \\rfloor $ ，也就是 $ p\_i^2 > j $ 的时候， $ g\_k(i,j) $ 的转移就变成了：  
$$  
g\_k(i,j)=g\_k(i-1,j)-p_i^k  
$$  
那么当 $ p\_i^2 > j $ 的时候，转移是可以被省去的。而在后面假设需要从这里转移的时候，我们记下最早有被转移的 $ i $ 的位置，那么后面只需要加上一段 $ p\_i $ 的前缀和就好了。

考虑设 $ pre\[j\] $ 为最小的 $ i $ 满足 $ p^2_{i}>j $ 。那么有：  
$$  
g\_k(i,j)=\\begin{cases}g\_k(i-1,j)-p\_i^kg\_k(i-1,\\left\\lfloor \\frac {j} {p_i}\\right\\rfloor) & i <pre\[j\]\\newline  
break &i \\geq pre\[j\]  
\\end{cases}  
$$  
那么当一个未dp的 $ g\_k(i,j) $ ，有 $ g\_k(i,j)=g_k(pre\[j\],j)+sump\[\\min(i,cntp\[j\])\]-sump\[pre\[j\]-1\] $

其中， $ sump $ 为素数前缀和， $ cntp $ 为小于某数的素数个数。

考虑对于每一组数 $ \\lfloor\\frac{n}{x}\\rfloor $ 都只需要转移根号的质数，因此逼近得到的时间复杂度为 $ O(\\frac{n^{\\frac 34}}{\\ln n}) $ 。

对于 $ cntp $ ，我们只需要处理出 $ j \\leq \\sqrt{n} $ 的就够了。而关于 $ g $ 数组，首先可以滚掉第一维，然后考虑将 $ j $ part in to：对于大于 $ \\sqrt{n} $ 的，可以将其存放在另外一个数组的 $ \\frac{n}{x} $ 位置。

#### 考虑求 $ F(x) $

考虑 $f(i,j)$ 为 $\[1,j\]$ 中，只包含前 $i$ 个质因子的 $F(x)$ 的和。转移就直接枚举幂指数 $c$ ，有  
$$  
f(i,j)=f(i-1,j)+\\sum_{c}F(p\_i^{c})f(i-1,\\left\\lfloor\\frac{j}{p\_i^c}\\right\\rfloor)  
$$  
暴力计算，考虑其 $ic$ 枚举最高为 $\\sqrt{n}$ 次，其总复杂度为 $O(\\frac{n}{\\ln n})$ 。

仍然考虑优化。注意到，在求 $F(p)$ 的时候我们用到了一个$ p^2\_i < j $的优化。但是在这一题里我们不方便做此优化。我们可以调整转移顺序，对于状态定义，将前$i$个质数改换为“小于 $\\sqrt{n}$ 的后$p\_i \\dots p\_m$质数”。或者将原来的正序排列质数改为降序排列质数。这样我们枚举的时候就是从大到小做转移。那么当$p\_i > j$时一定会有 $f(i,j)=1$ 。

那么也就是说，当 $p_i^2 > j$ 的时候，存在转移  
$$  
f(i,j)=f(i-1,j)+F(p_i)  
$$  
对于转移边界，肯定有 $f(0,j)=1$ 。

那么转移分为三个部分：

1.  $\[cntp\[j\]+1,m\]$，不用计算。
2.  $\[pre\[j\],cntp\[j\]\]$，我们算出$F(p_i)$的前缀和就好了。
3.  $\[0,pre\[j\]\]$，直接按照前式dp。这一部分是没法优化的。

而其中，在第二步的dp可以这样算出来：假设 $sumf$ 为 $F(p_i)$ 前缀和。于是有：

$ f(i,j)=f(pre\[j\],j)-sumf\[\\min(i,cntp\[j\])-1\]-sump\[pre\[j\]-1\] $

这个转移与上面求 $F(p)$ 的转移十分类似。

我们考虑分析这个的转移复杂度。积分可知复杂度近似为$O(\\frac{n^{\\frac 34}}{\\ln n})$。

同样的，类似于前述，我们对于 $f$ 的储存也可以用根号映射的方法。

#### 合并

我们回到前面的式子：  
$$  
S(n)=\\sum_{x \\in\[1,\\sqrt{n}\]}F(x)\\sum_{p \\in\[\\sqrt{n},\\lfloor\\frac{n}{x}\\rfloor\],p \\in \\mathbb{P}}F(p)+\\sum_{i\\in \[1,n\],\\mathbb{P}\\cap \\sqrt{N}' \\not \\in p_x^i}F(x)  
$$  
那么此刻，三个部分都是被依次独立求出的。我们只需要关于$\\left\\lfloor\\frac{n}{x}\\right\\rfloor$分块后带入dp值求解，加上最后算的部分即可。

注意到整个算法的瓶颈复杂度为 $O(\\frac{n^{\\frac 34}}{\\ln n})$ 。而空间我们全程利用的也只有$O(\\sqrt{n})的空间；因此这个算法可以在比线性时间优的复杂度内求解满足以下条件的数论函数前缀和：

*   $F(n)$为积性函数，并且是一个在$\\mathbb{P}$下关于$p$的低阶多项式。
*   $G(p)$可以分解为若干**完全**积性函数之和。并且这些函数的和要可以快速求出。
*   $G(p)$ 与 $T(p^c)$（定义见前述）可以快速计算。

代码还有很多 超级多的实现细节。还是没有研读明白代码。

### min_25筛

min_25筛在国内的引进出处是whzzt 一类特殊的数论函数求和问题。这个筛法也是一种特殊的Euler筛，渐进时间复杂度与洲阁筛大致相同，但是常数因子更小，并且更好实现。（但是更难理解…）。

在这里，我们沿用在 洲阁筛 中的部分定义：设质数集为 $ \\mathbb{P},p \\in \\mathbb{P},\\hat p_{\\to x} \\in \\mathbb{P}$ ,即 $p$ 代表 一个质数，$\\hat p \\to x $ 表示 $x$ 的最小质因子。而在上面，$p_{\\to x}$则表示 $p$ 的某一质因子。

接下来，考虑$S(n)=\\sum_{i=1}^n F(i)$。

那么考虑Euler筛法的过程，我们可以得到：  
$$  
S(n)=1+\\sum_{p \\in\[2,n\],p \\in \\mathbb{P}}\\sum_{x \\in\[2,n\],\\hat p_{\\to x}=p}F(x)=1+\\sum_{p^e \\in \[2,n\],e \\in \\mathbb{N^*}} F(p^e) \\left(1+\\sum_{\\substack{x \\in\[2, \\lfloor \\frac{n}{p^e}\\rfloor\]\\newline \\forall p_{\\to x} > p}} F(x)\\right)  
$$  
在这里就是我们就是枚举了 $p^e$ 作为了某些数的最小质因子，然后考虑用这个质因子来筛出后面的积性函数。这个东西也就相当于在Euler筛中的“只枚举作为最小质因子的数”。

注意到在朴素的Euler筛中，这个东西想要筛出来，效率是$O(n)$的，这也等价于积性函数求和的效率。我们考虑从这一步出发来优化积性函数求和。

考虑继续化简式子：  
$$\\begin{aligned} S(n)&=1+\\sum_{p \\in\[2,n\],p \\in \\mathbb{P}}\\sum_{x \\in\[2,n\],\\hat p_{\\to x}=p}F(x) \\newline &=1+\\sum_{p^e \\in \[2,n\],e \\in \\mathbb{N^*}} F(p^e) \\left(1+\\sum_{\\substack{x \\in\[2, \\lfloor \\frac{n}{p^e}\\rfloor\] \\newline \\forall p_{\\to x} > p}} F(x)\\right)\\newline &=1+\\sum_{\\substack{p \\in\[2,\\sqrt{n}\] \\newline p^e \\in \[2,n\],e \\in \\mathbb{N^*}}}F(p^e) \\left(1+\\sum_{\\substack{x \\in\[2, \\lfloor \\frac{n}{p^e}\\rfloor\] \\newline \\forall p_{\\to x} > p}} F(x)\\right)+ \\sum_{p \\in\[\\sqrt{n},n\],p \\in \\mathbb{P}}F(p)\\newline \\end{aligned} $$  
那么考虑这个东西要如何快速去求。

不妨设  
$$  
g(n,m)=\\sum_{x \\in\[2,n\],\\forall p_{\\to x} > m} F(x)  
$$  
$$  
h(n)=\\sum_{p \\in\[2,n\],p \\in \\mathbb{P}} F(p)  
$$

首先考虑 $g(n,m)$怎么计算。注意到这个的定义改换十分类似于在上面的定义改换。

那么接下来的就有  
$$  
\\begin{aligned}g(n,m)&=\\sum_{x \\in\[2,n\],\\forall p_{\\to x} > m} F(x) \\newline &=\\sum_{\\substack{p\\in\[m,\\sqrt{n}\] ,p^e \\leq n \\newline p \\in \\mathbb{P},e \\ge 1}}F(p^e)\\left( \[e \\neq 1\]+\\sum_{\\substack{x \\in \[p+1,\\lfloor\\frac{n}{p^e}\\rfloor\]\\newline \\forall p_{\\to x} > p}}f(x)\\right)+\\sum_{p \\in \[m+1,n\],p \\in \\mathbb{P}}f(p) \\newline &=\\sum_{\\substack{p\\in\[m,\\sqrt{n}\] ,p^e \\leq n \\newline p \\in \\mathbb{P},e \\ge 1}}F(p^e)\\left( \[e \\neq 1\]+g(\\lfloor\\frac{n}{p^e}\\rfloor,p)\\right)+\\sum_{p \\in \[m+1,n\],p \\in \\mathbb{P}}f(p) \\newline &=\\sum_{\\substack{p\\in\[m,\\sqrt{n}\] ,p^e \\leq n \\newline p \\in \\mathbb{P},e \\ge 1}}F(p^e)\\left( \[e \\neq 1\]+g(\\lfloor\\frac{n}{p^e}\\rfloor,p)\\right)+h(n)-h(m)  
\\end{aligned}  
$$  
注意，此处有一个关于与zzt论文不同的地方：当 $e=1$的时候前面的常转移系数需要特殊判断。

而对于我们要求解的答案就是$S(n)=g(n,0)+1$。

那么现在我们有两种做法：直接按照该式子，记忆化维护dp，或者从大到小枚举 $m$ 来计算所有的 $g$ 。而后者对应了洲阁筛论文中的第二种做法。对于这种做法，仅当 $n > m^2$ 的时候$g(n,m) \\neq 0$。于是后面的部分就可以用前缀和优化了。

现在考虑，我们的答案瓶颈就是计算 $h(i)$，即质数函数值前缀和。我们用dp优化埃筛来做这个东西。

对于埃筛，每次是枚举一个质数，然后筛去所有 $\\geq p^2$ 的 $p$ 的倍数。我们假设将 $F(p)$ 看做是一个多项式，那么多项式系数固定，只要求出所需质数的幂和就可以算出 $F(p)$ 的前缀和。令 $H_k(i,j)$ 表示枚举前 $i$ 个质数后，所有剩下的不超过 $j$ 的数的 $k$ 次方之和。可以发现，这一部分的转移就是在上面洲阁筛中第一部分：$f(p)$ 的计算。

于是，我们可以用另外一个角度来理解洲阁筛：**DP模拟 优化埃拉托斯特尼筛法**。

关于这个东西时间复杂度的证明，可以参照《朱震霆 一类特殊的数论函数求和问题》 里的 [时间复杂度证明](http://www.dtenomde.com/wp-content/uploads/2018/12/120519230434_2.pdf)部分。