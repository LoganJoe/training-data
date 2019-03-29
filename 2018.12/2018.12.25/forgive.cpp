#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, m, head[N], ecnt, deep[N], fa[N][20]; ll dist[N], ans;
struct edge { int v, w, next; }e[N << 1];
void add (int u, int v, int w) { e[++ecnt] = { v,w,head[u] }; head[u] = ecnt; }
struct node { int a, b; }A[N];
void dfs (int u, int fath)
{
	fa[u][0] = fath, deep[u] = deep[fath] + 1;
	for (int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].v; if (v == fath) continue;
		dist[v] = dist[u] + e[i].w, dfs (v, u);
	}
}
void process ()
{
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
}
int getlca (int u, int v)
{
	if (deep[u] < deep[v]) std::swap (u, v);
	for (int i = 19; ~i; i--) if (deep[fa[u][i]] >= deep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = 19; ~i; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
ll dis (int u, int v) { return dist[u] + dist[v] - 2 * dist[getlca (u, v)]; }
namespace solve1
{
	void Main ()
	{
		for (int i = 1; i <= m; i++)
			for (int j = 1; j < i; j++)
				ans = std::max (ans, dis (A[i].a, A[j].a) + dis (A[i].b, A[j].b));
		std::cout << ans << "\n";
	}
}
namespace solve2
{
	int mark[N]; ll f[N];
	void dfs1 (int u, int fath)
	{
		ll Max1 = 0, Max2 = 0;
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v; if (v == fath) continue;
			dfs1 (v, u);
			if (f[v] || mark[v])
			{
				f[u] = std::max (f[u], f[v] + e[i].w);
				if (f[v] + e[i].w >= Max1) Max2 = Max1, Max1 = f[v] + e[i].w;
				else if (f[v] + e[i].w >= Max2) Max2 = f[v] + e[i].v;
			}
		}
		if (mark[u]) ans = std::max (ans, f[u]);
		if (Max1 && Max2) ans = std::max (ans, Max1 + Max2);
	}
	void Main ()
	{
		for (int i = 1; i <= n; i++) mark[A[i].b] = 1;
		dfs1 (1, 0);
		std::cout << ans << "\n";
	}
}
int main ()
{
	freopen("forgive.in","r",stdin);
	freopen("forgive.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1, u, v, w; i < n; i++) 
		scanf ("%d%d%d", &u, &v, &w), add (u, v, w), add (v, u, w);
	dfs (1, 0); process ();
	for (int i = 1; i <= m; i++) scanf ("%d%d", &A[i].a, &A[i].b);
	if (m <= 5000) solve1::Main ();
	else solve2::Main ();
}
/*
6 3
1 2 3
2 3 4
2 4 8
2 5 6
1 6 2
1 3
1 5
1 6
*/
