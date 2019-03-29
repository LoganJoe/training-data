#include<bits/stdc++.h>
#define N 300005
#define ll long long
int n, m, S, T, head[N], ecnt = 1, ans;
struct edge
{
	int v; ll w; int next;
}e[N << 2];
void add (int u, int v, ll w)
{
	e[++ecnt] = { v,w,head[u] }; head[u] = ecnt;
}
namespace solve1
{
	struct node
	{
		int x; ll dis;
		friend bool operator <(node t1, node t2) { return t1.dis > t2.dis; }
	};
	struct info
	{
		int u, v; ll w;
		friend bool operator <(info t1, info t2) { return t1.w < t2.w; }
	}s[N << 2];
	int cnt, vis[N];
	ll dis[N], disS[N];
	void Dijkstra_Heap (int ST)
	{
		std::priority_queue<node>q;
		for (int i = 1; i <= n; i++) dis[i] = 1e18;
		dis[ST] = 0; q.push ({ ST,0 });
		while (!q.empty ())
		{
			node u = q.top (); q.pop ();
			if (u.dis != dis[u.x]) continue;
			for (int i = head[u.x]; i; i = e[i].next)
				if (dis[e[i].v] > dis[u.x] + e[i].w && e[i].w <= 1e9)
					dis[e[i].v] = dis[u.x] + e[i].w, q.push ({ e[i].v,dis[e[i].v] });
		}
	}
	void dfs (int ST)
	{
		for (int i = 1; i <= n; i++) dis[i] = 1e18;
		std::queue<int>q; dis[S] = 0, vis[S] = 1; q.push (S);
		while (!q.empty ())
		{
			int u = q.front (); q.pop (); vis[u] = 0;
			for (int i = head[u]; i; i = e[i].next)
				if (dis[e[i].v] > std::max (dis[u], e[i].w))
				{
					dis[e[i].v] = std::max (dis[u], e[i].w);
					if (!vis[e[i].v]) vis[e[i].v] = 1, q.push (e[i].v);
				}
		}

	}
	void Main ()
	{
		Dijkstra_Heap (S);
		for (int i = 1; i <= n; i++) disS[i] = dis[i];
		for (int i = 1; i <= n; i++)
			for (int k = head[i]; k; k = e[k].next)
			{
				int to = e[k].v, tp = e[k].w; e[k].w = e[k ^ 1].w = 2e9;
				Dijkstra_Heap (T);
				s[++cnt] = { i,to,std::max (dis[i] + disS[i], disS[i] + dis[to] + tp) };
				e[k].w = e[k ^ 1].w = tp;
			}
		for (int i = 1; i <= n; i++) head[i] = 0; ecnt = 1;
		for (int i = 1; i <= cnt; i++) add (s[i].u, s[i].v, s[i].w);
		dfs (S);
		if (dis[T] > 1e15) std::cout << "-1\n";
		else  std::cout << dis[T] << "\n";
	}
}
int main ()
{
	scanf ("%d%d%d%d", &n, &m, &S, &T);
	for (int i = 1, u, v, w; i <= m; i++)
		scanf ("%d%d%d", &u, &v, &w), add (u, v, w), add (v, u, w);
	if (n <= 1000 && m <= 3000) solve1::Main ();
}

