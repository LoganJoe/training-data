---
title: " DTOJ4216车\t\t"
tags:
  - 奇技淫巧
  - 容斥
url: 6918.html
id: 6918
categories:
  - Solution
date: 2019-03-10 18:51:19
---

我们可以状压枚举哪些不能放的位置放了棋子，然后用容斥计算方案数。 但是即使是这样，这个方案数还是不太好算。我们针对最难处理的对角线限制考虑容斥。用不考虑对角线的方案数减去考虑其中一条对角线的方案数加上考虑两条对角线的方案数。 不考虑对角线的方案数十分简单。若还剩下$k$行没有棋子，方案数就是$k!$。 考虑至少一条对角线没有棋子的方案数。 这样还是很难，我们可以用所有方案-至少有一个棋子的方案数+至少有两个棋子的方案数-至少有三个棋子的方案数……。假如还剩下$k$行没有棋子，其中对角线上有$cnt$个位置可以放棋子，那么一条对角线上没有棋子的方案数就是 $$ \\sum_{i=0}^{cnt}(-1)^i\\binom{cnt}{i}(k-i)! $$ 另外一条对角线同理。下面考虑最困难的两条对角线有棋子的方案数。 仍然考虑容斥。强制对角线上一些格子有棋子，然后计算剩下的 行、列方案数。 剩下行列的方案数为 $k!$。但是，强制对角线上一些格子有棋子的方案数不再是组合数了。考虑 $(i, i), (i, n−1−i), (n−1−i, i),(n−1−i, n−1−i)$ 这四个格子放了多少个棋子。那么就可以对每个 $i < \\left\\lfloor\\frac n2 \\right\\rfloor 求出这四个格子放置 $k$ 个棋子的方案数，然后背包就行了。 时间复杂度$O( 2^m n^2)$。不用FFT优化。   你不如看看我的代码，然后想一想要怎么实现它。

#include <bits/stdc++.h>
#define N 105
#define mod 10007
int T, n, m, x\[N\], y\[N\], fac\[N\], inv\[N\], cntx\[N\], cnty\[N\], ans;
int C(int a, int b) { return 1ll * fac\[a\] * inv\[b\] % mod * inv\[a - b\] % mod; }
int mul(int x) { return x >= mod ? x - mod : x; }
int solve1(int rem) {
    int res = 0, rest = n;
    for (int i = 1; i <= n; i++)
        if (cntx\[i\] || cnty\[i\])
            --rest;
    for (int i = 0; i <= rem; ++i) res = ((i & 1 ? -1 : 1) * C(rest, i) * fac\[rem - i\] + res) % mod;
    return res;
}
int solve2(int rem) {
    int res = 0, rest = n;
    for (int i = 1; i <= n; i++)
        if (cntx\[i\] || cnty\[n - i + 1\])
            --rest;
    for (int i = 0; i <= rem; ++i) res = ((i & 1 ? -1 : 1) * C(rest, i) * fac\[rem - i\] + res) % mod;
    return res;
}
int p\[N\], q\[N\];
int solve3(int rem) {
    int a = 0, b = 0, c = 0, res = 0, x, y;
    for (int l = 1, r = n; l <= r; l++, r--) {
        x = y = 1 + (l != r);
        x -= (cntx\[l\] > 0) + (l ^ r && cntx\[r\] > 0);
        y -= (cnty\[l\] > 0) + (l ^ r && cnty\[r\] > 0);
        if (x * y == 1)
            a++;
        if (x * y == 2)
            b++;
        if (x * y == 4)
            c++;
    }
    for (int i = 1; i <= n; i++) p\[i\] = q\[i\] = 0;
    p\[0\] = 1;
    int cnt = 0;
    for (int i = 1; i <= a; i++) {
        cnt++;
        for (int j = 0; j <= cnt; j++) q\[j\] = ((j < cnt ? p\[j\] : 0) + (j ? p\[j - 1\] : 0)) % mod;
        for (int j = 0; j <= cnt; j++) p\[j\] = q\[j\], q\[j\] = 0;
    }
    for (int i = 1; i <= b; i++) {
        cnt++;
        for (int j = 0; j <= cnt; j++) q\[j\] = ((j < cnt ? p\[j\] : 0) + (j ? 2 * p\[j - 1\] : 0)) % mod;
        for (int j = 0; j <= cnt; j++) p\[j\] = q\[j\], q\[j\] = 0;
    }
    for (int i = 1; i <= c; i++) {
        cnt += 2;
        for (int j = 0; j <= cnt; j++)
            q\[j\] =
                ((j < cnt - 1 ? p\[j\] : 0) + (j && j < cnt ? 4 * p\[j - 1\] : 0) + (j > 1 ? 2 * p\[j - 2\] : 0)) %
                mod;
        for (int j = 0; j <= cnt; j++) p\[j\] = q\[j\], q\[j\] = 0;
    }
    for (int i = 0; i <= rem; i++)
        res = ((i & 1 ? -1 : 1) * (i <= cnt ? p\[i\] : 0) * fac\[rem - i\] + res) % mod;
    return res;
}
int main() {
    fac\[0\] = inv\[0\] = inv\[1\] = 1;
    for (int i = 1; i < N; i++) fac\[i\] = 1ll * fac\[i - 1\] * i % mod;
    for (int i = 2; i < N; i++) inv\[i\] = 1ll * (mod - mod / i) * inv\[mod % i\] % mod;
    for (int i = 2; i < N; i++) inv\[i\] = 1ll * inv\[i - 1\] * inv\[i\] % mod;
    for (scanf("%d", &T); T--;) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; i++) scanf("%d%d", &x\[i\], &y\[i\]), x\[i\]++, y\[i\]++;
        int totS = (1 << m) - 1;
        for (int S = 0; S <= totS; S++) {
            int mark1 = 0, mark2 = 0;
            for (int i = 1; i <= n; i++) cntx\[i\] = cnty\[i\] = 0;
            int tot = 0;
            for (int i = 1; i <= m; i++)
                if (S >> (i - 1) & 1) {
                    tot++, cntx\[x\[i\]\]++, cnty\[y\[i\]\]++;
                    if (x\[i\] == y\[i\])
                        mark1 = 1;
                    if (x\[i\] == n - y\[i\] + 1)
                        mark2 = 1;
                }
            bool mark = 0;
            for (int i = 1; i <= n && !mark; i++)
                if (cntx\[i\] > 1 || cnty\[i\] > 1)
                    mark = 1;
            if (mark)
                continue;
            int coef = tot & 1 ? -1 : 1;
            if (mark1 && mark2)
                ans = (ans + coef * fac\[n - tot\]) % mod;
            else if (mark1)
                ans = (ans + coef * (fac\[n - tot\] - solve2(n - tot))) % mod;
            else if (mark2)
                ans = (ans + coef * (fac\[n - tot\] - solve1(n - tot))) % mod;
            else
                ans =
                    (ans + coef * (fac\[n - tot\] - solve1(n - tot) - solve2(n - tot) + solve3(n - tot))) % mod;
        }
        printf("%d\\n", (ans + mod) % mod);
        ans = 0;
    }
}