#include<bits/stdc++.h>
#define N 100005
#define ll long long

int n, Size[N], son[N], rt, rt2, vis[N], cnt[N<<1], tot, dis[N], deep[N];
int maxdep;
ll ans, g[N<<1][2], f[N<<1][2];
struct edge{int x, w;};
std::vector<edge> e[N];
void getroot (int u, int fa)
{
	Size[u] = 1;son[u] = 0;
	for (edge v : e[u])
	{
		if (v.x == fa || vis[v.x]) continue;
		getroot (v.x, u); Size[u] += Size[v.x];
		son[u] = std::max (son[u], Size[v.x]);
	}
	son[u] = std::max (son[u], tot - Size[u]);
	if (son[u] < son[rt])  rt = u;
	else if (son[u] == son[rt]) rt2 = u;
}
void dfs (int u, int fa)
{
	f[dis[u]][cnt[dis[u]] > 0]++, cnt[dis[u]]++;
	maxdep = std::max (maxdep, deep[u]);
	for (auto v : e[u])
	{
		if (v.x == fa || vis[v.x]) continue;
		deep[v.x] = deep[u] + 1, dis[v.x] = dis[u] + v.w;
		dfs (v.x, u);
	}
	cnt[dis[u]]--;
}
void solve (int u)
{
	vis[u] = 1; int Max = 0;
	g[n][0] = 1;
	for (edge v : e[u])
	{
		if (vis[v.x]) continue;
		dis[v.x] = n + v.w, deep[v.x] = 1;
		maxdep = 1, dfs (v.x, rt); 
		Max = std::max (Max, maxdep);
		maxdep=std::max(maxdep,deep[v.x]);
		ans += (g[n][0] - 1) * f[n][0];
		for (int i = -maxdep; i <= maxdep; i++)
			ans += g[n - i][0] * f[n + i][1] + g[n - i][1] * f[n + i][0] + g[n - i][1] * f[n + i][1];
		for (int i = -maxdep; i <= maxdep; i++)
			g[n + i][0] += f[n + i][0], g[n + i][1] += f[n + i][1], f[n + i][0] = f[n + i][1] = 0;
	}
	for (int i = -Max; i <= Max; i++) g[n + i][0] = g[n + i][1] = 0;
	for (edge v : e[u])
	{
		if (vis[v.x]) continue;
		tot = Size[v.x], rt = 0;
		getroot (v.x, u);
		solve (rt);
	}
}
int main ()
{
	//freopen("yinyang.in","r",stdin);
	//freopen("yinyang.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1,u,v,w; i < n; i++)
	{
		scanf ("%d%d%d", &u, &v, &w); if (!w) w = -1;
		e[u].push_back ({ v,w });
		e[v].push_back ({ u,w });
	}
	son[rt = 0] = 1e9, tot = n; getroot (1, 0);
	deep[rt] = 1; solve (rt);
	printf ("%lld\n",ans);
}
