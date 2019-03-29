#include<bits/stdc++.h>
#define DEBUG 0
#define $ if(DEBUG)
#define dbg1(x) $ std::cerr << #x << "=" << x << " ";
#define dbg2(x) $ std::cerr << #x << "=" << x << "\n";
#define dbg3(x) $ for(auto v:x) std::cerr<<v<<" ";std::cerr<<"\n"
#define dbg4(x) $ std::cerr<<__FUNCTION__<<"() L"<<__LINE__<<":->: "#x"="<<(x)<<"\n"
#define N 50005
int n, Q, K, head[N], ecnt;
struct edge
{
	int v, next;
}e[N << 1];
struct query
{
	int x, v;
}A[N];
void add (int u, int v)
{
	e[++ecnt] = { v,head[u] }; head[u] = ecnt;
}
namespace Slove1
{
	int dist[4005][4005];
	void dfs (int rt, int u, int fa)
	{
		for (int i = head[u]; i; i = e[i].next)
			if (e[i].v != fa) dist[rt][e[i].v] = dist[rt][u] + 1, dfs (rt, e[i].v, u);
	}
	void Main ()
	{
		for (int i = 1; i <= n; i++) dfs (i, i, 0);
		while (Q--)
		{
			scanf ("%d", &K); int res = 0;
			for (int i = 1; i <= K; i++) scanf ("%d%d", &A[i].x, &A[i].v);
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= K; j++) if (dist[A[j].x][i] <= A[j].v) { res++; break; }
			printf ("%d\n", res);
		}
	}
} 
namespace Slove2
{
	int fa[N][20], pos[N], deep[N], tim, val[N], res;
	void dfs (int u, int fath)
	{
		fa[u][0] = fath, pos[u] = ++tim, deep[u] = deep[fa[u][0]] + 1;
		for (int i = head[u]; i; i = e[i].next)
			if (e[i].v != fath) dfs (e[i].v, u);
	}
	void process ()
	{
		for (int j = 1; j < 20; j++)
			for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
	}
	int lca (int u, int v)
	{
		if (deep[u] < deep[v]) std::swap (u, v);
		for (int i = 19; ~i; i--)
			if (deep[fa[u][i]] >= deep[v]) u = fa[u][i];
		if (u == v) return u;
		for (int i = 19; ~i; i--)
			if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
		return fa[u][0];
	}
	void dfs2 (int u, int fath)
	{
		if (val[u]) res++;
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v; if (v == fath) continue;
			if (val[u]) val[v] = std::max (val[v], val[u] - 1);
			dfs2 (v, u);
		}
		val[u] = 0;
	}
	void Main ()
	{
		dfs (1, 0);
		process ();
		while (Q--)
		{
			scanf ("%d", &K); res = 0;
			for (int i = 1; i <= K; i++) scanf ("%d%d", &A[i].x, &A[i].v);
			for (int i = 1; i <= K; i++)
				for (int x = A[i].x, v = A[i].v + 1; x && v; x = fa[x][0])
				{
					if (val[x] >= v) continue;
					val[x] = std::max (val[x], v), v--;
				}
			dfs2 (1, 0);
			printf ("%d\n", res);
		}
	}
}
int main ()
{
	freopen("svisor.in","r",stdin);
	freopen("svisor.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf ("%d%d", &u, &v), add (u, v), add (v, u);
	scanf ("%d", &Q);
	if (n <= 4000) return Slove1::Main (), 0;
	else return Slove2::Main (), 0;
}
/*
3
1 2
2 3
2 2 1 1 3 1
1 1 1

*/
