---
title: " LOJ563「LibreOJ Round #10」Snakes 的 Naïve  Graph\t\t"
tags:
  - 奇技淫巧
  - 数学
url: 6406.html
id: 6406
categories:
  - Solution
date: 2019-02-08 11:10:47
---

好像很好吃的样子。考虑答案其实就是要求 $\\mod m$下，$\[0,m)$中乘法逆元非自身的数的个数。

然后打一个表：诶真的这么好吃。

证明？半个小时过去了还是不会。于是成为了一个打表AC选手（被出题人安排的明明白白）。

下面是出题人的证明。可以发现的是，老子只能发现并证明至**引理四**。出题人就是个大毒瘤。

* * *

**引理一** 对于 $G(m)$ 中的任意一点，其度数小于等于 $2$。

*   **证明** 对于小于 $m$ 且与 $m$ 的正整数 $i$，其模 $m​$ 意义下乘法逆元唯一。

**引理二** 若模 $m$ 意义下乘法逆元非自身的数的个数为 $g(m)$，则 $f\[G(m)\]=2^{g(m)/2}$。

*   **证明** $G(m)$ 可以被划分为若干不联通子图，对于模 $m$ 意义下乘法逆元非自身的数 $i$，$i\_X, i^{-1}\_X, i\_Y, i^{-1}\_Y$ 之间两两有边，则选择 $i\_X\\rightarrow i\_Y, i^{-1}\_X\\rightarrow i^{-1}\_Y$ 或 $i\_X\\rightarrow i^{-1}\_Y, i^{-1}\_X\\rightarrow i\_Y$ 中任意一组匹配均不改变其最大匹配数。对于乘法逆元为自身或不存在乘法逆元的数 $j$，$j\_X$ 仅与 $j\_Y$ 连边，因此在最大匹配中 $j\_X$ 只能与 $j\_Y$ 匹配。根据乘法原理可得 $f\[G(m)\]=2^{g(m)/2}$。

**引理三** 若在 $G(m)$ 中，对于 $1\\leq i,j\\leq m-1$ 的正整数 $i,j$，若 $i\_X$ 向 $j\_Y$ 有边，则 $(m-i)\_X$ 向 $(m-j)\_Y$ 有边。

*   **证明** 对于 $i=j$ 情况显然，对于 $i\\neq j$ 有 $(m-i)(m-j)=m^2-mi-mj+ij$，在模 $m$ 意义下前三项被消去，由于 $ij \\equiv 1 \\pmod m$，因此 $(m-i)(m-j) \\equiv 1 \\pmod m$。

定义 $h(x)$ 表示在模 $m$ 意义下满足 $i^2 \\equiv 1 \\pmod m$ 且 $1\\leq i\\leq m-1$ 的正整数 $i$ 的个数。

**引理四** $g(m)=\\varphi(m)-h(m)$ 显然成立，则答案可表示为 $2^{\\varphi(m)-h(m)\\over 2}$。

**引理五** 令 $\\omega(m)$ 表示 $m$ 的不同质因子个数，$\[P\]$ 表示命题 $P$ 是否成立，若成立则 $\[P\]=1$，否则 $\[P\]=0$。则有 $h(m)=2^{\\omega(m)-\[2|n\]+\[4|n\]+\[8|n\]}$，也即答案为：  
$$  
\\Huge{f\[G(m)\]=2^{\\varphi(m)-2^{\\omega(m)-\[2|n\]+\[4|n\]+\[8|n\]} \\over 2}}  
$$

**证明** 若 $m$ 分解质因数后，$m=\\prod_{i=1}^k p\_i^{\\alpha\_i}$，令 $y=x^2$，$y\_i=x\_i^2$，可将 $x^2 \\equiv 1 \\pmod m​$ 转化为如下形式的同余方程组：

$$y \\equiv 1\\quad (\\text{mod} \\;\\; m) \\Leftrightarrow \\begin{cases} y \\equiv 1\\quad (\\text{mod} \\;\\; {p\_1^{\\alpha\_1}}) \\\ y \\equiv 1\\quad (\\text{mod} \\;\\; {p\_2^{\\alpha\_2}}) \\\ \\quad\\quad \\vdots \\\ y \\equiv 1\\quad (\\text{mod} \\;\\; {p\_k^{\\alpha\_k}}) \\end{cases}$$

右侧同余方程组中 $p\_i^{\\alpha\_i}$ 的最小公倍数为 $m$，因此右侧同余方程组显然可以推得左侧同余式。考虑使用中国剩余定理，下式可转化至上式情况，且由于 $y\_i=x\_i^2$，我们可以通过对每条同余方程计算合法 $x_i$ 的个数以计算 $h(m)$：

$$ \\begin{cases} y\_1 \\equiv 1\\quad (\\text{mod} \\;\\; {p\_1^{\\alpha\_1}}) \\\ y\_2 \\equiv 1\\quad (\\text{mod} \\;\\; {p\_2^{\\alpha\_2}}) \\\ \\quad\\quad \\vdots \\\ y\_k \\equiv 1\\quad (\\text{mod} \\;\\; {p\_k^{\\alpha_k}}) \\end{cases}$$

由于 $p\_i^{\\alpha\_i}$ 两两互质，因此该同余方程组必定有解且在 $\[0,m-1\]$ 范围内仅有一解。

显然地，我们有：

$$ x\_i^2 \\equiv 1\\pmod m \\Rightarrow x\_i^2-1 \\equiv 1\\pmod m \\Rightarrow (x\_i+1)(x\_i-1) \\equiv 0\\pmod m$$

