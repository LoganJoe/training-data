---
title: " DTOJ4121签到\t\t"
tags:
  - 数学
url: 6633.html
id: 6633
categories:
  - Solution
date: 2019-02-24 15:12:45
---

我们先解决掉那$m$个质数。正难则反，我们考虑求几个数不是 $m$ 个质数中任何一个的倍数。设积性函数$g(x)$： $$g(p^c)=\\begin{cases}0 & p \\in a \\\ 1 & p \\not \\in a\\end{cases}$$ 那么$g(i)$的前缀和就是这个的答案了。可以用$Min-25$筛求出。 那么我们要考虑的问题是，有几个数 $x$ 是 $b$ 的倍数或 $f(x) = 1$， 并且 $x$ 不是 $m$ 个质数中任何一个的倍数。 同样定义积性函数$h(x)$，有 $$g(p^c)=\\begin{cases}0 & p \\in a \\\ f(p^c) & p \\not \\in a\\end{cases}$$ 然后主要问题是$b$非质数，$Min-25$的时候会有一部分答案算不清楚。实际上我们算的时候同时记一下出现$r=0$的次数，将多算的部分减掉就好了。 讲的很意识流，具体的做法可以看代码。g的求法就是普通的$Min-25$筛，$h$的区别在于后面一部分的特判。说实话我还没有写过一道$Min-25$筛能如此烦人。

#include<bits/stdc++.h>
#define N 2000005
#define M 1000000
#define ll long long
ll n, b, A\[N\], r\[N\], h\[N\], f\[N\], g\[N\], ans, tp, Min\[N\], pri\[N / 10\], B;
int m, hcnt;
int  pcnt, lstp, mark\[N\], c\[N\];
int H (ll x) { return x <= B ? x : hcnt - n / x + 1; }
int findA (ll x) { return (std::upper_bound (A + 1, A + 1 + m, x) - A - 1); }
void init ()
{
	for (int i = 2; i <= M; i++)
	{
		if (!Min\[i\]) pri\[++pcnt\] = i, Min\[i\] = pcnt;
		for (int j = 1; j <= Min\[i\] && 1ll * i * pri\[j\] <= M; j++) Min\[i*pri\[j\]\] = j;
	}
	int mark_b = 1;
	for (int i = 1; pri\[i\] * pri\[i\] <= b; i++) if (b%pri\[i\] == 0) mark_b = 0;
	if (mark_b)
	{
		A\[++m\] = b; std::sort (A + 1, A + 1 + m);
		m = std::unique (A + 1, A + 1 + m) - A - 1;
	}
	B = sqrt (n);
	for (int i = 1; i <= B; i++) h\[++hcnt\] = i;
	for (int i = B; i >= 1; i--) if (h\[hcnt\] != n / i) h\[++hcnt\] = n / i;
	std::sort (A + 1, A + 1 + m);
}
void solveother ()
{
	ll tb = b, gb = 1;
	for (int i = 1; i <= lstp; i++)
	{
		for (; b%pri\[i\] == 0; c\[i\]++, b /= pri\[i\]);
		gb *= r\[c\[i\]\];
	}
	for (int i = 1; i <= hcnt; i++) g\[i\] = 0;
	if (b > 1) gb *= r\[1\];
	for (ll i = lstp, t = b > 1 ? r\[1\] : 1; i; i--) if (!mark\[pri\[i\]\])
		g\[pri\[i\]\] += t * r\[c\[i\] + 1\], t *= r\[c\[i\]\];
	for (int i = 1; i <= B; i++) g\[i\] += g\[i - 1\];
	if (b == 1)
	{
		for (int i = B + 1; i <= hcnt; i++)
			g\[i\] = ((f\[i\] - findA (h\[i\])) - (f\[B\] - findA (B))) * r\[1\] + g\[B\];
	}
	int l = (b > 1 && r\[1\] == 0) ? 2 : 0;
	for (int j = lstp; j; j--) if (!mark\[pri\[j\]\])
	{
		for (int i = hcnt; pri\[j\] * pri\[j\] <= h\[i\]; i--)
		{
			if (r\[c\[j\]\] == 0) g\[i\] = 0;
			for (ll k = 1, p = pri\[j\]; p\*pri\[j\] <= h\[i\]; k++, p \*= pri\[j\])
			{
				g\[i\] += (g\[H (h\[i\] / p)\] - g\[pri\[j\]\]) * r\[c\[j\] + k\];
				if (!l) g\[i\] += r\[c\[j\] + k + 1\];
			}
		}
		if (r\[c\[j\]\] == 0 && !l)
		{
			for (int i = 1; pri\[j\] * pri\[j\] > h\[i\]; i++) g\[i\] = 0;
			for (int i = 1; i <= hcnt; i++)
				if (pri\[j\] <= h\[i\]) g\[i\] += r\[c\[j\] + 1\];
			l = 1;
		}
		else if (r\[c\[j\]\] == 0 && l == 1)
		{
			for (int i = 1; pri\[j\] * pri\[j\] > h\[i\]; i++) g\[i\] = 0;
			l = 2;
		}	
	}
	ans += tp - g\[H (n / tb)\] - gb;
}
int main ()
{
	scanf ("%lld%d%lld", &n, &m, &b);
	for (int i = 1; i <= m; i++) scanf ("%lld", &A\[i\]);
	for (int i = 1; i <= 60; i++) scanf ("%d", &r\[i\]);
	if (b == 1) return puts ("0"), 0; r\[0\] = 1;
	init ();
	for (int i = 1; i <= pcnt; i++) 
		if (pri\[i\] <= B) lstp = i; else break;
	for (int i = 1; i <= m; i++) if (A\[i\] <= B) mark\[A\[i\]\] = 1;
	for (int i = 1; i <= hcnt; i++) f\[i\] = h\[i\] - 1;
	for (int j = 1; j <= lstp; j++)
		for (int i = hcnt; 1ll * pri\[j\] * pri\[j\] <= h\[i\]; i--)
			f\[i\] -= f\[H (h\[i\] / pri\[j\])\] - f\[pri\[j\] - 1\];
	for (int i = 1; i <= hcnt; i++) g\[i\] = f\[i\] - findA (h\[i\]);
	for (int j = lstp; j; j--) if (!mark\[pri\[j\]\])
		for (int i = hcnt; pri\[j\] * pri\[j\] <= h\[i\]; i--)
			for (ll c = 1, p = pri\[j\]; p\*pri\[j\] <= h\[i\]; c++, p \*= pri\[j\])
				g\[i\] += g\[H (h\[i\] / p)\] - g\[pri\[j\]\] + 1;
	ans = n - g\[hcnt\] - 1, tp = g\[H (n / b)\] + 1;
	for (int i = 1; i <= hcnt; i++)
		g\[i\] = (f\[i\] - findA(h\[i\])) * r\[1\];
	for (int j = lstp; j; j--) if (!mark\[pri\[j\]\])
		for (int i = hcnt; pri\[j\] * pri\[j\] <= h\[i\]; i--)
			for (ll c = 1, p = pri\[j\]; p\*pri\[j\] <= h\[i\]; c++, p \*= pri\[j\])
				g\[i\] += (g\[H (h\[i\] / p)\] - g\[pri\[j\]\]) * r\[c\] + r\[c + 1\];
	ans += g\[hcnt\] + 1;
	int divb = 1;
	for (int i = 1; i <= m; i++) if (b%A\[i\] == 0) divb = 0;
	if (divb) solveother ();
	std::cout << n - ans << "\\n";
}