#include <bits/stdc++.h>
#define N 100005
int n, A[N], b[N], tot;
std::vector<int> e[N];
namespace solve1
{
int f[5005][5005], g[5005], Max[5005];
void dfs(int u, int fa)
{
	for (int v : e[u]) if (v ^ fa)
	{
		dfs(v, u);
		for (int i = 1; i <= tot; i++) 
			Max[i] = std::max (Max[i - 1], f[v][i]), g[i] = std::max (g[i], f[u][i] + Max[i]);
		for (int i = 1; i <= tot; i++) 
			Max[i] = std::max (Max[i - 1], f[u][i]), g[i] = std::max (g[i], f[v][i] + Max[i]);
		for (int i = 1; i <= tot; i++) 
			f[u][i] = g[i], g[i] = 0;
	}
	f[u][A[u]]++;
}
void Main()
{
	dfs (1, 0);
	for (int i = 1; i <= n; i++)
	{
		int ans = 0;
		for (int j = 1; j <= A[i]; j++) ans = std::max (ans, f[i][j]);
		printf ("%d ", ans);
	}
}
} // namespace solve1
namespace solve2
{
int ans[N];
class Segment_Tree
{
#define lc t[x].ls
#define rc t[x].rs
#define mid ((l+r)>>1)
	struct tree
	{
		int ls, rs, tag, v;
	} t[N * 20];
	void pushup (int x)
	{
		t[x].v = std::max (t[lc].v, t[rc].v);
	}
	void update (int x, int v)
	{
		t[x].v += v, t[x].tag += v;
	}
	void pushdown (int x)
	{
		if(!t[x].tag) return ;
		if(lc) update (lc, t[x].tag);
		if(rc) update (rc, t[x].tag);
		t[x].tag = 0;
	}
public:
	int root[N], cnt;
	void insert (int &x, int l, int r, int p, int v)
	{
		if (!x) x = ++cnt;
		if (l == r) return (void)(t[x].v = v);
		pushdown (x);
		if (p <= mid) insert (lc, l, mid, p, v);
		else insert (rc, mid + 1, r, p, v);
		pushup (x);
	}
	int query (int x, int l, int r, int ql, int qr)
	{
		if (!x) return 0;
		if (ql <= l && r <= qr) return t[x].v;
		pushdown (x); int res = 0;
		if (ql <= mid) res = std::max (res, query (lc, l, mid, ql, qr));
		if (qr > mid) res = std::max (res, query(rc, mid + 1, r, ql, qr));
		return res;
	}
	void merge (int &x, int y, int l, int r, int v1, int v2)
	{
		if (!x && !y) return ;
		if (!x) return update (x = y, v1);
		if (!y) return update (x, v2);
		if (l == r)
		{
			v1 = std::max (v1, t[x].v), v2 = std::max (v2, t[y].v);
			t[x].v = std::max(t[x].v + v2, t[y].v + v1);
			return ;
		}
		pushdown (x), pushdown (y);
		merge (rc, t[y].rs, mid + 1, r, std::max (v1, t[t[x].ls].v), std::max(v2, t[t[y].ls].v));
		merge (lc, t[y].ls, l, mid, v1, v2);
		pushup (x);
	}
}T;
void dfs (int u, int fa)
{
	for (int v : e[u]) if(v ^ fa)
		dfs (v, u), T.merge (T.root[u], T.root[v], 1, tot, 0, 0);
	ans[u] = T.query (T.root[u], 1, tot, 1, A[u]) + 1;
	T.insert (T.root[u], 1, tot, A[u], ans[u]);
}
void Main()
{
	dfs (1, 0);
	for (int i = 1; i <= n; i++)
		printf ("%d ", ans[i]);
	puts("");
}
} // namespace solve2
int main()
{
	freopen ("treap.in" , "r", stdin);
	freopen ("treap.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), b[i] = A[i];
	for (int i = 1, u, v; i < n; i++) 
		scanf ("%d%d", &u, &v), u++, v++, e[u].push_back(v), e[v].push_back(u);
	std::sort (b + 1, b + 1 + n);
	tot = std::unique (b + 1, b + 1 + n) - b - 1;
	for (int i = 1; i <= n; i++) 
		A[i] = std::lower_bound (b + 1, b + 1 + tot, A[i]) - b;
//	if (n <= 5000) return solve1::Main(), 0;
//	else return solve2::Main(), 0;
	return solve2::Main(), 0;
}
/*
14 
5 4 3 6 2 3 4 0 1 7 9 8 6 2 
0 1 0 2 0 3 1 4 3 5 3 6 3 7 4 8 4 9 4 10 6 11 6 12 11 13 
*/
