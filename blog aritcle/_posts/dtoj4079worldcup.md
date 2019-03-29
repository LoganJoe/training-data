---
title: " DTOJ4079worldcup\t\t"
tags:
  - 多项式
  - 多项式求逆
  - 奇技淫巧
  - 数学
url: 5663.html
id: 5663
categories:
  - Solution
date: 2018-12-19 22:55:36
---

多项式神仙题。

首先要考虑答案怎么得到。由于期望是具有线性性的，期望的和等于和的期望。考虑怎么处理$m$次幂的对应期望。

不妨记$E(A\_i^k)$为在$\[0,A\_i\]$间连续型随机变量的期望值。由于带着次幂，不可以直接线性乘。考虑积分计算。积分计算的是一个函数与坐标轴间围成的面积，而考虑横轴就是概率可以取到的区间。考虑对应连续型随机概率的期望就是面积除以横轴长度。

根据微积分基本定理，其不定积分有$\\int A\_i^k \\mathrm{dx}=\\frac{A\_i^{k+1}}{k+1}$。于是有$E(A\_i^k)=\\frac{A\_i^k}{k+1}$。

考虑对于原先的多项式进行展开，那么

$$E((x\_1+x\_2+…+x\_n)^m)=\\sum\_{p\_1+p\_2+…+p\_n=m} \\space\\left\[ \\prod\_{i=1}^{n}E(A\_i^{p\_i}) \\times \\frac{m!}{\\prod_{i=1}^{n}p_i!}\\right\]$$  
这个被称为多项式定理。可以通过二项式定理推广得到。

接下来继续考虑这个东西怎么计算。注意到展开后所有的多项式都是$m$次齐次式。那么我们只需要计算所有的$m$次齐次式除以$\\prod_{i=1}^{n}p_i!$就好了。

将所有的$A\_i$拆开考虑。记形式幂级数$f\_i(x)=\\frac{A\_i^{k}}{(k+1)!} x^k$。第$k$项就是$A\_i$作为齐次式中充当$k$项的贡献、那么考虑将$f\_1(x)…f\_n(x)$共$n$个$\[m\]$幂级数做卷积，最后卷成多项式中$f(m)$就是所有齐次式的贡献和了。

这样做是$\\Theta (n^2 \\log n)$的。继续考虑优化。

发现，我们需要将$n$个形式幂级数卷在一起的原因就是因为$(k+1)!$的贡献不同。假设我们没有底下的$(k+1)!$，要将$n$个幂级数$f'i(x)=A\_i^k x^k$卷在一起，相当于每次做dp转移：$f\[i\]$为有$i$次齐次式的答案。那么容易写出转移:$f\[i\]=\\sum{j=0}^{i-1}f\[j\]g\[i-j\]$。其中$g\[i\]$为$\\sum\_{k=1}^{n}A\_k^i$。这个是很显然的，因为不管怎样，$g\[i\]$都是其中一项对于整个齐次式走$k$次的代价。假设我们可以预处理出$g(x)=\[\\sum\_{i=1}^{n}A\_i^k \]x^k $的前$m+1$项，我们就可以用分治$NTT$算出$f'\_i(x)$卷在一起的答案。

回过头来考虑有$\\frac{1}{(k+1)!}$时如何处理。

回顾多项式的复合的相关知识。仍然设$g(x)=\[\\sum_{i=1}^{n}A\_i^k\]x^k,p(x)=\\frac{1}{(k+1)!}x^k$,那么我们可以发现，实际上，$\\prod f\_i(x)=g\\circ p(x)$。

如何考虑这个问题？可以发现，上面幂级数$f’i(x)$卷在一起的答案（不考虑$(k+1)!$的答案）实际上是$g(x)$与$\\frac{1}{1-x}$的复合。那么另外考虑上面的将$x^k$替换为$\\frac{1}{(k+1)!}x^k$,那么答案就可以表示为$g(x)=\[\\sum{i=1}^{n}A_i^k \]x^k$与$p(x)=\\frac{1}{(k+1)!}x^k$的复合了。

形式幂级数的复合可以应用多项式ln和多项式exp解决。具体可以参看另外一篇关于生成函数与多项式相关的总结。

