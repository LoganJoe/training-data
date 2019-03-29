#include<bits/stdc++.h>
#define N 5000005
int n, m, b, mark[N], f[N], R[N], ans;
int pri[N], vis[N], pcnt;
void init ()
{
	for (int i = 2; i < N; i++)
	{
		if (!vis[i]) pri[++pcnt] = i;
		for (int j = 1; j <= pcnt && i*pri[j] < N; j++)
		{
			vis[i*pri[j]] = 1;
			if (i%pri[j] == 0) break;
		}
	}
}
int main ()
{
	freopen ("qiandao.in", "r", stdin);
	freopen ("qiandao.out", "w", stdout);
	scanf ("%d%d%d", &n, &m, &b);
	init ();
	for (int i = b; i <= n; i += b) mark[i] = 1;
	for (int i = 1; i <= n; i++) f[i] = 1;
	for (int i = 1; i <= m; i++)
	{
		int x; scanf ("%d", &x);
		for (int t = x; t <= n; t += x) mark[t] = 1;
	}
	for (int i = 1; i <= 60; i++) scanf ("%d", &R[i]);
	
	for (int i = 1; i <= pcnt && pri[i] <= n; i++)
		for (int x = pri[i], r = 1; x <= n; x *= pri[i], r++) f[x] &= R[r];
	for (int i = 1; i <= n; i++) if (!f[i])
		for (int x = i; x <= n; x += i) f[x] &= f[i];
	for (int i = 1; i <= n; i++) if (!mark[i] && !f[i]) ans++;
	printf ("%d\n", ans);
}
/*
20 1 4 3 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/
