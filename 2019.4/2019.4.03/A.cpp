#include<bits/stdc++.h>
#define N 3005
#define M 1000005
int Case, n, m, A[N], pri[M], pvis[M], pcnt, S, T, id[N], tot, vcnt[N], sum[N], col[N], ans;
void init ()
{
	for (int i = 2; i < M; i++)
	{
		if (!pvis[i]) pri[++pcnt] = i;
		for (int j = 1; j <= pcnt && i*pri[j] < M; j++)
		{
			pvis[i*pri[j]] = 1;
			if (i%pri[j] == 0) break;
		}
	}
}
class Flow
{
	struct edge
	{
		int v, cap, flow, next;
	}e[N << 2];
	int head[N], ecnt, vis[N], dis[N], cur[N];
	bool bfs ()
	{
		for (int i = S; i <= T; i++) vis[i] = dis[i] = 0, cur[i] = head[i];
		std::queue<int> q; q.push (S); vis[S] = 1;
		while (!q.empty ())
		{
			int u = q.front (); q.pop ();
			for (int i = head[u]; i; i = e[i].next)
				if (!vis[e[i].v] && e[i].cap > e[i].flow)
				{
					dis[e[i].v] = dis[u] + 1;
					if (e[i].v == T) return 1;
					vis[e[i].v] = 1, q.push (e[i].v);
				}
		}
		return 0;
	}
	int dfs (int u, int res)
	{
		if (u == T || res == 0) return res;
		int flow = 0, f;
		for (int &i = cur[u]; i; i = e[i].next)
			if (dis[e[i].v] == dis[u] + 1 && (f = dfs (e[i].v, std::min (res, e[i].cap - e[i].flow))) > 0)
				e[i].flow += f, e[i ^ 1].flow -= f, flow += f, res -= f;
		return flow;
	}
public:
	int Dinic ()
	{
		int sum = 0;
		while (bfs ()) sum += dfs (S, 1e9);
		return sum;
	}
	void add (int u, int v, int w)
	{
		e[++ecnt] = { v,w,0,head[u] }; head[u] = ecnt;
		e[++ecnt] = { u,0,0,head[v] }; head[v] = ecnt;
	}
	void clear ()
	{
		for (int i = S; i <= T; i++) head[i] = vis[i] = dis[i] = cur[i] = 0;
		ecnt = S = T = 0;
	}
}MF;
std::vector<int> t[N];

void dfs (int u)
{
	for (int v : t[u])
		if (!col[v]) col[v] = 3 - col[u], dfs (v);
}
int main ()
{
	freopen ("prime.in","r", stdin);
	freopen ("prime.out", "w", stdout);
	init ();
	for (; scanf ("%d%d", &n, &m) != EOF; MF.clear ())
	{
		for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
		std::sort (A + 1, A + 1 + n);
		for (int i = 1, lst = 1; i <= n; i++) if (i == n || A[i] != A[i + 1])
		{
			id[i] = ++tot;
			for (int j = 1; j < i; j++)
				if (A[j] != A[j + 1] && !pvis[A[i] + A[j]])
				{
					vcnt[id[i]]++, vcnt[id[j]]++;
					t[id[i]].push_back (id[j]);
					t[id[j]].push_back (id[i]);
				}
			sum[id[i]] = i - lst + 1; lst = i + 1;
			if (A[i] == 1) vcnt[1]++;
		}
		for (int i = 1; i <= tot; i++) if (!col[i]) col[i] = 1, dfs (i);
		S = 0, T = tot + 1;
		for (int i = 1; i <= tot; i++)
		{
			if (i ^ 1 || A[1] ^ 1)
				if (col[i] == 1)MF.add (S, i, sum[i]);
				else MF.add (i, T, sum[i]);
			for (int v : t[i]) if (v < i)
				if (col[i] == 1) MF.add (i, v, 1e9);
				else MF.add (v, i, 1e9);
		}
		ans = MF.Dinic ();
		int sums = 0;
		for (int i = 1; i <= tot; i++) if (vcnt[i] > 0) sums += sum[i];
		if (A[1] == 1)
		{
			int sum1 = sum[1];
			for (int i = 1; i <= sum[1]; i++)
			{
				int tp = 0;
				MF.add (S, 1, 1), tp += MF.Dinic ();
				if (!tp) break;
				else sum1--, ans += tp;
			}
			ans += sum1 >> 1;
		}
		if (ans >= m) printf ("%d\n", 2 * m);
		else sums = std::min (m - ans, sums - 2 * ans), printf ("%d\n", ans * 2 + sums);
		for (int i = 1; i <= tot; i++) id[i] = sum[i] = col[i] = vcnt[i] = 0, t[i].clear ();
		ans = tot = 0;
	}
}
/*
*/
