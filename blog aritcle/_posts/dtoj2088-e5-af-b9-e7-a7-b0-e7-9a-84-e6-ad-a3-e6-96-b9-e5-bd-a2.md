---
title: " DTOJ2088对称的正方形\t\t"
tags:
  - hash
url: 5268.html
id: 5268
categories:
  - Solution
date: 2018-11-23 10:02:27
---

既然一维数组有前缀和和hash前缀和，二维数组也就有二位前缀和和二维前缀和hash了啦！ 每次按照二维前缀和的处理方法处理出hash前缀和。那么每次枚举对称点，二分大小然后hash判定就好了。

#include<bits/stdc++.h>
#define N 2005
#define ull unsigned long long
#define P1 19990213
#define P2 19260817
int n, m, A\[N\]\[N\];
ull ha1\[N\]\[N\], ha2\[N\]\[N\], ha3\[N\]\[N\], ha4\[N\]\[N\], po1\[N\], po2\[N\], ans;
bool check (int x, int y, int len)
{
    ull h1 = ha1\[x\]\[y\] - ha1\[x - len\]\[y\] * po1\[len\] - ha1\[x\]\[y - len\] * po2\[len\] + ha1\[x - len\]\[y - len\] * po1\[len\] * po2\[len\];
    ull h2 = ha2\[x\]\[y\] - ha2\[x - len\]\[y\] * po1\[len\] - ha2\[x\]\[y + len\] * po2\[len\] + ha2\[x - len\]\[y + len\] * po1\[len\] * po2\[len\];
    ull h3 = ha3\[x\]\[y\] - ha3\[x + len\]\[y\] * po1\[len\] - ha3\[x\]\[y - len\] * po2\[len\] + ha3\[x + len\]\[y - len\] * po1\[len\] * po2\[len\];
    ull h4 = ha4\[x\]\[y\] - ha4\[x + len\]\[y\] * po1\[len\] - ha4\[x\]\[y + len\] * po2\[len\] + ha4\[x + len\]\[y + len\] * po1\[len\] * po2\[len\];
    return h1 == h2 && h2 == h3 && h3 == h4;
}
void solve (int x, int y)
{
    int l = 1, r = std::min (std::min (x, n - x + 1), std::min (y, m - y + 1)), res = 1;
    for (int mid; l <= r;) mid = (l + r) >> 1, check (x, y, mid) ? (l = mid + 1, res = mid) : r = mid - 1;
    ans += res >> 1;
}
int main ()
{
    scanf ("%d%d", &n, &m); n = n << 1 | 1, m = m << 1 | 1;
    for (int i = 2; i <= n; i += 2)
        for (int j = 2; j <= m; j += 2)
            scanf ("%d", &A\[i\]\[j\]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ha1\[i\]\[j\] = ha1\[i - 1\]\[j\] * P1 + ha1\[i\]\[j - 1\] * P2 - ha1\[i - 1\]\[j - 1\] * P1*P2 + A\[i\]\[j\];
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            ha2\[i\]\[j\] = ha2\[i - 1\]\[j\] * P1 + ha2\[i\]\[j + 1\] * P2 - ha2\[i - 1\]\[j + 1\] * P1*P2 + A\[i\]\[j\];
    for (int i = n; i >= 1; i--)
        for (int j = 1; j <= m; j++)
            ha3\[i\]\[j\] = ha3\[i + 1\]\[j\] * P1 + ha3\[i\]\[j - 1\] * P2 - ha3\[i + 1\]\[j - 1\] * P1*P2 + A\[i\]\[j\];
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
            ha4\[i\]\[j\] = ha4\[i + 1\]\[j\] * P1 + ha4\[i\]\[j + 1\] * P2 - ha4\[i + 1\]\[j + 1\] * P1*P2 + A\[i\]\[j\];
    po1\[0\] = po2\[0\] = 1;
    for (int i = 1; i <= std::max (n, m); i++)
        po1\[i\] = po1\[i - 1\] * P1, po2\[i\] = po2\[i - 1\] * P2;
    for (int i = 1; i <= n; i += 2)
        for (int j = 1; j <= m; j += 2) solve (i, j);
    for (int i = 2; i <= n; i += 2)
        for (int j = 2; j <= m; j += 2) solve (i, j);
    std::cout << ans << "\\n";
}