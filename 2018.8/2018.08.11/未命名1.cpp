#include<bits/stdc++.h>
#define N 1005
#define M 100005

int n, m, q, f[N], ans[M];
int find (int x) { return f[x] == x ? f[x] : f[x] = find (f[x]); }
int head[N], ecnt = 1, scnt ;
struct edge{int u, v, w, next, mark;}e[M<<1];
void add (int u, int v, int w) {e[++ecnt] = { u,v,w,head[u] }; head[u] = ecnt;}
struct data {int opt, a, b, c, id;}A[M];
struct node
{
	int u, v, w;
	friend bool operator <(node t1, node t2) { return t1.w < t2.w; }
}s[M << 1];
class Sequence_forest
{
public:
	int fa[N][12], val[N][12], deep[N];
public:
	struct info { int v, w; };
	std::vector<info> G[N];
	void add (int u, int v, int w)
	{
		G[u].push_back ({ v,w });
		G[v].push_back ({ u,w });
	}
	void dfs (int u, int fath)
	{
		deep[u] = deep[fath] + 1;
		for (info to : G[u])
			if (to.v != fath) fa[to.v][0] = u, val[to.v][0] = to.w, dfs (to.v, u);
	}
	void process ()
	{
		dfs (1, 0);
		for (int j = 1; j < 12; j++)
			for (int i = 1; i <= n; i++) 
				fa[i][j] = fa[fa[i][j - 1]][j - 1], val[i][j] = std::max (val[i][j - 1], val[fa[i][j - 1]][j - 1]);
	}
	int LCA, Max;
	int GetLca (int u, int v)
	{
		int res = 0;
		if (deep[u] < deep[v]) std::swap (u, v);
		for (int i = 11; ~i; i--) 
			if (deep[fa[u][i]] >= deep[v]) res = std::max (res, val[u][i]), u = fa[u][i];
		LCA = u;
		if (u == v) return res;
		for (int i = 11; ~i; i--) 
			if (fa[u][i] != fa[v][i]) 
				res = std::max (res, std::max (val[u][i], val[v][i])), u = fa[u][i], v = fa[v][i];
		res = std::max (res, std::max (val[u][0], val[v][0])); LCA = fa[u][0];
		return res;
	}
	int Jump (int x) 
	{
		for (int i = 11; ~i; i--)
			if (deep[fa[x][i]] >= deep[LCA] && val[x][i] < Max) x = fa[x][i];
		if (x != LCA && val[x][0] == Max) return x;
		else return 0;
	}
	void Delete (int u, int v)
	{
		for (int i = 0; i < G[u].size (); i++)
			if (G[u][i].v == v) G[u].erase (G[u].begin () + i), i--;
	}
	void insert (int u, int v, int w)
	{
		Max = GetLca (u, v);
		if (Max <= w) return ;
		int del = Jump (u); if (!del) Jump (v);
		Delete (del, fa[del][0]);
		Delete (fa[del][0], del);
		add (u, v, w);
		process ();
	}
	
}T;
void Kruscal ()
{
	for (int i = 2; i <= ecnt; i += 2) if (!e[i].mark) s[++scnt] = { e[i].u,e[i].v, e[i].w };
	for (int i = 1; i <= n; i++) f[i] = i;
	std::sort (s + 1, s + 1 + scnt);
	for (int i = 1; i <= scnt; i++)
	{
		int fx = find (s[i].u), fy = find (s[i].v);
		if (fx != fy) f[fy] = fx, T.add (s[i].u, s[i].v, s[i].w);
	}
}
int main ()
{
	scanf ("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf ("%d%d%d", &u, &v, &w);
		add (u, v, w), add (v, u, w);
	}
	for (int i = 1; i <= q; i++)
	{
		scanf ("%d%d%d", &A[i].opt, &A[i].a, &A[i].b);
		if (A[i].opt == 1) A[i].id = ++ans[0];
		for (int k = head[A[i].a]; k; k = e[k].next)
			if (e[k].v == A[i].b) e[k].mark = e[k ^ 1].mark = 1, A[i].c = e[k].w;
	}
	Kruscal (); T.process ();
	for (int i = q; i; i--)
	{
		if (A[i].opt == 1) ans[A[i].id] = T.GetLca (A[i].a, A[i].b);
		else T.insert (A[i].a, A[i].b, A[i].c);
	}
	for (int i = 1; i <= ans[0]; i++) printf ("%d\n", ans[i]);
}
