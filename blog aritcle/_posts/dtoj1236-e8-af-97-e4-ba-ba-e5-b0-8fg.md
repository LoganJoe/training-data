---
title: " DTOJ1236诗人小G\t\t"
tags:
  - dp
  - 决策单调性
url: 6356.html
id: 6356
categories:
  - Solution
date: 2019-02-06 21:09:30
---

很容易写出朴素的动态规划方程： $f\[i\]$为前$i$个句子的最小答案。那么有： $f\[i\]=\\min_{j=0}^{i=1} \\{f\[j\]+(Sum\[i\]-Sum\[j\]+i-j-1-L)^P\\}$ $Sum\[i\]$为句子长度的前缀和。 这其实是一个$P$次偏移（还是叫什么鬼名字的我早忘了）。假设$P=2$，就是一个方差。这个可以用单调性很好的处理。 但是实际上，对于$\\forall P>0$，其都是满足决策单调性的。 那么我们还是要用一个单调栈来处理整个东西的单调性。 具体实现看代码吧。

#include<bits/stdc++.h>
#define db long double
#define N 100005
int T, n, L, p, sum\[N\], head, tail;
char ch\[N\];
struct node
{
    int p, l, r;
}que\[N\];
db f\[N\];
db Pow (db x, int k) { db t = 1; for (; k; k >>= 1, x = x * x) if (k & 1) t = t * x; return t; }
db calc (int x, int y) { return f\[x\] + Pow (fabs (sum\[y\] - sum\[x\] + y - x - 1 - L), p); }
int main ()
{
    for (scanf ("%d", &T); T--;)
    {
        scanf ("%d%d%d", &n, &L, &p);
        for (int i = 1; i <= n; i++) scanf ("%s", ch), sum\[i\] = sum\[i - 1\] + strlen (ch);
        que\[head = tail = 1\] = { 0,0,n };
        for (int i = 1; i <= n; i++) 
        {
            que\[head\].l++; if (que\[head\].l > que\[head\].r) head++;
            f\[i\] = calc (que\[head\].p, i);
            for (; head <= tail && calc (i, que\[tail\].l) < calc (que\[tail\].p, que\[tail\].l); tail--);
            if (head > tail) que\[++tail\] = { i,i,n };
            else if (calc (i, n) < calc (que\[tail\].p, n))
            {
                int l = que\[tail\].l, r = n;
                while (l < r)
                {
                    int mid = l + r >> 1;
                    if (calc (i, mid) < calc (que\[tail\].p, mid)) r = mid;
                    else l = mid + 1;
                }
                que\[tail\].r = r - 1, que\[++tail\] = { i,r,n };
            }
        }
        if (f\[n\] > 1e18) puts ("Too hard to arrange");
        else printf ("%lld\\n", (long long)f\[n\]);
        puts ("--------------------");
    }
}

    另外还有一个1D1D的动态规划方法但是我不会。