下面问题主要在于如何处理$g(x)=\[\\sum_{i=1}^nA_i^k\]x^k$。

对于数列$<1,A\_i,A\_i^2,\\Lambda,A\_i^n>$，其生成函数即为$\\frac{1}{1-A\_ix}$。

那么就可以得到，$g(x)=\\sum A(x)=\\prod \\frac{1}{1-A_ix}$。

于是我们将$n$个多项式$1-A_ix$乘在一起算出分子*分母的逆元就可以得到 $g(x)$ 了。

从前往后暴乘多项式是不行的。我们分治就可以做到$\\Theta(n \\log^2 n)$。

这部分的知识外延极广，尤其是关于复合的化简比较抽象。对于有推导部分不理解的请务必参看另外一篇文章。

代码：

#include<bits/stdc++.h>

#define ll long long
#define N 300005
#define mod 998244353

ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod)
		if (k & 1) t = t * x%mod;
	return t;
}
int mul (int x) { return x >= mod ? x - mod : x; }

class NTT
{
public:
	int rev\[N\], len, clc, g1 = 3, g2 = 332748118, invn;
	void process (int L)
	{
		for (len = 1, clc = 0; len < L; len <<= 1, clc++); invn = Pow (len, mod - 2);
		for (int i = 0; i < len; i++) rev\[i\] = (rev\[i >> 1\] >> 1) | ((i & 1) << clc - 1);
	}
	void transform (int *s, int op)
	{
		for (int i = 0; i < len; i++) if (i < rev\[i\]) std::swap (s\[i\], s\[rev\[i\]\]);
		for (int i = 1; i < len; i <<= 1)
		{
			int wn = Pow (op > 0 ? g1 : g2, (mod - 1) / (i << 1));
			for (int j = 0; j < len; j += i << 1)
				for (int k = 0, w = 1; k < i; k++, w = 1ll * w * wn%mod)
				{
					int A = s\[j + k\], B = 1ll * s\[i + j + k\] * w%mod;
					s\[j + k\] = mul (A + B), s\[i + j + k\] = mul (A - B + mod);
				}
		}
		if (op < 0) for (int i = 0; i < len; i++) s\[i\] = 1ll * s\[i\] * invn % mod;
	}
	void times (int \*a, int \*b, int *c, int L)
	{
		process (L << 1);
		for (int i = L; i < len; i++) a\[i\] = b\[i\] = 0;
		transform (a, 1), transform (b, 1);
		for (int i = 0; i < len; i++) c\[i\] = 1ll * a\[i\] * b\[i\] % mod;
		transform (c, -1);
		for (int i = L; i < len; i++) c\[i\] = 0;
	}
	std::vector<int> times (std::vector<int> a, std::vector<int> b)
	{
		process (a.size () + b.size () - 1);
		int lena = a.size (), lenb = b.size ();
		static int x\[N\], y\[N\];
		for (int i = 0; i < len; i++)
			x\[i\] = i < lena ? a\[i\] : 0, y\[i\] = i < lenb ? b\[i\] : 0;
		times (x, y, x, lena + lenb - 1);
		return std::vector <int> (x, x + lena + lenb - 1);
	}
}F;
void getInv (int \*a, int \*b, int len)
{
	if (len == 1) return (void)(b\[0\] = Pow (a\[0\], mod - 2));
	getInv (a, b, len + 1 >> 1);
	static int tp\[N\];
	F.process (len << 1);
	for (int i = 0; i < F.len; i++) tp\[i\] = i < len ? a\[i\] : 0, b\[i\] = i < (len + 1 >> 1) ? b\[i\] : 0;
	F.transform (tp, 1), F.transform (b, 1);
	for (int i = 0; i < F.len; i++) tp\[i\] = 1ll * b\[i\] * mul (2 - 1ll * tp\[i\] * b\[i\] % mod + mod) % mod;
	F.transform (tp, -1);
	for (int i = 0; i < F.len; i++) b\[i\] = i < len ? tp\[i\] : 0;
}
void getDer (int \*a, int \*b, int len)
{
	for (int i = 0; i < len; i++)
		b\[i\] = 1ll * a\[i + 1\] * (i + 1) % mod;
}
void getInt (int \*a, int \*b, int len)
{
	for (int i = 1; i <= len; i++)
		b\[i\] = 1ll * a\[i - 1\] * Pow (i, mod - 2) % mod;
}
void getLn (int \*a, int \*b, int len)
{
	static int Der\[N\], Inv\[N\];
	for (int i = 0; i < len << 1; i++) Der\[i\] = Inv\[i\] = 0;
	getDer (a, Der, len), getInv (a, Inv, len);
	F.times (Der, Inv, Inv, len), getInt (Inv, b, len);
	for (int i = len; i < F.len; i++) b\[i\] = 0;
}
void getExp (int \*a, int \*b, int len)
{
	if (len == 1) return (void)(b\[0\] = 1);
	getExp (a, b, len + 1 >> 1);
	static int tp\[N\];
	for (int i = 0; i < len << 1; i++) tp\[i\] = 0;
	getLn (b, tp, len);
	for (int i = 0; i < F.len; i++) tp\[i\] = i < len ? mul (a\[i\] + (!i) - tp\[i\] + mod) : 0;
	F.times (b, tp, tp, len);
	for (int i = 0; i < F.len; i++) b\[i\] = i < len ? tp\[i\] : 0;
}
void getsqr (int \*a, int \*b, int len)
{
	if (len == 1) return (void)(b\[0\] = sqrt (a\[0\]));
	getsqr (a, b, len + 1 >> 1);
	static int tp\[N\], tx\[N\];
	for (int i = 0; i < len; i++) tx\[i\] = a\[i\], tp\[i\] = 0;
	getInv (b, tp, len);
	F.process (len << 1);
	F.transform (tp, 1); F.transform (tx, 1);
	for (int i = 0; i < F.len; i++) tp\[i\] = 1ll * tp\[i\] * tx\[i\] % mod;
	F.transform (tp, -1);
	for (int i = 0; i < len; i++) b\[i\] = 1ll * mul (b\[i\] + tp\[i\]) * (mod + 1 >> 1) % mod;
	for (int i = 0; i < F.len; i++) tp\[i\] = 0;
}
std::vector <int> Mul (std::vector <std::vector <int> > &x, int l, int r)
{
	if (l == r - 1) return x\[l\];
	int mid = l + r >> 1;
	std::vector<int> L = Mul (x, l, mid), R = Mul (x, mid, r);
	return F.times (L, R);
}
int n, m, A\[N\], f\[N\], g\[N\], fac\[N\], inv\[N\];
int invg\[N\], invp\[N\], tp\[N\];
std::vector <std::vector <int> > P;
int main ()
{
	scanf ("%d%d", &n, &m);
	fac\[0\] = inv\[0\] = inv\[1\] = 1;
	for (int i = 1; i <= m + 1; i++) fac\[i\] = 1ll * fac\[i - 1\] * i % mod;
	for (int i = 2; i <= m + 1; i++) inv\[i\] = 1ll * (mod - mod / i) * inv\[mod%i\] % mod;
	for (int i = 2; i <= m + 1; i++) inv\[i\] = 1ll * inv\[i - 1\] * inv\[i\] % mod;
	for (int i = 1; i <= n; i++)
	{
		scanf ("%d", &A\[i\]);
		P.push_back (std::vector <int> {1, mod - A\[i\]});
	}
	std::vector<int> res = Mul (P, 0, P.size ());
	for (int i = 0; i <= n; i++) f\[i\] = res\[i\];
	while (res.size () < m + 1) res.push_back (0);
	while (res.size () > m + 1) res.pop_back ();
	for (int i = 0; i <= m; i++) g\[i\] = res\[i\];
	getInv (g, invg, m + 1);
	for (int i = 0; i <= n; i++) f\[i\] = 1ll * f\[i\] * (n - i) % mod;
	F.times (f, invg, f, m + 1);
	for (int i = 0; i <= m; i++) invp\[i\] = inv\[i + 1\];
	getLn (invp, tp, m + 1);
	for (int i = 0; i <= m; i++) tp\[i\] = 1ll * tp\[i\] * f\[i\] % mod;
	getExp (tp, f, m + 1);
	std::cout << 1ll * f\[m\] * fac\[m\] % mod << "\\n";
}