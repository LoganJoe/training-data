---
title: " DTOJ4113per\t\t"
tags:
  - Trie树
  - 思路
url: 6035.html
id: 6035
categories:
  - Solution
date: 2019-01-15 20:18:22
---

一个简单易想的思路是，最大值一定是最高位为$1$和$0$的两个数异或出来的。 找到最高的那一位，将点分为两个集合:$S,T$分别为最高位为$0$和$1$的集合。 接下来用Trie树，将其中一个集合插入$Trie$中，另外一个集合就可以在其中查到异或最大值的最小是多少。 那么考虑统计答案。对于某个异或值我们可以将其丢到$set$里面维护。而$S \\to T$肯定是交替连边的。那么相当于找到一条异或值最小的哈密顿路径。 贪心的构造解。每次在相应集合里面从编号小的开始选数，假设这个异或值合法那么就可以将其丢出来作为一个解，然后再将选出的这个数删去，扣掉计算的大小就可以了。 具体分讨的细节可以见代码。

#include<bits/stdc++.h>
#define N 300005
int n, A\[N\], S\[N\], T\[N\], bel\[N\], Min\[N\], Minp = 2e9, b\[N\], tot, ans\[N\];
long long cnt;
std::set<int> setS, setT, q\[N\];
class Trie
{
	struct tree
	{
		int son\[2\], v;
	}t\[N * 32\];
public:
	int cnt, rt;
	void insert (int v)
	{
		int x = rt;
		for (int i = 30; ~i; i--)
		{
			int k = v >> i & 1;
			if (!t\[x\].son\[k\]) t\[x\].son\[k\] = ++cnt;
			x = t\[x\].son\[k\];
		}
	}
	int query (int v)
	{
		int x = rt, res = 0;
		for (int i = 30; ~i; i--)
		{
			int k = v >> i & 1;
			if (t\[x\].son\[k\]) x = t\[x\].son\[k\];
			else x = t\[x\].son\[k ^ 1\], res += 1 << i;
		}
		return res;
	}
}Tr;
int find (int x)
{
	int t = std::lower_bound (b + 1, b + 1 + tot, x) - b;
	if (b\[t\] != x) return -1; return t;
}
bool check (int x)
{
	int tx = find (A\[x\] ^ Minp), ts = q\[tx\].size ();
	if (bel\[x\] == 1)
		if (setT.size () == 1 || setS.empty()) return 1;
		else return ts != cnt;
	else
		if (setS.size () == 1 || setT.empty ()) return 1;
		else return ts != cnt;
}
void Delete (int x)
{
	if (bel\[x\] == 1) setT.erase (x);
	else setS.erase (x);
	int tx = std::lower_bound (b + 1, b + 1 + tot, A\[x\]) - b;
	q\[tx\].erase (x);
	tx = std::lower_bound (b + 1, b + 1 + tot, A\[x\] ^ Minp) - b;
	if (b\[tx\] != (A\[x\] ^ Minp)) return;
	cnt -= q\[tx\].size ();
}
int main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A\[i\]), b\[i\] = A\[i\];
	std::sort (b + 1, b + 1 + n);
	tot = std::unique (b + 1, b + 1 + n) - b - 1;
	for (int j = 30; ~j; j--)
	{
		int cnt = 0;
		for (int i = 1; i <= n; i++) cnt += A\[i\] >> j & 1;
		if (!cnt || cnt == n) continue;
		for (int i = 1; i <= n; i++)
			if (A\[i\] >> j & 1) bel\[T\[++T\[0\]\] = i\] = 1, setT.insert (i);
			else S\[++S\[0\]\] = i, setS.insert (i);
		break;
	}
	if (setS.empty ())
	{
		for (int i = 1; i <= n; i++) printf ("%d ", i);
		return puts (""), 0;
	}
	Tr.rt = ++Tr.cnt;
	for (int i = 1; i <= T\[0\]; i++) Tr.insert (A\[T\[i\]\]);
	for (int i = 1; i <= S\[0\]; i++)
		Min\[i\] = Tr.query (A\[S\[i\]\]), Minp = std::min (Minp, Min\[i\]);
	for (int i = 1; i <= n; i++) q\[find (A\[i\])\].insert (i);
	for (int i = 1; i <= S\[0\]; i++)
	{
		int x = find (A\[S\[i\]\] ^ Minp);
		if (x != -1) cnt += q\[x\].size ();
	}
	for (int i = 1; i <= n; i++) if (check (i)) { ans\[1\] = i; break; }
	Delete (ans\[1\]);
	for (int i = 2; i <= n; i++)
	{
		int x = ans\[i - 1\]; ans\[i\] = n + 1;
		int tx = find (A\[x\] ^ Minp);
		int ts = q\[tx\].empty () ? n + 1 : *q\[tx\].begin ();
		if (check (ts)) ans\[i\] = std::min (ans\[i\], ts);
		if (bel\[x\] == 1)
			for (auto j = setT.begin (); j != setT.end (); j++)
			{
				if (*j >= ans\[i\]) break;
				if (check (\*j)) { ans\[i\] = \*j; break; }
			}
		else
			for (auto j = setS.begin (); j != setS.end (); j++)
			{
				if (*j >= ans\[i\]) break;
				if (check (\*j)) { ans\[i\] = \*j; break; }
			}
		Delete (ans\[i\]);
	}
	for (int i = 1; i <= n; i++) printf ("%d ", ans\[i\]);
	return puts ("");
}