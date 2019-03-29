#include<bits/stdc++.h>
#define N 80005
#define db double
int n, Q;
int head[N], ecnt;
struct edge { int v, next; }e[N << 1];
void add (int u, int v) { e[++ecnt] = { v,head[u] }; head[u] = ecnt; }
int tim, pos[N], deep[N], Rnk[N], top[N], son[N], Size[N], fa[N];
double f[50];
void dfs1 (int u, int fath)
{
	Size[u] = 1, deep[u] = deep[fath] + 1; fa[u] = fath;
	for (int i = head[u]; i; i = e[i].next)
	{
		int v = e[i].v; if (v == fath) continue;
		dfs1 (v, u), Size[u] += Size[v];
		if (!son[u] || Size[son[u]] < Size[v]) son[u] = v;
	}
}
void dfs2 (int u, int Top)
{
	Rnk[pos[u] = ++tim] = u; top[u] = Top;
	if (son[u]) dfs2 (son[u], Top);
	for (int i = head[u]; i; i = e[i].next)
		if (e[i].v != fa[u] && e[i].v != son[u]) dfs2 (e[i].v, e[i].v);
}
#define M 12
struct node
{
	int v[M + 2];
	void clear () { for (int i = 1; i <= M + 1; i++) v[i] = 0; }
	friend node operator +(node t1, node t2)
	{
		node res; res.clear ();
		for (int i = 1; i <= M; i++) res.v[i] = t1.v[i] + t2.v[i];
		return res;
	}
	friend node operator +(node a, int  x)
	{
		node res; res.clear ();
		for (int i = M; i; i--)
			if (i + x > M) res.v[M + 1] += a.v[i];
			else res.v[i + x] += a.v[i];
		return res;
	}
	friend node operator *(node a, int  x)
	{
		node res; res.clear ();
		for (int i = M; i; i--)
			if (i * x > M) res.v[M + 1] += a.v[i];
			else res.v[i * x] += a.v[i];
		return res;
	}
}E;
class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	node t[N << 2]; int tag1[N << 1], tag2[N << 1];
	//tag1 + tag2 *
	void pushup (int x) { t[x] = t[lc] + t[rc]; }
	
	void pushdown (int x)
	{
		if (tag2[x] != 1)
		{
			
			tag2[x] = std::min (tag2[x], M);
			tag2[lc] *= tag2[x], tag2[rc] *= tag2[x];
			tag1[lc] *= tag2[x], tag1[rc] *= tag2[x];
			t[lc] = t[lc] * tag2[x], t[rc] = t[rc] * tag2[x];
			tag2[x] = 1;
		}
		if (tag1[x])
		{
			tag1[x] = std::min (tag1[x], M);
			tag1[lc] += tag1[x], tag1[rc] += tag1[x];
			t[lc] = t[lc] + tag1[x], t[rc] = t[rc] + tag1[x];
			tag1[x] = 0;
		}
	}
public:
	void build (int x, int l, int r)
	{
		tag2[x] = 1;
		if (l == r) return (void)(t[x].v[1] = 1);
		build (lc, l, mid), build (rc, mid + 1, r);
		pushup (x);
	}
	node query (int x, int l, int r,int ql,int qr)
	{
		if (ql <= l && r <= qr) return t[x];
		pushdown (x); node res = E;
		if (ql <= mid) res = res + query (lc, l, mid, ql, qr);
		if (qr > mid) res = res + query (rc, mid + 1, r, ql, qr);
		return res;
	}
	void plus (int x, int l, int r, int ql, int qr,int v)
	{
		if (ql <= l && r <= qr)
		{
			if (l != r) pushdown (x);
			tag1[x] += v, t[x] = t[x] + v;
			return;
		}
		pushdown (x);
		if (ql <= mid) plus (lc, l, mid, ql, qr, v);
		if (qr > mid) plus (rc, mid + 1, r, ql, qr, v);
		pushup (x);
	}
	void multi (int x, int l, int r, int ql, int qr, int v)
	{
		if (ql <= l && r <= qr)
		{
			if (l != r) pushdown (x);
			tag1[x] *= v, tag2[x] *= v, t[x] = t[x] * v;
			return;
		}
		pushdown (x);
		if (ql <= mid) multi (lc, l, mid, ql, qr, v);
		if (qr > mid) multi (rc, mid + 1, r, ql, qr, v);
		pushup (x);
	}
}T;
db change (int x, int y, int op, int v)
{
	if (v >= M) v = M;
	node res = E;
	while (top[x] != top[y])
	{
		if (deep[top[x]] < deep[top[y]]) std::swap (x, y);
		if (op == 1) T.plus (1, 1, n, pos[top[x]], pos[x], v);
		if (op == 2) T.multi (1, 1, n, pos[top[x]], pos[x], v);
		if (op == 3) res = res + T.query (1, 1, n, pos[top[x]], pos[x]);
		x = fa[top[x]];
	}
	if (deep[x] > deep[y]) std::swap (x, y);
	if (op == 1) T.plus (1, 1, n, pos[x], pos[y], v);
	if (op == 2) T.multi (1, 1, n, pos[x], pos[y], v);
	if (op == 3) res = res + T.query (1, 1, n, pos[x], pos[y]);
	if (op == 3)
	{
		db re = 0;
		for (int i = 1; i <= M + 1; i++) re += f[i] * res.v[i];
		return re;
	}
}
int main ()
{
	freopen("yuyuko.in","r",stdin);
	freopen("yuyuko.out","w",stdout);
	f[1] = 1;
	for (int i = 2; i < 30; i++) f[i] = f[i - 1] * (i - 1) / i + f[i - 2] / i;
	for (int i = 1; i < 30; i++)  f[i] = 1 - f[i];
	scanf ("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf ("%d%d", &u, &v), add (u, v), add (v, u);
	dfs1 (1, 0), dfs2 (1, 1); T.build (1, 1, n);
	scanf ("%d", &Q);
	while (Q--)
	{
		char ch[10]; int x, y, v;
		scanf ("%s%d%d", ch, &x, &y);
		if (ch[0] != 'Q') scanf ("%d", &v);
		if (ch[0] == 'A') change (x, y, 1, v);
		if (ch[0] == 'M') change (x, y, 2, v);
		if (ch[0] == 'Q') printf ("%.1lf\n", change (x, y, 3, 0));
	}
}

