#include<bits/stdc++.h>
#define N 500005
int n, m, q, fa[N][20], deep[N], pos[N], Size[N], tim;
std::vector<int> e[N];
void dfs (int u, int fath)
{
	fa[u][0] = fath, deep[u] = deep[fath] + 1;
	pos[u] = ++tim, Size[u] = 1;
	for (int j = 0, v; j < e[u].size (); j++)
		if ((v = e[u][j]) ^ fath) dfs (v, u), Size[u] += Size[v];
}
void process ()
{
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
}
int getlca (int u, int v)
{
	if (deep[u] < deep[v]) std::swap (u, v);
	for (int i = 19; ~i; i--) if (deep[fa[u][i]] >= deep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = 19; ~i; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
int dist (int u, int v) { return deep[u] + deep[v] - 2 * deep[getlca (u, v)]; }
bool cmp (int t1, int t2)
{
	return pos[t1] < pos[t2];
}
class VirtualTree
{
	struct edge
	{
		int v, next;
	}e[N << 1];
	int head[N], ecnt, A[N], bel[N], ans[N], Ind, sta[N], top, id[N], tp[N], qort[N];
	void add (int u, int v)
	{
		e[++ecnt] = { v,head[u] }; head[u] = ecnt;
	}
	void dfs1 (int u)
	{
		id[++Ind] = u, tp[u] = Size[u];
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v;
			dfs1 (v); if (!bel[v]) continue;
			int Dist1 = dist (bel[v], u), Dist2 = dist (bel[u], u);
			if (Dist1 == Dist2 && qort[bel[v]] < qort[bel[u]] || Dist1 < Dist2 || !bel[u]) bel[u] = bel[v];
		}
	}
	void dfs2 (int u)
	{
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v;
			int Dist1 = dist (bel[u], v), Dist2 = dist (bel[e[i].v], v);
			if (Dist1 == Dist2 && qort[bel[v]] > qort[bel[u]] || Dist1 < Dist2 || !bel[v]) bel[v] = bel[u];
			dfs2 (e[i].v);
		}
	}
	void solve (int a, int b)
	{
		int x = b;
		for (int i = 19; ~i; i--) if (deep[fa[x][i]] > deep[a]) x = fa[x][i];
		tp[a] -= Size[x];
		if (bel[a] == bel[b]) return (void)(ans[bel[a]] += Size[x] - Size[b]);
		int mid = b;
		for (int i = 19; ~i; i--)
		{
			int p = fa[mid][i]; if (deep[p] <= deep[a]) continue;
			int Dist1 = dist (bel[a], p), Dist2 = dist (bel[b], p);
			if (Dist1 > Dist2 || Dist1 == Dist2 && qort[bel[b]] < qort[bel[a]]) mid = p;
		}
		ans[bel[a]] += Size[x] - Size[mid];
		ans[bel[b]] += Size[mid] - Size[b];
	}
public:
	void query ()
	{
		scanf ("%d", &m);
		for (int i = 1; i <= m; i++) scanf ("%d", &A[i]), bel[A[i]] = A[i], qort[A[i]] = i;
		int touli = A[1];
		std::sort (A + 1, A + 1 + m, cmp);
		if (bel[1] ^ 1) sta[++top] = 1;
		for (int i = 1; i <= m; i++)
		{
			int c = 0;
			while (top)
			{
				c = getlca (sta[top], A[i]);
				if (top > 1 && deep[c] < deep[sta[top - 1]]) add (sta[top - 1], sta[top]), top--;
				else if (deep[c] < deep[sta[top]]) { add (c, sta[top]); top--; break; }
				else break;
			}
			if (sta[top] != c) sta[++top] = c;
			sta[++top] = A[i];
		}
		for (; top > 1; top--) add (sta[top - 1], sta[top]);
		dfs1 (1), dfs2 (1);
		for (int i = 1; i <= Ind; i++)
			for (int j = head[id[i]]; j; j = e[j].next) solve (id[i], e[j].v);
		for (int i = 1; i <= Ind; i++) ans[bel[id[i]]] += tp[id[i]];
		printf ("%d\n", ans[touli]);
		for (int i = 1; i <= Ind; i++)
			ans[id[i]] = bel[id[i]] = head[id[i]] = tp[id[i]] = qort[id[i]] = 0;
		top = Ind = ecnt = 0;
	}
}T;
int main ()
{
	freopen ("civilization.in", "r", stdin);
	freopen ("civilization.ans", "w", stdout);
	scanf ("%d%d", &n, &q);
	for (int i = 1, u, v; i < n; i++)
		scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
	dfs (1, 0); process ();
	while (q--) T.query ();
}
/*
6 4 
1 2
1 3
2 4
3 5
3 6
2 1 3
3 1 4 5
3 4 5 6
3 1 2 3
*/
