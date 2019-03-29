---
title: " 数学知识：导数，积分，泰勒展开\t\t"
url: 4220.html
id: 4220
categories:
  - Algorithm
date: 2018-10-19 15:30:43
tags:
---

### 导数

关于导数的一个主定义是：当函数$f(x)$在$x=x\_0$处有一个增量$\\Delta x$，其函数值的一个增量$\\Delta y$，当$\\Delta x \\to 0$时假设$\\frac{\\Delta y }{\\Delta x}=a$的极限存在，则$a$为函数$f(x)$在$x=x\_0$处取到的极限。现代表示即为$\\frac{dy}{dx}=\\lim_{x \\to 0} \\frac{\\Delta y}{\\Delta x}$。

其几何上的表示即为$f(x)$在$x_0$处切线的斜率。

假设一个函数在一段区间内可导，通过定义，我们可以求出一个函数在某处的导数。而其导数的函数即为导函数。

函数连续不一定可导，可导一定连续，不连续一定不可导。

以下是所有初等函数的导函数：

1.  $$\\begin{matrix}f(x)=c(c为常数),f'(x)=0 \\end{matrix}$$
2.  $$\\begin{matrix}f(x)=x^n & f'(x)=nx^{n-1}\\end{matrix}$$
3.  $$\\begin{matrix}f(x)=a^x & f'(x)=a^x \\ln a & f(x)=e^x & f'(x)=e^x \\end{matrix}$$
4.  $$\\begin{matrix}f(x)=\\log_a x & f'(x)=\\frac{1} {x\\ln a} &  f(x)=\\ln x & f'(x)=\\frac{1}{x} \\end{matrix}$$
5.  $$\\begin{matrix}f(x)=\\sin x & f'(x)=\\cos x \\end{matrix}$$
6.  $$\\begin{matrix}f(x)=\\cos x & f'(x)=-\\sin x \\end{matrix}$$
7.  $$\\begin{matrix}f(x)=\\tan x & f'(x)=\\frac{1}{\\cos^2 x }\\end{matrix}$$
8.  $$\\begin{matrix}f(x)=\\cot x & f'(x)=\\frac{-1}{\\sin^2 x } \\end{matrix}$$
9.  $$\\begin{matrix}f(x)=\\arcsin x  &  f'(x)=\\frac{1}{\\sqrt{1-x^2}}\\end{matrix}$$

对于复合函数，其导函数可以通过复合函数的导函数的运算规则来求出：

1.  $$'(f(x)+g(x))=f'(x)+g'(x)$$
2.  $$'(f(x) \ g(x))=f(x)g'(x)+f'(x)g(x)$$
3.  $$'\\left(\\frac{f(x)}{g(x)}\\right)=\\frac{f'(x)g(x)-f(x)g'(x)}{g^2(x)}$$
4.  $$'(f(g(x)))=g'(x)f'(g(x))$$

### 积分

#### 积分

积分，在数学分析中的概念，可以形象的理解为函数与$x$轴围成的曲边梯形的面积。如果一个函数存在积分，那么就说这个函数是可积的。

可导函数一定连续，连续函数一定可积。可积一定连续，连续不一定可导，可导一定可微，可微一定可导。多元函数可以求偏导。

#### 定积分

定积分是指，在范围$\[a,b\]$内连续的函数$f(x)$上积分和的极限。

上述积分表示为$\\int_{a}^{b}f(x)\\mathrm{dx}$。

一个函数，可以存在不定积分，而不存在定积分，也可以存在定积分，而不存在不定积分。一个连续函数，一定存在定积分和不定积分；若只有有限个间断点，则定积分存在；若有跳跃间断点，则原函数一定不存在，即不定积分一定不存在。

定积分有以下基本运算法则：

1.  当$a=b$，$\\int_{a}^{b}f(x)\\mathrm{dx}=0$。
2.  当$a>b$，那么$\\int_{b}^{a}f(x)\\mathrm{dx}=-\\int_{a}^{b}f(x)\\mathrm{dx}$。
3.  常数可以提前，即$\\int_{a}^{b}kf(x)\\mathrm{dx}=k\\int_{a}^{b}f(x)\\mathrm{dx}$。
4.  定积分满足范式，即$\\int_{a}^{b}\[f(x) \\pm g(x)\]\\mathrm{dx}=\\int_{a}^{b}f(x)dx \\pm \\int_{a}^{b}g(x)\\mathrm{dx}$。
5.  定积分满足区间结合，即$\\int_{a}^{b}f(x)\\mathrm{dx}+\\int_{b}^{c}f(x)\\mathrm{dx}=\\int_{a}^{c}f(x)\\mathrm{dx}$。

