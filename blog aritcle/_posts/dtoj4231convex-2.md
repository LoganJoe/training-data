---
title: " DTOJ4231Convex\t\t"
tags:
  - 凸包
  - 计算几何
url: 7045.html
id: 7045
categories:
  - Solution
date: 2019-03-17 20:24:09
---

考虑答案，就是要求切一刀后较小的那一半的面积之和。 那么在凸包上，对于一个点，我们一定可以找到相对的另外一个点，满足这两点之间的劣凸壳上面积一定相对较小。这个是可以推指针求出的。 那么考虑凸包面积，即是凸包上相邻两点的叉积之和。考虑弧上的即是两两叉积前缀和的前缀和的相减，考虑中间插的一条边怎么解决。 拆开叉积的式子，就是$x\_1y\_2-x\_2y\_1$。那么当前固定了$x\_1,y\_1$,这每根的叉积均可以用$x\_i,y\_i$的前缀和直接算出了。

#include<bits/stdc++.h>
#define ll __int128
#define N 4000005
#define mod 1000000007
#define inv2 500000004
int n; 
ll sum\[N\], sum2\[N\], sumx\[N\], sumy\[N\], ans, Minx, Miny;
struct point
{
	ll x, y;
	point operator +(const point &a) const { return { x + a.x, y + a.y }; }
	point operator -(const point &a) const { return { x - a.x, y - a.y }; }
	point operator *(const ll &a) const { return { x\*a, y\*a }; }
	ll operator *(const point &a) const { return x * a.y - y * a.x; }
}A\[N\], Min;
ll calc (int a, int b) 
{
	return (sum2\[b\] - sum2\[a\] - sum\[a\] * (b - a) + (sumy\[b\] - sumy\[a\]) * A\[a\].x - (sumx\[b\] - sumx\[a\]) * A\[a\].y) % mod;
}
ll getS (int a, int b) 
{
	return sum\[b\] - sum\[a\] + A\[a\] * A\[b\]; 
}
int main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int x, y; scanf ("%d%d", &x, &y);
		A\[i\].x = x, A\[i\].y = y;
		Minx = std::min (Minx, A\[i\].x);
		Miny = std::min (Miny, A\[i\].y);
	}
	for (int i = 1; i <= n; i++) A\[i + n\] = A\[i\];
	Min = { Minx, Miny };
	for (int i = 1; i <= n << 1; i++)
	{
		A\[i\] = A\[i\] - Min;
		if (i > 1) sum\[i\] = sum\[i - 1\] + A\[i\] * A\[i - 1\], sum2\[i\] = (sum2\[i - 1\] + sum\[i\]) % mod;
		sumx\[i\] = (sumx\[i - 1\] + A\[i\].x) % mod;
		sumy\[i\] = (sumy\[i - 1\] + A\[i\].y) % mod;
	}
	ll totS = getS (1, n);
	for (int i = 1, j = 2; i <= n; i++)
	{
		for (; getS (i, j + 1) * 2 <= totS; j++);
		ans = (ans + totS % mod * (j - i - 1) + 2 * (mod - calc (i, j) % mod)) % mod;
	}
	std::cout << (int)(ans + mod) % mod << "\\n";
}