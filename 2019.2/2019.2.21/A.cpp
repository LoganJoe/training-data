#include<bits/stdc++.h>
#define ll long long
#define N 100005
int n, K, head[N], ecnt, A[N], mark[N], size[N], in[N], out[N], Rnk[N], tim, Maxsz[N], rt, pre[N];
ll dist[N], Sum, ans;
struct edge
{
	int v, w, next;
}e[N << 1];
void add (int u, int v, int w)
{
	e[++ecnt] = { v,w,head[u] }; head[u] = ecnt;
}
void dfs1 (int u, int fa)
{
	Rnk[in[u] = ++tim] = u;
	if (mark[u]) Sum += dist[u];
	size[u] = mark[u];
	for (int i = head[u]; i; i = e[i].next) if (e[i].v != fa)
	{

		dist[e[i].v] = dist[u] + e[i].w; dfs1 (e[i].v, u);
		size[u] += size[e[i].v];
		Maxsz[u] = std::max (Maxsz[u], size[e[i].v]);
	}
	Maxsz[u] = std::max (Maxsz[u], K - size[u]);
	out[u] = tim;
}
void dfs2 (int u, int fa)
{
	if (2 * Maxsz[u] <= K && Sum > ans) ans = Sum, rt = u;
	for (int i = head[u]; i; i = e[i].next) if (e[i].v != fa)
	{
		int tot = pre[out[e[i].v]] - pre[in[e[i].v] - 1];
		Sum += 1ll * (K - (tot << 1))*e[i].w;
		dfs2 (e[i].v, u);
		Sum += 1ll * (K - (tot << 1))*e[i].w;
	}
}
std::vector<int>t[N];
int tot;
void dfs3 (int u, int fa,int id)
{
	if (mark[u]) t[id].push_back (u);
	for (int i = head[u]; i; i = e[i].next) 
		if (e[i].v != fa) dfs3 (e[i].v, u,id);
}
int main ()
{
	freopen ("pair.in", "r", stdin);
	freopen ("pair.out", "w", stdout);
	scanf ("%d%d", &n, &K);
	for (int i = 1, u, v, w; i < n; i++)
		scanf ("%d%d%d", &u, &v, &w), add (u, v, w), add (v, u, w);
	for (int i = 1; i <= K; i++) scanf ("%d", &A[i]), mark[A[i]] = 1;
	dfs1 (1, 0);
	for (int i = 1; i <= K; i++) pre[in[A[i]]]++;
	for (int i = 1; i <= n; i++) pre[i] += pre[i - 1];
	dfs2 (1, 0);
	if (mark[rt]) t[++tot].push_back (rt);
	for (int i = head[rt]; i; i = e[i].next) dfs3 (e[i].v, rt, ++tot);
	std::priority_queue<std::pair<int, int> >q;
	for (int i = 1; i <= tot; i++) q.push ({ t[i].size (), i });
	for (int i = 1; i <= K >> 1; i++)
	{
		std::pair<int, int> a = q.top (); q.pop ();
		std::pair<int, int> b = q.top (); q.pop ();
		printf ("%d %d\n", t[a.second][--a.first], t[b.second][--b.first]);
		q.push (a), q.push (b);
	}
}

