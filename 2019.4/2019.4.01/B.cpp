#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, head[N], ecnt;
struct edge
{
	int v, w, next;
}e[N << 1];
ll f[N], Size[N], sum[N], t[N];
void add (int u, int v, int w)
{
	e[++ecnt] = { v,w,head[u] }; head[u] = ecnt;
}
struct node
{
	ll v, Size;
	friend bool operator <(node t1, node t2)
	{
		return t1.v * t2.Size < t2.v * t1.Size;
	}
};
void dfs (int u, int fa)
{
	Size[u] = 1;
	std::vector<node> S;
	for (int i = head[u]; i; i = e[i].next) if (e[i].v^fa)
	{
		dfs (e[i].v, u);
		f[u] += f[e[i].v] + Size[e[i].v] * e[i].w;
		t[u] += t[e[i].v] + e[i].w, Size[u] += Size[e[i].v];
		S.push_back ({ (t[e[i].v] + e[i].w) * 2, Size[e[i].v] });
	}
	std::sort (S.begin (), S.end ()); sum[S.size ()] = 0;
	for (int i = S.size () - 1; ~i; i--) sum[i] = sum[i + 1] + S[i].Size;
	for (int i = 0; i < S.size (); i++)f[u] += sum[i + 1] * S[i].v;
}
int main ()
{
	freopen ("tree.in", "r", stdin);
	freopen ("tree.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1, u, v, w; i < n; i++)
		scanf ("%d%d%d", &u, &v, &w), add (u, v, w), add (v, u, w);
	dfs (1, 0);
	printf ("%.8lf\n", 1. * f[1] / (n - 1));
}
