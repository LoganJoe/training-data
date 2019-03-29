#include<bits/stdc++.h>
#define N 200005
int n, head[N], ecnt, dis[N], ans=1e9;
struct edge
{
	int v, next;
}e[N << 1];
void add (int u, int v) { e[++ecnt] = { v,head[u] }; head[u] = ecnt; }
void dfs (int u, int fa,int d)
{
	dis[u] = std::min (dis[u], d);
	for (int i = head[u]; i; i = e[i].next)
		if (e[i].v != fa) dfs (e[i].v, u, d + 1);
}
int main ()
{
	freopen("ob.in","r",stdin);
	freopen("ob.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf ("%d %d", &u, &v), add (u, v), add (v, u);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			int res = 0;
			if (i == j) continue;
			for (int k = 1; k <= n; k++) dis[k] = 1e9;
			dfs (i, 0, 0), dfs (j, 0, 0);
			for (int k = 1; k <= n; k++) res = std::max (res, dis[k]);
			ans = std::min (ans, res);
		}
	printf ("%d\n", ans);
}
