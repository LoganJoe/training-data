---
title: " BZOJ5407girls\t\t"
tags:
  - 思路
  - 计数
url: 6758.html
id: 6758
categories:
  - Solution
date: 2019-03-03 14:52:05
---

考虑容斥。 我们拿所有的方案数，减去有至少一对边的方案数，减去至少两对边的方案数，加上三元环的方案数。 对于所有的方案数，我们直接枚举每个点计算贡献即可： $$ ans += \\times i \\times ((n - i - 1) \\times (n - i - 2) / 2) \\\ ans += \\times i \\times (n - i - 1) \\times i\\\ ans += C \\times i \\times (i \\times (i - 1) / 2)\\\ $$ 对于至少有一对连边的情况，我们枚举那条边，扣掉相应的贡献： $$ ans -= (B \\times u + C \\times v) \\times u + A \\times ( u \\times (u - 1) / 2)\\\ ans -= (A \\times u + C \\times v)\\times(v - u - 1) + B \\times ((u + v) \\times (v - u - 1) / 2)\\\ ans -= (A \\times u + B \\times v)\\times(n - v - 1) + C \\times ((v + n) \\times (n - v - 1) / 2) $$ 至于两对连边的情况，我们枚举这两条边的公共点。然后对于这个点枚举其出边，用前缀和计算贡献。

for (int i = 0; i < n; i++)
    {
        deg\[i\] = e\[i\].size ();
        std::sort (e\[i\].begin (), e\[i\].end ());
        int t = 0, tot = 0;
        for(int t=0;t<e\[i\].size();t++)
        {
            int v = e\[i\]\[t\];
            if (v < i) ans += A * v * (deg\[i\] - t - 1) + B * v * t, tot++;
            else ans += B * v * (deg\[i\] - t - 1) + C * v * t;
        }
        ans += C * i * (1ll * (tot * (tot - 1) / 2));
        ans += B * i * tot * (deg\[i\] - tot);
        ans += A * i * (1ll * (deg\[i\] - tot) * (deg\[i\] - tot - 1) / 2);
    }

剩下三元环。我们可以对于每个点按照编号排序，每条边算在度数小的那个点上。 之后枚举一条边，two-pointer的枚举两个端点的出边。对于每个枚举到的三元环扣掉相应贡献即可。