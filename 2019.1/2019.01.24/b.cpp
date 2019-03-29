#include<bits/stdc++.h>
#define N 100005
int n, Q, head[N], ecnt = 1, lastans, ans1, ans2, x, w, s, t;
struct edge
{
	int v, w, next;
}e[N << 1];
void add (int u, int v, int w)
{
	e[++ecnt] = { v,w,head[u] }; head[u] = ecnt;
}
void dfs (int u, int fa, int mark)
{
	if (u == t) ans2 = 1; ans1++;
	for (int i = head[u]; i; i = e[i].next)
	{
		if (e[i].v == fa) continue;
		if (!mark || e[i].w < 3) dfs (e[i].v, u, mark | (e[i].w > 1));
	}
}
int main ()
{
	scanf ("%d%d", &n, &Q);
	for (int i = 1; i < n; i++)
	{
		int u, v, w; scanf ("%d%d%d", &u, &v, &w);
		add (u, v, w), add (v, u, w);
	}
	while (Q--)
	{
		scanf ("%d%d%d%d", &x, &w, &s, &t);
		x ^= lastans, w ^= lastans, s ^= lastans, t ^= lastans;
		e[x << 1].w = e[x << 1 | 1].w = w;
		ans1 = ans2 = 0;
		dfs (s, 0, 0);
		printf ("%d %d\n", ans1, ans2), lastans = ans1;
	}
}
