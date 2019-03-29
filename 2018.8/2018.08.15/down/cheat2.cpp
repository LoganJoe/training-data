#include<bits/stdc++.h>
#define N 1010
#define ll long long
#define inf 1e12

int n, m, head[N], cnt = 1, vis[N], pre[N], S, T, E;
ll ans = 1e18;
ll deg[N],dis[N];
struct edge
{
	int u, v;ll cap, flow, cost;int next;
}e[N*N];
void add (int u, int v, ll flow, ll cost)
{
	e[++cnt] = { u,v,flow,0, cost,head[u] }; head[u] = cnt;
	e[++cnt] = { v,u,   0,0,-cost,head[v] }; head[v] = cnt;
}
bool spfa ()
{
	for (int i = S; i <= T; i++) dis[i] = 1e18, vis[i] = 0, pre[i] = -1;
	dis[S] = 0, vis[S] = 1; std::queue<int>q; q.push (S);
	while (!q.empty ())
	{
		int u = q.front (); q.pop (); vis[u] = 0;
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v;
			if (dis[v] > dis[u] + e[i].cost && e[i].cap > e[i].flow)
			{
				dis[v] = dis[u] + e[i].cost; pre[v] = i;
				if (!vis[v]) vis[v] = 1, q.push (v);
			}
		}
	}
	return pre[T] != -1;
}
ll maxflowcost ()
{
	ll res = 0;
	while (spfa ())
	{
		ll Min = inf;
		for (int i = pre[T]; i != -1; i = pre[e[i ^ 1].v]) Min = std::min (Min, e[i].cap - e[i].flow);
		for (int i = pre[T]; i != -1; i = pre[e[i ^ 1].v]) e[i].flow += Min, e[i ^ 1].flow -= Min, res += 1ll * Min*e[i].cost;
	}
	return res;
}
int main ()
{
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v, c, w; scanf ("%d%d%d%d", &u, &v, &c, &w); 
		deg[u] += c, deg[v] -= c;
		add (u, v, c, w), add (v, u, inf, w);
	}
	S = 0, T = n + 1;
	deg[1] += deg[n];
	add (1, n, inf, 0), add (n, 1, inf, 0);

	for (int i = 1; i < n; i++)
	{
		if (deg[i] > 0) add (S, i, deg[i], 0);
		else add (i, T, -deg[i], 0);
	}
	std::cout << maxflowcost () << "\n";
}
/*
4 3
1 2 9 5
2 3 1 11
3 4 12 7

*/
