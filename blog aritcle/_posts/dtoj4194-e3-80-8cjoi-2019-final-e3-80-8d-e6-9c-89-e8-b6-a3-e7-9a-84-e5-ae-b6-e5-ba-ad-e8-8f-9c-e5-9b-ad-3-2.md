---
title: " DTOJ4194「JOI 2019 Final」有趣的家庭菜园 3\t\t"
tags:
  - dp
  - 思路
url: 6799.html
id: 6799
categories:
  - Solution
date: 2019-03-03 19:20:16
---

"不知所措啊？" 记$f\[i\]\[j\]\[k\]\[0/1/2\]$为前$i$个位置中有$j$个\`R\`，有$k$个\`G\`，并且第$i$个是\`R\`/\`G\`/\`Y\`的最小代价。 状态方程很好列出。最后的状态可以很好的保证相邻两株草不同色。我们重点考虑代价怎么计算。 考虑我们记录一下对应的草的位置，那么实际的代价就是那株草移动过来的代价了。 哇真的不想写。自己看代码吧。

#include<bits/stdc++.h>
#define N 405
int n, A\[N\], f\[2\]\[N\]\[N\]\[3\], B\[3\]\[N\], cnt\[3\], pre\[3\]\[N\];
char s\[N\];
int calc (int a, int b, int c, int op)
{
	int x;
	if (op == 0) x = B\[0\]\[a\];
	if (op == 1) x = B\[1\]\[b\];
	if (op == 2) x = B\[2\]\[c\];
	return std::max (pre\[0\]\[x - 1\] - a, 0) + std::max (pre\[1\]\[x - 1\] - b, 0) + std::max (pre\[2\]\[x - 1\] - c, 0);
}
int main ()
{
	scanf ("%d", &n);
	scanf ("%s", s + 1);
	for (int i = 1; i <= n; i++)
	{
		if (s\[i\] == 'R') A\[i\] = 0;
		if (s\[i\] == 'G') A\[i\] = 1;
		if (s\[i\] == 'Y') A\[i\] = 2;
		B\[A\[i\]\]\[++cnt\[A\[i\]\]\] = i;
		pre\[0\]\[i\] = pre\[0\]\[i - 1\], pre\[1\]\[i\] = pre\[1\]\[i - 1\], pre\[2\]\[i\] = pre\[2\]\[i - 1\];
		pre\[A\[i\]\]\[i\]++;
	}
	if (cnt\[0\] > (n + 1) / 2 || cnt\[1\] > (n + 1) / 2 || cnt\[2\] > (n + 1) / 2) return puts ("-1"), 0;
	memset (f, 63, sizeof (f));
	if (cnt\[0\]) f\[1\]\[1\]\[0\]\[0\] = B\[0\]\[1\] - 1;
	if (cnt\[1\]) f\[1\]\[0\]\[1\]\[1\] = B\[1\]\[1\] - 1;
	if (cnt\[2\]) f\[1\]\[0\]\[0\]\[2\] = B\[2\]\[1\] - 1;
	for (int i = 2, p = 0; i <= n; i++, p ^= 1)
	{
		for (int j = 0; j <= i; j++)
			for (int k = 0; k + j <= i; k++)
				for (int l = 0; l < 3; ++l) f\[p\]\[j\]\[k\]\[l\] = 1e9;
		for (int j = 0; j <= i; j++)
			for (int k = 0; k + j <= i; k++)
			{
				if (j > cnt\[0\] || k > cnt\[1\] || i - j - k > cnt\[2\]) continue;
				if (j) f\[p\]\[j\]\[k\]\[0\] = std::min (f\[p\]\[j\]\[k\]\[0\], std::min (f\[p ^ 1\]\[j - 1\]\[k\]\[1\], f\[p ^ 1\]\[j - 1\]\[k\]\[2\]) + calc (j, k, i - j - k, 0));
				if (k) f\[p\]\[j\]\[k\]\[1\] = std::min (f\[p\]\[j\]\[k\]\[1\], std::min (f\[p ^ 1\]\[j\]\[k - 1\]\[0\], f\[p ^ 1\]\[j\]\[k - 1\]\[2\]) + calc (j, k, i - j - k, 1));
				if (i - j - k) f\[p\]\[j\]\[k\]\[2\] = std::min (f\[p\]\[j\]\[k\]\[2\], std::min (f\[p ^ 1\]\[j\]\[k\]\[0\], f\[p ^ 1\]\[j\]\[k\]\[1\]) + calc (j, k, i - j - k, 2));
			}
	}
	std::cout << std::min (f\[n & 1\]\[cnt\[0\]\]\[cnt\[1\]\]\[0\], std::min (f\[n & 1\]\[cnt\[0\]\]\[cnt\[1\]\]\[1\], f\[n & 1\]\[cnt\[0\]\]\[cnt\[1\]\]\[2\])) << "\\n";

}