因此该同余方程组又可化为：

$$ \\begin{cases} y\_1 \\equiv 1\\quad (\\text{mod} \\;\\; {p\_1^{\\alpha\_1}}) \\\ y\_2 \\equiv 1\\quad (\\text{mod} \\;\\; {p\_2^{\\alpha\_2}}) \\\ \\quad\\quad \\vdots\\\ y\_k \\equiv 1\\quad (\\text{mod} \\;\\; {p\_k^{\\alpha\_k}}) \\end{cases} \\Leftrightarrow \\begin{cases} (x\_1+1)(x\_1-1) \\equiv 0\\quad (\\text{mod} \\;\\; {p\_1^{\\alpha\_1}}) \\\(x\_2+1)(x\_2-1) \\equiv 0\\quad (\\text{mod} \\;\\; {p\_2^{\\alpha\_2}}) \\\ \\quad\\quad \\vdots \\\(x\_k+1)(x\_k-1) \\equiv 0\\quad (\\text{mod} \\;\\; {p\_k^{\\alpha_k}}) \\end{cases}$$

我们只需计算每条同余方程合法解 $x_i$ 的个数，并根据乘法原理将其相乘即为 $h(m)$。

考虑 $p\_i\\geq 3$ 的情况，由于此时 $\\gcd(x\_i+1,x\_i-1)=1$，因此其在模 $p\_i^{\\alpha\_i}$ 的情况下当且仅当 $x\_i+1 \\equiv 0\\pmod {p\_i^{\\alpha\_i}}$ 或 $x\_i-1 \\equiv 0\\pmod {p\_i^{\\alpha\_i}}$ 时满足 $(x\_i+1)(x\_i-1) \\equiv 0\\pmod {p\_i^{\\alpha\_i}}$，该情况下 $x\_i$ 合法解的个数为 $2$。

对于 $p\_i=2$ 的情况，由于此时 $\\gcd(x\_i+1,x_i-1)$ 可能为 $2$，因此需要谨慎地分类讨论：

*   若 $\\alpha\_i=1$，此时 $p\_i^{\\alpha\_i}=2$，当且仅当 $x\_i=1$ 时满足 $(x\_i+1)(x\_i-1) \\equiv 0\\pmod {p\_i^{\\alpha\_i}}$，该情况下 $x_i$ 合法解的个数为 $1$。
*   若 $\\alpha\_i=2$，此时 $p\_i^{\\alpha\_i}=4$，当且仅当 $x\_i\\in{1,3}$ 时满足 $(x\_i+1)(x\_i-1) \\equiv 0\\pmod {p\_i^{\\alpha\_i}}$，该情况下 $x_i$ 合法解的个数为 $2$。
*   若 $\\alpha\_i\\leq 3$，此时 $p\_i^{\\alpha\_i}\\leq 8$，当且仅当 $x\_i\\in{1,p\_i^{\\alpha\_i}-1,{p\_i^{\\alpha\_i}-1\\over 2},{p\_i^{\\alpha\_i}+1\\over 2}}$ 时满足 $(x\_i+1)(x\_i-1) \\equiv 0\\pmod {p\_i^{\\alpha\_i}}$，该情况下 $x_i$ 合法解的个数为 $4$。

我们不妨这样考虑，令 $L(x)$ 表示 $x$ 在分解质因数后 $2$ 的个数，也即 $\\log_2{\\text{lowbit}(x)}$，则 $L(x)$ 的前 $15$ 项为：

$1$

$2$

$3$

$4$

$5$

$6$

$7$

$8$

$9$

$10$

$11$

$12$

$13$

$14$

$15$

$0$

$1$

$0$

$2$

$0$

$1$

$0$

$3$

$0$

$1$

$0$

$2$

$0$

$1$

$0$

注意到在模 $p\_i^{\\alpha\_i}$ 意义下除平凡解 $1,p\_i^{\\alpha\_i}-1$ 外，非平凡解 $x\_i$ 满足 $L(x\_i-1)+L(x\_i+1)\\leq \\alpha\_i$，$L(x)$ 有如下性质：

*   在前 $p\_i^{\\alpha\_i}-1$ 项中最大值为 $\\alpha_i-1$ 且仅出现一次。
*   对于正整数 $x$，必定有 $L(x-1)$ 与 $L(x+1)$ 中其一值为 $1$。

上述性质读者可自行证明。由上述性质我们可推得非平凡解仅出现在 $p\_i^{\\alpha\_i}\\over 2$ 的两侧，在 $2,4$ 的特殊情况下解的个数退化至 $1,2$。

通过整理上述推导，我们即可推得 $h(m)​$ 表达式：

$$\\Huge{f\[G(m)\]=2^{\\varphi(m)-2^{\\omega(m)-\[2|n\]+\[4|n\]+\[8|n\]} \\over 2}}$$

注意到 $311021$ 为质数，因此 $2^x \\equiv 2^{x \\bmod 311020} \\pmod {311021}$，预处理 $2$ 的次幂对 $311021$ 取模结果即可。注意到 $\\omega(m)$ 在 $10^7$ 范围内小于 $20$，因此可共用同一表。

* * *

不要脸的出题人的安排：

> 一位优秀的 OIer 如何在 15 分钟内 AC 此题：

> 1 min：发现求模某个数下 $1​$ 平方根个数
> 
> 4 min：手算前几个发现结论并证明完毕
> 
> 14 min：码完线性筛并样例测试完毕
> 
> 15 min：提交！AC！