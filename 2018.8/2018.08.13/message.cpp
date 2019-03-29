#include<bits/stdc++.h>
#define N 200005

std::vector<int>e[N];
int n, Q, fa[N], root, ans[N][3];
int deep[N], pos[N], top[N], son[N], Size[N], tim;

struct node
{
	int opt, a, b, c, id, t;
	friend bool operator <(node t1, node t2) { return t1.t < t2.t || t1.t == t2.t && t1.opt > t2.opt; }
}A[N];
void dfs1 (int u)
{
	for (auto v : e[u])
	{
		deep[v] = deep[u] + 1;
		dfs1 (v); Size[u] += Size[v];
		if (!son[u] || Size[son[u]] < Size[v]) son[u] = v;
	}
}
void dfs2 (int u, int Top)
{
	pos[u] = ++tim, top[u] = Top;
	if (son[u]) dfs2 (son[u], Top);
	for (auto v : e[u]) if (v != son[u]) dfs2 (v, v);
}
class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	int t[N << 2];
	void pushup (int x) { t[x] = t[lc] + t[rc]; }
public:
	void insert (int x, int l, int r, int p)
	{
		if (l == r) return (void)(t[x] = 1);
		if (p <= mid) insert (lc, l, mid, p);
		else insert (rc, mid + 1, r, p);
		pushup (x);
	}
	int query (int x, int l, int r, int ql,int qr)
	{
		if (ql <= l && r <= qr) return t[x];
		int res = 0;
		if (ql <= mid) res += query (lc, l, mid, ql, qr);
		if (qr > mid) res += query (rc, mid + 1, r, ql, qr);
		return res;
	}
}T;
void ask (int x, int y, int id)
{
	int res = 0, tmpx = x, tmpy = y;
	while (top[x] != top[y])
	{
		if (deep[top[x]] < deep[top[y]]) std::swap (x, y);
		res += T.query (1, 1, n, pos[top[x]], pos[x]);
		x = fa[top[x]];
	}
	if (deep[x] > deep[y]) std::swap (x, y);
	res += T.query (1, 1, n, pos[x], pos[y]);
	ans[id][0] = 1, ans[id][1] = deep[tmpx] + deep[tmpy] - 2 * deep[x] + 1; ans[id][2] = res;
}
int main ()
{
	freopen ("message.in", "r", stdin);
	freopen ("message.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf ("%d", &fa[i]);
		if (fa[i] == 0) root = i;
		else e[fa[i]].push_back (i);
	}
	dfs1 (root), dfs2 (root, root);
	scanf ("%d", &Q);
	for(int i=1;i<=Q;i++)
	{
		scanf ("%d", &A[i].opt);
		if (A[i].opt == 1)
		{
			scanf ("%d%d%d", &A[i].a, &A[i].b, &A[i].c);
			A[i].t = i - A[i].c - 1;
		}
		else scanf ("%d", &A[i].a), A[i].t = i;
		A[i].id = i;
	}
	std::sort (A + 1, A + 1 + Q);
	for (int i = 1; i <= Q; i++)
	{
		if (A[i].opt == 1) ask (A[i].a, A[i].b, A[i].id);
		else T.insert (1, 1, n, pos[A[i].a]);
	}
	for (int i = 1; i <= Q; i++)if (ans[i][0]) printf ("%d %d\n", ans[i][1], ans[i][2]);
}
/*
8
0 1 1 2 2 3 3 7
6
1 4 7 0
2 1
2 4
2 7
1 4 7 1
1 4 8 3
*/
