#include<bits/stdc++.h>
#define ll long long
#define N 100005
int n, m, k, val[N], S[N], tot, cnt[N], bel[N]; ll ans;
int head[N << 2], ecnt;
struct edge { int v, w, next; }e[N * 10];
void add (int u, int v, int w) { e[++ecnt] = { v,w,head[u] }; head[u] = ecnt; }
struct node
{
	int x; ll dis;
	friend bool operator <(node t1, node t2) { return t1.dis > t2.dis; }
};
std::priority_queue<node>q;
ll dis[N];
void dijkstraHeap (int st)
{
	for (int i = 1; i <= tot + m; i++) dis[i] = 1e17;
	dis[st] = 0, q.push ({ st,0 });
	while (!q.empty ())
	{
		node u = q.top (); q.pop ();
		if (dis[u.x] != u.dis) continue;
		for (int i = head[u.x]; i; i = e[i].next)
			if (dis[e[i].v] > dis[u.x] + e[i].w)
				dis[e[i].v] = dis[u.x] + e[i].w, q.push ({ e[i].v,dis[e[i].v] });
	}
}
int main ()
{
	freopen("dist.in","r",stdin);
	freopen("dist.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf ("%d %d", &val[i], &k);
		for (int j = 1, x; j <= k; j++) scanf ("%d", &x), S[x] |= 1 << i - 1;
	}
	int totS = (1 << m) - 1;
	for (int i = 1; i <= n; i++) cnt[S[i]]++;
	for (int i = 0; i <= totS; i++) if (cnt[i]) bel[++tot] = i;
	for (int s = 1; s <= tot; s++)
		for (int i = 1; i <= m; i++)
			if (bel[s] >> (i - 1) & 1) add (s, tot + i, val[i]), add (tot + i, s, 0);
	for (int i = 1; i <= tot; i++)
	{
		dijkstraHeap (i);int Min = 1e9;
		for (int j = 1; j <= tot; j++) 
			if (i^j) ans += 1ll * cnt[bel[i]] * cnt[bel[j]] * dis[j];
		for (int j = 1; j <= m; j++) 
			if (bel[i] >> (j - 1) & 1) Min = std::min (Min, val[j]);
		ans += 1ll * cnt[bel[i]] * (cnt[bel[i]] - 1) * Min;
	}
	std::cout << (ans >> 1ll) << "\n";
}
