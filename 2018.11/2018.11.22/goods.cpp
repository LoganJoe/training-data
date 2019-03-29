#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, head[N], ecnt; ll ans;
int fa[N], A[N], C[N], D[N], vis[N], Min[N], fMin[N], isrt[N], in[N], cnt;
std::vector<int>e[N];
int main ()
{
	freopen("goods.in","r",stdin);
	freopen("goods.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf ("%d%d%d%d", &fa[i], &C[i], &D[i], &A[i]), in[fa[i]]++, e[fa[i]].push_back (i);
	for (int i = 1, p; i <= n; i++)
	{
		for (int j = i; !vis[j]; p = j = fa[j]) vis[j] = 1;
		if (!in[i])
			for (int j = i, fl = 0; vis[j] == 1 && !fl; j = fa[j])
				vis[j] = -1, fl |= (j == p), isrt[j] = fl;
	}
	for (int i = 1; i <= n; i++) Min[i] = fMin[i] = 1e9, vis[i] = 0;
	for (int i = 1; i <= n; i++) Min[fa[i]] = std::min (Min[fa[i]], C[i]);
	for (int i = 1; i <= n; i++)
	{
		ll st = 1e18;
		if (!isrt[i] || vis[i]) continue;
		++cnt;
		for (int j = i; !vis[j]; j = fa[j])
		{
			if (!isrt[i]) st = std::min (st, 1ll * A[i] * (D[i] - Min[i]));
			vis[j] = cnt;
		}
		for (int j = i, fl = 0, pre = 0;; pre = j, j = fa[j])
		{
			if (!pre) continue;
			st = std::min (st, 1ll * A[i] * (D[i] - C[pre]));
			if (j == i && fl) break;
			if (j == i)fl = 1;
		}
		if (st < 0) continue;
		ans -= st;
	}
	for (int i = 1; i <= n; i++)
		if (1ll * A[i] * (D[i] - Min[i]) > 0) ans += 1ll * A[i] * (D[i] - Min[i]);
	std::cout << ans << "\n";
}