**定理1：**设$f(x)$在区间$\[a,b\]$上连续，则$f(x)$在$\[a,b\]$上可积。

**定理2****：**设$f(x)$区间$\[a,b\]$上有界，且只有有限个间断点，则$f(x)$在$\[a,b\]$上可积。

**定理3：**设$f(x)$在区间$\[a,b\]$上单调，则$f(x)$在$\[a,b\]$上可积。

#### 不定积分

定积分是一个数值，而不定积分就是一个公式。

$\\int f(x)\\mathrm{dx}=g(x)+C$，我们把$g(x)+C$叫做一个函数的不定积分，或者一个函数的反导数。其中，$C$为任一常数。

要求一个函数的不定积分，只需要将其当做一个导函数，而反过去去求它的原函数（即反导函数）。这个东西就是原函数的不定积分。即在上面的式子中有$g'(x)=f(x)$。

1、函数的和的不定积分等于各个函数的不定积分的和；即：设函数$f(x)$以及$g(x) 的原函数存在，则：

$$\\int\[f(x) + g(x)\]\\mathrm{dx}=\\int f(x)dx+\\int g(x)\\mathrm{dx}$$

2、求不定积分时，被积函数中的常数因子可以提到积分号外面来。即：设函数$f(x)$ 的原函数存在，$k$ 非零常数，则

$$\\int kf(x)\\mathrm{dx}=k\\int f(x)\\mathrm{dx}$$

### 牛顿-莱布尼茨公式

**牛顿-莱布尼茨公式**如果$f(x)$是$\[a,b\]$上的连续函数，并且有$g′(x)=f(x)$，那么

$$\\int_{a}^{b}f(x)\\mathrm{dx}=g(b)-g(a)$$

用文字表述为：一个定积分式的值，就是原函数在上限的值与原函数在下限的值的差。正因为这个理论，揭示了积分与黎曼积分本质的联系，可见其在微积分学以至更高等的数学上的重要地位，因此，牛顿-莱布尼兹公式也被称作微积分基本定理。

从这个公式可以看出，一个函数的定积分，等于这个函数的不定积分的差，等于这个函数的反导函数的差。

### 泰勒展开

$$\\begin{split} f(x)&=f(x\_0)+f'(x\_0)(x-x\_0)+f''(x\_0)\\int_{x\_0}^x (x-x\_0){\\rm d}x+f'''(x\_0)\\iint\_{x\_0}^x (x-x\_0) {\\rm d}x + \\ldots \\\ &=f(x\_0)+f'(x\_0)(x-x\_0) + f''(x\_0)\\cdot \\frac{1}{2} (x-x\_0)^2 + f'''(x\_0)\\cdot \\frac{1}{2}\\cdot \\frac{1}{3} (x-x\_0)^3 + \\ldots \\\ &=f^{(0)}(x\_0)\\frac{1}{0!}(x-x\_0)^0+f'(x\_0)\\frac{1}{1!}(x-x\_0)^1 + f''(x\_0)\\frac{1}{2!} (x-x\_0)^2 + f'''(x\_0)\\frac{1}{3!}(x-x\_0)^3 + \\ldots \\\ &=\\sum\_{i=0}^{+\\infty} f^{(i)}(x\_0)\\frac{1}{i!}(x-x\_0)^i \\end{split}$$

其中,$f^{(i)}(x)$表示$f(x)$的$i$阶导。

**泰勒展开式就是基于对线性逼近的无限次运用而得到的。**

扩展的一些式子：  
$$\\frac{e^x + e^{-x}}{2} = \\sum\\limits_{i = 0}^{\\infty} \\frac{x^{2i}}{(2i)!}$$  
$$\\frac{e^x - e^{-x}}{2} = \\sum\\limits_{i = 0}^{\\infty} \\frac{x^{2i + 1}}{(2i + 1)!}$$  
还有一些比较有用的公式：  
$$\\frac{1}{1 - x} = \\sum\\limits_{i = 0}^{\\infty} x^i$$

$$\\ln(1 + x) = \\sum\\limits_{i = 0}^{\\infty} (-1)^{i} \\frac{x^{i + 1}}{i + 1}$$

$$(1 + x)^{a} = \\sum\\limits_{i = 0}^{\\infty} a^{i}\\frac{x^i}{i!}$$

$$\\sin(x) = \\sum\\limits_{i = 0}^{\\infty} (-1)^{i}\\frac{x^{2i + 1}}{(2i + 1)!}$$ $$\\cos(x) = \\sum\\limits_{i = 0}^{\\infty} (-1)^{i}\\frac{x^{2i}}{(2i)!}$$