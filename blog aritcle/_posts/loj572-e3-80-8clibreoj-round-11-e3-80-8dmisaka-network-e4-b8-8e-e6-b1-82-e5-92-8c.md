---
title: " LOJ572「LibreOJ Round #11」Misaka Network 与求和\t\t"
tags:
  - 奇技淫巧
  - 数学
url: 6387.html
id: 6387
categories:
  - Solution
date: 2019-02-08 10:38:18
---

首先，考虑将原题的 $f(x)$ 的定义改为 $x$ 次大的质因数的 $k$ 次方。

现在考虑求

$$\\sum_{i=1}^{N}\\sum_{j=1}^{N}f(gcd(i,j))​$$

枚举gcd，那么有  
$$  
\\begin{aligned}  
&\\sum_{i=1}^{N}\\sum_{j=1}^{N}f(gcd(i,j))​\\\  
=&\\sum_{g=1}^{N}f(g)\\sum_{i=1}^{\\lfloor\\frac{N}{g}\\rfloor}\\sum_{j=1}^{\\lfloor\\frac{N}{g}\\rfloor}\[gcd(i,j)=1\]\\\  
=&\\sum_{g=1}^{N}f(g)\\sum_{i=1}^{\\lfloor\\frac{N}{g}\\rfloor}\\sum_{j=1}^{\\lfloor\\frac{N}{g}\\rfloor}\\sum_{d|(i,j)}\\mu(d)\\\  
=&\\sum_{g=1}^{N}f(g)\\sum_{d=1}^{\\lfloor\\frac{N}{g}\\rfloor}\\mu(d)\\left\\lfloor\\frac{N}{gd}\\right\\rfloor^2\\\  
=&\\sum_{T=1}^{N}(f*\\mu)(T)\\left\\lfloor\\frac{N}{T}\\right\\rfloor^2 \\end{aligned} $$

现在的瓶颈在于，如何计算$(f*u)​$的前缀和。

令$g(N)=\\sum_{i=1}^{N}(f*\\mu)(i)$，注意到$(f*\\mu)\*I=f\*(\\mu*I)=f$。因此：

\\begin{aligned}  
\\sum_{i=1}^{N}f(i)&=\\sum_{i=1}^{N}(f*\\mu*1)(i)\\\&=\\sum_{i=1}^{N}g(\\lfloor\\frac{N}{i}\\rfloor)\\\  
g(N)&=\\sum_{i=1}^{N}f(i)-\\sum_{i=2}^{N}g\\left(\\left\\lfloor\\frac{N}{i}\\right\\rfloor\\right)  
\\end{aligned}

这是一个很明显能杜教筛的式子。考虑如何计算$f(i)$的前缀和。

回过头来思考计算$f(x)$的过程：我们从小到大枚举一个数的每一个质因子，最后第二个被枚举到的质因子的 $k$ 次方即为 $f(x)$。

这个东西，我们可以用类似dp优化埃氏筛法的方法处理：我们令$s(n,i)$表示上次选择的质因子为$p_{i-1}$，剩余部分的乘积不超过$n$的数的$f(x)$ 之和。下面$\\mathbb{P}$为质数集， $p \\in \\mathbb{P}$，有：  
$$  
s(n,i)=\\begin{cases}0 & & {p\_i>n}\\\p\_{i-1}^k*(\\sum_{j=1}^{n}\[j \\in \\mathbb{P}\]-(i-1))+\\sum_{j=i}^{p\_j^2≤n}\\sum\_{e=1}^{p\_j^{e+1}≤n}(s(\\lfloor\\frac{n}{p\_j^e}\\rfloor,j+1)+p\_j^k) & & {p\_i≤n}\\end{cases}  
$$

$\\sum_{i=1}^{N}f(i)=s(N,1)$。

其中，$n$以内质数个数可以用洲阁筛或者$Min25$筛快速计算直接计算，因为我们只需要计算在$\\left\\lfloor\\frac{N}{i}\\right\\rfloor$的值。

时间复杂度$O(N^{1-\\epsilon})$。具体复杂度分析见2018集训队论文 《**朱震霆 一类特殊的数论函数求和问题**》 里的 [时间复杂度证明](http://www.dtenomde.com/wp-content/uploads/2018/12/120519230434_2.pdf)部分。

    #include<bits/stdc++.h>
    #define N 1000005
    #define uint unsigned int
    #define ll long long
    int n, m, K, sqr, pri[N], vis[N], pcnt, w[N];
    uint prk[N], h[N], f[N], g[N], ans;
    uint Pow (uint x, int k) { uint t = 1; for (; k; k >>= 1, x = x * x) if (k & 1) t = t * x; return t; }
    void init ()
    {
        for (int i = 2; i <= sqr; i++)
        {
            if (!vis[i]) pri[++pcnt] = i, prk[pcnt] = Pow (i, K);
            for (int j = 1; i*pri[j] <= sqr; j++)
            {
                vis[i*pri[j]] = 1;
                if (i%pri[j] == 0) break;
            }
        }
        for (int i = 1, j; i <= n; i = j + 1)
            j = n / (n / i), w[++m] = n / i, h[m] = w[m] - 1;
    }
    int id (int x) { return x > sqr ? n / x : m - x + 1; }
    uint solve (int x)
    {
        if (g[id (x)] != -1) return g[id (x)];
        uint res = f[id (x)] + h[id (x)];
        for (int i = 2, j; i <= x; i = j + 1) 
            j = x / (x / i), res -= (j - i + 1) * solve (x / i);
        return g[id(x)] = res;
    }
    int main ()
    {
        scanf ("%d%d", &n, &K), sqr = sqrt (n);
        init ();
    
        for (int j = 1; j <= pcnt; j++)
            for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; i++)
                h[i] = h[i] - h[id (w[i] / pri[j])] + j - 1; 
        for (int i = pcnt; i; i--)
            for (int j = 1; j <= m && 1ll * pri[i] * pri[i] <= w[j]; j++)
                for (ll p = pri[i]; p * pri[i] <= w[j]; p *= pri[i])
                    f[j] += f[id (w[j] / p)] + prk[i] * (h[id (w[j] / p)] - i + 1);
        memset (g, -1, sizeof (g));
        for (int i = 1, j; i <= n; i = j + 1)
        {
            j = n / (n / i);
            ans += (uint)(n / i) * (n / i) * (solve (j) - solve (i - 1));
        }
        std::cout << ans << "\n";
    }