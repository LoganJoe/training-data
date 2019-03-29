#include<bits/stdc++.h>
#define N 100005
int n, m, head[N], ecnt, deep[N], fa[N][20], f[N][3], Max[2][N][20];
std::vector<int>e[N];
void dfs (int u, int fath)
{
	fa[u][0] = fath, f[u][0] = deep[u] = deep[fath] + 1;
	for (int v : e[u])
	{
		if (v == fath) continue;
		dfs (v, u);
		if (f[v][0] >= f[u][0]) f[u][2] = f[u][1], f[u][1] = f[u][0], f[u][0] = f[v][0];
		else if (f[v][0] >= f[u][1]) f[u][2] = f[u][1], f[u][1] = f[v][0];
		else if (f[v][0] >= f[u][2]) f[u][2] = f[v][0];
	}
	for (int v : e[u])
		if (v != fath)
		{
			int w = f[u][0] != f[v][0] ? f[u][0] : f[u][1];
			Max[0][v][0] = w, Max[1][v][0] = w - deep[u] * 2;
		}
}
void process ()
{
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++)
		{
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
			Max[0][i][j] = std::max (Max[0][i][j - 1], Max[0][fa[i][j - 1]][j - 1]);
			Max[1][i][j] = std::max (Max[1][i][j - 1], Max[1][fa[i][j - 1]][j - 1]);
		}
}
int getlca (int u, int v)
{
	if (deep[u] < deep[v]) std::swap (u, v);
	for (int i = 19; ~i; i--) if (deep[fa[u][i]] >= deep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = 19; ~i; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
int jump (int u, int d) { for (int i = 19; ~i; i--) if (d >> i & 1) u = fa[u][i]; return u; }
int ask (int u, int d, int op)
{
	if (d <= 0) return -1e9; int res = -1e9;
	for (int i = 19; i; i--) if (d >> i & 1) res = std::max (res, Max[op][u][i]), u = fa[u][i];
	return res;
}
int solve (int x, int y, int v)
{
	int lca = getlca (x, y); int res = 0, to;
	if (x != lca) res = f[x][0] - deep[x];
	if (v < deep[y] - deep[lca])
	{
		res = std::max (res, deep[x] - deep[lca] * 2 + ask (to = jump (y, v), deep[to] - deep[lca] - 1, 0));
		res = std::max (res, deep[x] + ask (x, deep[x] - deep[lca] - 1, 1));
		res = std::max (res, deep[x] + ask (x, deep[lca] - 1, 1));
		int tmp = 0;
		if (x != lca)
		{
			int tx = jump (x, deep[x] - deep[lca] - 1), ty = jump (y, deep[y] - deep[lca] - 1);
			if (f[lca][0] != std::max (f[tx][0], f[ty][0])) tmp = f[lca][0];
			else if (f[lca][1] != std::min (f[tx][0], f[ty][0])) tmp = f[lca][1];
			else tmp = f[lca][2];
		}
		else tmp = f[lca][0] ^ f[jump (y, deep[y] - deep[lca] - 1)][0] ? f[lca][0] : f[lca][1];
		res = std::max (res, deep[x] + tmp - deep[lca] * 2);
	}
	else if (v == deep[y] - deep[lca])
		res = std::max (res, deep[x] + ask (x, deep[x] - deep[lca] - 1, 1));
	else
		res = std::max (res, deep[x] + ask (x, deep[x] + deep[y] - 2 * deep[lca] - v - 1, 1));
	return res;
}
int main ()
{
	scanf ("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; i++) 
		scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
	dfs (1, 0);
	while (m--)
	{
		int u, v, k, d; scanf ("%d%d%d", &u, &v, &k); 
		d = deep[u] + deep[v] - deep[getlca (u, v)] * 2;
		if (d > k) printf ("%d\n", k & 1);
		else if (!(k & 1) && (d & 1)) puts ("0");
		else if ((k & 1) && !(d & 1)) puts ("1");
		else if ((k & 1) && (d & 1))
			if (d <= (k + 1 >> 1)) puts ("2");
			else puts (solve (v, u, k + 1 >> 1) >= (k >> 1) ? "1" : "2");
		else
			if (d <= (k >> 1)) puts ("-1");
			else puts (solve (v, u, k >> 1) >= (k >> 1) ? "0" : "-1");
	}
}
