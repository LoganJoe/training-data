#include<bits/stdc++.h>
#define N 100005
#define db double
int n, m, head[N], ecnt, d[N];
struct edge { int v, next; }e[N << 1];
void add (int u, int v) { e[++ecnt] = { v,head[u] }; head[u] = ecnt; }
struct node
{
	int x; db dis;
	friend bool operator <(node t1, node t2) { return t1.dis > t2.dis; }
};
db dis[N], sum[N]; bool vis[N];
void Dijkstra_Heap ()
{
	for (int i = 1; i <= n; i++) dis[i] = 1e15, vis[i] = 0;
	std::priority_queue<node>q; q.push ({ n,dis[n] = 0 });
	while (!q.empty ())
	{
		node u = q.top (); q.pop ();
		if (u.dis != dis[u.x]) continue;
		vis[u.x] = 1;
		for (int i = head[u.x]; i; i = e[i].next) if (!vis[e[i].v])
		{
			d[e[i].v]++, sum[e[i].v] += dis[u.x];
			dis[e[i].v] = 1. * (m + sum[e[i].v]) / d[e[i].v];
			q.push ({ e[i].v,dis[e[i].v] });
		}
	}
}
int main ()
{
	freopen ("path.in", "r", stdin);
	freopen ("path.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1, u, v; i <= n; i++) 
		scanf ("%d%d", &u, &v), add (u, v), add (v, u);
	Dijkstra_Heap ();
	printf ("%.10lf\n", dis[1]);
}
