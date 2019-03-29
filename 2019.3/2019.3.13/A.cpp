#include<bits/stdc++.h>
#define N 1005
#define EX {puts ("-1"); exit (0);}
int n, q, rtx, rty, head[N], ecnt = 1, A[N], t[N], bel[N], suma, sumb, ans;
int S, T, dis[N], vis[N], pre[N];
std::vector<int> G[N];
struct edge
{
	int v, cap, flow, cost, next;
}e[N * 10];
void add (int u, int v, int flow, int cost)
{
	e[++ecnt] = { v,flow,0, cost,head[u] }; head[u] = ecnt;
	e[++ecnt] = { u,   0,0,-cost,head[v] }; head[v] = ecnt;
}
int dfs (int u, int fa, int top)
{
	int tp = 0, res = 0;
	if (t[u]) top = u; bel[u] = top;
	for (auto v : G[u]) if (v ^ fa) res += dfs (v, u, top);
	if (t[u]) tp = t[u], t[u] -= res, res = tp;
	if (t[u] < 0) EX;
	return res;
}
bool spfa ()
{
	for (int i = S; i <= T; i++) dis[i] = 1e9, vis[i] = 0, pre[i] = -1;
	dis[S] = 0, vis[S] = 1; std::queue<int>q; q.push (S);
	while (!q.empty ())
	{
		int u = q.front (); q.pop ();
		for (int i = head[u]; i; i = e[i].next)
			if (dis[e[i].v] > dis[u] + e[i].cost && e[i].cap > e[i].flow)
			{
				dis[e[i].v] = dis[u] + e[i].cost, pre[e[i].v] = i;
				if (!vis[e[i].v]) vis[e[i].v] = 1, q.push (e[i].v);
			}
	}
	return pre[T] != -1;
}
void Maxflowcost ()
{
	for (; spfa ();)
	{
		int Min = 1e9;
		for (int i = pre[T]; i != -1; i = pre[e[i ^ 1].v]) Min = std::min (Min, e[i].cap - e[i].flow);
		for (int i = pre[T]; i != -1; i = pre[e[i ^ 1].v])
			e[i].flow += Min, e[i ^ 1].flow -= Min, ans += Min * e[i].cost;
		suma -= Min;
	}
}
int main ()
{
	scanf ("%d%d%d", &n, &rtx, &rty); rty += n;
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 1, u, v; i < n; i++)
		scanf ("%d%d", &u, &v), G[u].push_back (v), G[v].push_back (u);
	for (int i = 1, u, v; i < n; i++)
		scanf ("%d%d", &u, &v), u += n, v += n, G[u].push_back (v), G[v].push_back (u);
	int a, b;
	for (scanf ("%d", &q); q--;) scanf ("%d%d", &a, &b), t[a] = b;
	for (scanf ("%d", &q); q--;) scanf ("%d%d", &a, &b), t[a + n] = b;
	dfs (rtx, 0, rtx), dfs (rty, 0, rty);
	S = 0, T = n * 2 + 1;
	for (int i = 1; i <= n; i++)
		if (t[i]) add (S, i, t[i], 0), suma += t[i];
	for (int i = n + 1; i <= n + n; i++)
		if (t[i]) add (i, T, t[i], 0), sumb += t[i];
	for (int i = 1; i <= n; i++) add (bel[i], bel[i + n], 1, -A[i]);
	if (suma^sumb) EX;
	Maxflowcost ();
	if (suma != 0) EX;
	printf ("%d\n", -ans);
}
