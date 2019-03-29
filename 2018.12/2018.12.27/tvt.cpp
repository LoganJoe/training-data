#include<bits/stdc++.h>
#define N 100005
#define ll long long
#define fr first
#define se second
int n, m, head[N], ecnt, fa[N][20], val[N][20], deep[N], in[N], out[N], dfn;
ll dist[N];
std::pair<int, int> nosol = { -1,-1 };
struct edge
{
	int v, w, next;
}e[N << 1];
void add (int u, int v, int w) { e[++ecnt] = { v,w,head[u] }; head[u] = ecnt; }
void dfs (int u, int fath)
{
	fa[u][0] = fath, deep[u] = deep[fath] + 1, in[u] = ++dfn;
	for (int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].v; if (v == fath) continue;
		dist[v] = dist[u] + e[i].w, val[v][0] = e[i].w;
		dfs (v, u);
	} out[u] = dfn;
}
void process ()
{
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++) 
			fa[i][j] = fa[fa[i][j - 1]][j - 1],
			val[i][j] = std::max (val[i][j - 1], val[fa[i][j - 1]][j - 1]);
}
int getlca (int u, int v)
{
	if (deep[u] < deep[v]) std::swap (u, v);
	for (int i = 19; ~i; i--) if (deep[fa[u][i]] >= deep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = 19; ~i; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
int inchain (int a, int b)
{
	return in[a] <= in[b] && out[b] <= out[a];
}
int getdist (int u, int v)
{
	return dist[u] + dist[v] - 2 * dist[getlca (u, v)];
}
std::pair<int, int> getcomm (int a, int b, int c, int d) //chain a->b,c->d
{
	std::pair<int, int> res = { d,c };
	for (int i = 19; ~i; i--)
	{
		if (!inchain (fa[res.se][i], a)) res.se = fa[res.se][i];
	}
	if (!inchain (res.se, a)) res.se = fa[res.se][0];
	return inchain (res.se, a) ? res : nosol;
}
std::pair<int, int> commedge (int a, int b, int c, int d)
{
	if (inchain (b, d) && inchain (d, a)) return getcomm (a, b, c, d);
	if (inchain (d, b) && inchain (b, c)) return getcomm (c, d, a, b);
	return nosol;
}
int main ()
{
	scanf ("%d%d", &n, &m);
	for (int i = 1, u, v, w; i < n; i++) 
		scanf ("%d%d%d", &u, &v, &w), add (u, v, w), add (v, u, w);
	dfs (1, 0); process (); in[0] = 1, out[0] = n;
	while (m--)
	{
		int u1, v1, t1, u2, v2, t2, c1, c2;
		scanf ("%d%d%d%d%d%d", &u1, &v1, &t1, &u2, &v2, &t2);
		c1 = getlca (u1, v1), c2 = getlca (u2, v2);
		bool res = 0; std::pair<int, int> E;
		ll D;int Max = 0;
		//part1::u1, lca1, u2, lca2;
		E = commedge (u1, c1, u2, c2);
		if (E.fr != -1 && E.se != -1)
		{
			ll distf1 = dist[u1] - dist[E.se] + t1, distf2 = dist[u1] - dist[E.fr] + t1;
			ll dists1 = dist[u2] - dist[E.se] + t2, dists2 = dist[u2] - dist[E.fr] + t2;
			if (distf2 <= dists1 || dists2 <= distf1) goto END1;
			Max = 0;
			for (int i = 19; ~i; i--)
				if (deep[fa[E.se][i]] >= deep[E.fr]) 
					Max = std::max (Max, val[E.se][i]), E.se = fa[E.se][i];
			if (Max >= abs (distf1 - dists1)) { res = 1; goto OUTPUT; };
		END1:;
		}
		//part2::v1, lca1, u2, lca2;
		E = commedge (v1, c1, u2, c2);
		if (E.fr != -1 && E.se != -1)
		{
			ll distf1 = dist[u1] + dist[E.fr] - 2 * dist[c1] + t1, distf2 = dist[u1] + dist[E.se] - 2 * dist[c2] + t1;
			ll dists1 = dist[u2] - dist[E.se] + t2, dists2 = dist[u2] - dist[E.fr] + t2;
			if (distf2 <= dists1 || dists2 <= distf1) goto END2;
			if (dist[E.se] - dist[E.fr] - abs (distf1 - dists1) < 0) goto END2;
			if (dist[E.se] - dist[E.fr] - abs (distf1 - dists1) % 2 == 1) { res = 1; goto OUTPUT; };
			D = (dist[E.se] - dist[E.fr] - abs (distf1 - dists1)) >> 1;
			if (dists1 < distf1) D += abs (distf1 - dists1);//diff
			for (int i = 19; ~i; i--)
				if (dist[E.se] - dist[fa[E.se][i]] <= D) 
					D -= dist[E.se] - dist[fa[E.se][i]], E.se = fa[E.se][i];
			if(D) { res = 1; goto OUTPUT; };
		END2:;
		}
		
		//part3::u1, lca1, v2, lca2;
		E = commedge (u1, c1, v2, c2);
		if (E.fr != -1 && E.se != -1)
		{
			ll distf1 = dist[u1] - dist[E.se] + t1, distf2 = dist[u1] - dist[E.fr] + t1;
			ll dists1 = dist[u2] + dist[E.fr] - 2 * dist[c2] + t2, dists2 = dist[u2] + dist[E.se] - 2 * dist[c2] + t2;
			if (distf2 <= dists1 || dists2 <= distf1) goto END3;
			if (dist[E.se] - dist[E.fr] - abs (distf1 - dists1) < 0) goto END3;
			if (dist[E.se] - dist[E.fr] - abs (distf1 - dists1) % 2 == 1) { res = 1; goto OUTPUT; };
			D = (dist[E.se] - dist[E.fr] - abs (distf1 - dists1)) >> 1;
			if (distf1 < dists1) D += abs (distf1 - dists1);//diff
			for (int i = 19; ~i; i--)
				if (dist[E.se] - dist[fa[E.se][i]] <= D)
					D -= dist[E.se] - dist[fa[E.se][i]], E.se = fa[E.se][i];
			if (D) { res = 1; goto OUTPUT; };
		END3:;
		}
		//part3::v1, lca1, v2, lca2;
		E = commedge (v1, c1, v2, c2);
		if (E.fr != -1 && E.se != -1)
		{
			ll distf1 = dist[u1] + dist[E.fr] - 2 * dist[c1] + t1, distf2 = dist[u1] + dist[E.se] - 2 * dist[c2] + t1;
			ll dists1 = dist[u2] + dist[E.fr] - 2 * dist[c2] + t2, dists2 = dist[u2] + dist[E.se] - 2 * dist[c2] + t2;
			if (distf2 <= dists1 || dists2 <= distf1) goto END4;
			Max = 0;
			for (int i = 19; ~i; i--)
				if (deep[fa[E.se][i]] >= deep[E.fr])
					Max = std::max (Max, val[E.se][i]), E.se = fa[E.se][i];
			if (Max >= abs (distf1 - dists1)) { res = 1; goto OUTPUT; };
		END4:;
		}
	OUTPUT:
		puts (res ? "YES" : "NO");
	}
}
