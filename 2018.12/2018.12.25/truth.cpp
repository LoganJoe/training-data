#include<bits/stdc++.h>
#define N 105
int n, m, A[N], S, T, head[N], ecnt = 1, dis[N], vis[N], cur[N], ans;
struct edge { int v, cap, flow, next; }e[N * N * 4];
void add (int u, int v, int w)
{
	e[++ecnt] = { v,w,0,head[u] }; head[u] = ecnt;
	e[++ecnt] = { u,0,0,head[v] }; head[v] = ecnt;
}
bool bfs ()
{
	for (int i = S; i <= T; i++) dis[i] = vis[i] = 0, cur[i] = head[i];
	std::queue<int>q; q.push (S); vis[S] = 1;
	while (!q.empty ())
	{
		int u = q.front (); q.pop ();
		for (int i = head[u]; i; i = e[i].next)
			if (!vis[e[i].v] && e[i].cap > e[i].flow)
			{
				dis[e[i].v] = dis[u] + 1, vis[e[i].v] = 1;
				if (e[i].v == T) return 1;
				q.push (e[i].v);
			}
	}
	return 0;
}
int dfs (int u, int res)
{
	if (u == T || res == 0) return res;
	int flow = 0, f;
	for (int &i = cur[u]; i && res; i = e[i].next)
		if (dis[e[i].v] == dis[u] + 1 && (f = dfs (e[i].v, std::min (res, e[i].cap - e[i].flow))) > 0)
			e[i].flow += f, e[i ^ 1].flow -= f, flow += f, res -= f;
	return flow;
}
int Dinic ()
{
	int sum = 0;
	while (bfs ()) sum += dfs (S, 1e9);
	return sum;
}
int main ()
{
	freopen("truth.in","r",stdin);
	freopen("truth.out","w",stdout);
	scanf ("%d%d", &n, &m), S = 0, T = n * 2 + 1;
	for (int i = 1; i <= n; i++)
	{
		scanf ("%d", &A[i]);
		if (A[i] > 0) add (S, i, A[i]), ans += A[i];
		else add (i, i + n, -A[i]);
		add (i + n, T, 1e9);
	}
	for (int i = 1, a, b; i <= m; i++) scanf ("%d%d", &a, &b), add (a, b, 1e9);
	std::cout << ans - Dinic () << "\n";
}
