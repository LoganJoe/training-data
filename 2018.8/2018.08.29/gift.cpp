#include<bits/stdc++.h>
#define DEBUG 0
#define $ if(DEBUG)
#define dbg1(x) $ std::cerr << #x << "=" << x << " "
#define dbg2(x) $ std::cerr << #x << "=" << x << "\n"
#define dbg3(x) $ for(auto v:x) std::cerr<<v<<" ";std::cerr<<"\n"
#define dbg4(x) $ std::cerr<<__FUNCTION__<<"() L"<<__LINE__<<":->: "#x"="<<(x)<<"\n"
#define N 200005
int n, m, A[N], head[N], cnt = 1, sum;
int dis[N], vis[N], S, T, cur[N];
struct node
{
	int a, b, val;
}B[N];
struct edge
{
	int v, cap, flow, next;
}e[N << 1];
void add (int u, int v, int w)
{
	e[++cnt] = { v,w,0,head[u] }; head[u] = cnt;
	e[++cnt] = { u,w,0,head[v] }; head[v] = cnt;
}
void setmap ()
{
	S = 0, T = n + m + 1;
	for (int i = 1; i <= n; i++) add (S, i, A[i]);
	for (int i = 1; i <= m; i++)
	{
		add (B[i].a, n + i, 1e9);
		add (B[i].b, n + i, 1e9);
		add (n + i, T, B[i].val);
	}
}
void reset_map (int x)
{
	for (int i = 2; i <= cnt; i++)
	{
		e[i].flow = 0;
		if (e[i].v == S || e[i ^ 1].v == S)
			e[i].cap = A[e[i ^ 1].v | e[i].v] * x;
	}
}
bool bfs ()
{
	for (int i = S; i <= T; i++) vis[i] = dis[i] = 0, cur[i] = head[i];
	vis[S] = 1; std::queue<int>q; q.push (S);
	while (!q.empty ())
	{
		int u = q.front (); q.pop ();
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v;
			if (!vis[v] && e[i].cap > e[i].flow)
			{
				vis[v] = 1;
				dis[v] = dis[u] + 1;
				if (v == T) return 1;
				q.push (v);
			}
		}
	}
	return 0;
}
int dfs (int u, int res)
{
	if (u == T || res == 0) return res;
	int flow = 0, f;
	for (int i = cur[u]; i; i = e[i].next)
	{
		cur[u] = i; int v = e[i].v;
		if (dis[v] == dis[u] + 1 && (f = dfs (v, std::min (res, e[i].cap - e[i].flow))) > 0)
		{
			e[i].flow += f;
			e[i ^ 1].flow -= f;
			flow += f;res -= f;
			if (!res) break;
		}
	}
	return flow;
}
int dinic ()
{
	int sum = 0; while (bfs ()) sum += dfs (S, 1e9);
	return sum;
}
int main ()
{
	freopen ("gift.in", "r", stdin);
	freopen ("gift.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 1; i <= m; i++)
		scanf ("%d%d%d", &B[i].a, &B[i].b, &B[i].val), sum += B[i].val;
	setmap ();
	int l = 0, r = 1000;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		reset_map (mid);
		if (sum - dinic () > 0) l = mid + 1;
		else r = mid;
	}
	printf ("%d\n", l);
}
