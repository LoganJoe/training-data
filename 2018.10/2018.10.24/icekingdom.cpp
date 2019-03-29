#include<bits/stdc++.h>
#define N 200005
int n, Q, head[N], ecnt;
struct edge { int v, next; }e[N << 1];
void add (int u, int v) { e[++ecnt] = { v,head[u] }; head[u] = ecnt; }
namespace solve1
{
	int l, r, vis[N], ans;
	void dfs (int u, int fa)
	{
		vis[u] = 1;
		for (int i = head[u]; i; i = e[i].next)
			if (e[i].v != fa && !vis[e[i].v]) dfs (e[i].v, u);
	}
	void Main ()
	{
		while (Q--)
		{
			scanf ("%d%d", &l, &r); ans = 0;
			for (int i = 1; i <= n; i++) vis[i] = (i <l || i >r);
			for (int i = 1; i <= n; i++) if (!vis[i]) dfs (i, 0), ans++;
			printf ("%d\n", ans);
		}
	}
}
namespace solve2
{
	struct qry
	{
		int l, r, id, block;
		friend bool operator <(qry t1, qry t2)
		{
			return t1.block < t2.block || t1.block == t2.block && ((t1.block & 1) ? (t1.r < t2.r) : (t1.r > t2.r));
		}
	}q[N];
	int ans, res[N];
	class graph
	{
		int mark[N];
	public:
		void add (int x)
		{
			ans++;
			for (int i = head[x]; i; i = e[i].next)
				if (mark[e[i].v]) ans--;
			mark[x] = 1;
		}
		void del (int x)
		{
			ans--;
			for (int i = head[x]; i; i = e[i].next)
				if (mark[e[i].v]) ans++;
			mark[x] = 0;
		}
	}G;
	void Main ()
	{
		int kuai = sqrt (n);
		for (int i = 1; i <= Q; i++)
		{
			scanf ("%d%d", &q[i].l, &q[i].r);
			q[i].id = i;
			q[i].block = (q[i].l - 1) / kuai + 1;
		}
		std::sort (q + 1, q + 1 + Q);
		G.add(1); int l = 1, r = 1;
		for (int i = 1; i <= Q; i++)
		{
			while (l > q[i].l) G.add (--l);
			while (r < q[i].r) G.add (++r);
			while (l < q[i].l) G.del (l++);
			while (r > q[i].r) G.del (r--);
			res[q[i].id] = ans;
		}
		for (int i = 1; i <= Q; i++) printf ("%d\n", res[i]);
	}
}
int main ()
{
	freopen ("icekingdom.in", "r", stdin);
	freopen ("icekingdom.out", "w", stdout);
	scanf ("%d%d", &n, &Q);
	for (int i = 1, u, v; i < n; i++) scanf ("%d%d", &u, &v), add (u, v), add (v, u);
	if (n <= 2000 && Q <= 2000) return solve1::Main (), 0;
	else return solve2::Main (), 0;
}
