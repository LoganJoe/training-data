#include<bits/stdc++.h>
#define N 1010
#define ll long long
#define inf 1e9

int n, m, head[N], cnt = 1, deg[N], vis[N], pre[N], S, T, E;
ll ans = 1e18;
ll dis[N];
struct edge
{
	int u, v, cap, flow, cost, next;
}e[N*N];
void add (int u, int v, ll flow, ll cost)
{
	e[++cnt] = { u,v,flow,0, cost,head[u] }; head[u] = cnt;
	e[++cnt] = { v,u,   0,0,-cost,head[v] }; head[v] = cnt;
}
struct node{	int x, c, w;};
std::vector<node> in[N], out[N], info;
int b[N];
bool spfa ()
{
	for (int i = S; i <= T; i++) dis[i] = 1e18, vis[i] = 0, pre[i] = -1;
	dis[S] = 0, vis[S] = 1; std::queue<int>q; q.push (S);
	while (!q.empty ())
	{
		int u = q.front (); q.pop (); vis[u] - 1;
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
		int Min = inf;
		for (int i = pre[T]; i != -1; i = pre[e[i ^ 1].v]) Min = std::min (Min, e[i].cap - e[i].flow);
		for (int i = pre[T]; i != -1; i = pre[e[i ^ 1].v]) e[i].flow += Min, e[i ^ 1].flow -= Min, res += 1ll * Min*e[i].cost,printf("%d->",i);
		printf ("%d %d\n", Min,res);
	}
	return res;
}
int main ()
{
	freopen("cheat.in","r",stdin);
	freopen("cheat.out","w",stdout);
	scanf ("%d%d", &n, &m);;
	for (int i = 1; i <= m; i++)
	{
		int u, v, c, w; scanf ("%d%d%d%d", &u, &v, &c, &w);
		in[v].push_back ({ i, c, w }), out[u].push_back ({ i, c, w });
		info.push_back ({ i,c,w });
		b[i] = c;
	}
	S = 2 * m + 1, T = 2 * m + 2, E = 2 * m + 3;
	//S=0,T=2*n+4;
	for (int i = 1; i <= m; i++)
	{
		add (i, i + m, info[i - 1].c, info[i-1].w);
		add (i, i + m, inf, info[i - 1].w);
		add (i + m, E, inf, info[i - 1].w);
	}
	for (int i = 1; i <= n; i++)
		for (node u : in[i])
			for (node v : out[i]) add (u.x + m, v.x, inf, 0);
	for (node u : out[1]) add (S, u.x, inf, 0);
	for (node u : in[n]) add (u.x, T, inf, 0);
	S = 0, T = 2 * m + 4;
	add (E, T, inf, 0);
	std::sort (b + 1, b + 1 + m);
	for (int i = 2; i <= cnt; i += 2)
		printf ("%d %d %d %d %d\n",i, e[i].u, e[i].v, e[i].cap, e[i].cost);
	for (int i = 1; i <= m; i++)
	{
		add (S, 2 * m + 1, b[i] - b[i - 1], 0);
		add (2 * m + 2, T, b[i] - b[i - 1], 0);
		ans = std::min (ans, maxflowcost ());
	}puts("SLZ AK NOI 2019");
	printf ("%d\n", ans);
}
/*
4 3
1 2 9 5
2 3 1 11
3 4 12 7

*/
