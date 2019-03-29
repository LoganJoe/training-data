#include<bits/stdc++.h>
#define ll long long
#define N 100005
int n, m, A[N], Delt[N];
ll ans[N], sum[N];

namespace solve1
{
ll ans[105][105];
void Main ()
{
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) ans[i][j] = sum[j] - sum[i - 1];
	for (; m--;)
	{
		int op, a, b; scanf ("%d%d%d", &op, &a, &b);
		if (op == 1)
		{
			A[a] = b;
			for (int i = a; i <= n; i++) sum[i] = sum[i - 1] + A[i];
			for (int i = 1; i <= n; i++)
				for (int j = i; j <= n; j++) ans[i][j] = std::min (ans[i][j], sum[j] - sum[i - 1]);
		}
		else printf ("%lld\n", ans[a][b]);
	}
}
} // namespace solve1

namespace solve2
{
struct node
{
	int op, x, y, id;
}q[N], tp[N];
class President_Tree
{
#define lc t[x].ls
#define rc t[x].rs
#define mid ((l+r)>>1)
	struct node
	{
		int ls, rs; ll v;
	}t[N * 21];
	void pushup (int x) { t[x].v = t[lc].v + t[rc].v; }
public:
	int root[N], cnt;
	void build (int &x, int l, int r)
	{
		x = ++cnt;
		if (l == r) return (void)(t[x].v = A[l]);
		build (lc, l, mid), build (rc, mid + 1, r);
		pushup (x);
	}
	void insert (int &x, int y, int l, int r, int p, int v)
	{
		t[x = ++cnt] = t[y];
		if (l == r)return(void)(t[x].v = v);
		if (p <= mid) insert (lc, t[y].ls, l, mid, p, v);
		else insert (rc, t[y].rs, mid + 1, r, p, v);
		pushup (x);
	}
	ll query (int x, int l, int r, int ql, int qr)
	{
		if (!x) return 0;
		if (ql <= l && r <= qr) return t[x].v;
		ll res = 0;
		if (ql <= mid) res += query (lc, l, mid, ql, qr);
		if (qr > mid) res += query (rc, mid + 1, r, ql, qr);
		return res;
	}
#undef lc
#undef rc
#undef mid
}T1;
class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	struct node
	{
		int v, tag, id;
	}t[N << 2];
	void update (int x, int v) { t[x].tag += v, t[x].v = std::min (t[x].tag, t[x].v); }
	void pushdown (int x)
	{
		t[lc].v = std::min (t[lc].v, t[lc].tag + t[x].v);
		t[rc].v = std::min (t[rc].v, t[rc].tag + t[x].v);
		t[lc].tag += t[x].tag, t[rc].tag += t[x].tag;
		t[x].tag = t[x].v = 0;
	}
public:
	void modify (int x, int l, int r, int ql, int qr, int v)
	{
		if (ql <= l && r <= qr) return update (x, v);
		pushdown (x);
		if (ql <= mid) modify (lc, l, mid, ql, qr, v);
		if (qr > mid) modify (rc, mid + 1, r, ql, qr, v);
	}
	int query (int x, int l, int r, int p)
	{
		if (l == r) return t[x].v;
		pushdown (x);
		if (p <= mid) return query (lc, l, mid, p);
		else return query (rc, mid + 1, r, p);
	}
	void clear (int x, int l, int r, int p)
	{
		t[x].v = t[x].tag = 0;
		if (l == r) return;
		if (p <= mid) return clear (lc, l, mid, p);
		else return clear (rc, mid + 1, r, p);
	}
#undef lc
#undef rc
#undef mid
}T2;
void solve (int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;
	solve (l, mid), solve (mid + 1, r);
	int top = 0;
	for (int i = l, j = mid + 1; i <= mid || j <= r;)
	{
		if (i <= mid && q[i].x > q[j].x || j > r)
		{
			if (q[i].op == 1)
				T2.modify (1, 1, n, q[i].x, n, q[i].y);
			tp[++top] = q[i++];
		}
		else
		{
			if (q[j].op == 2)
				ans[q[j].id] = std::min (ans[q[j].id], T1.query (T1.root[l - 1], 1, n, q[j].x, q[j].y) + T2.query (1, 1, n, q[j].y));
			tp[++top] = q[j++];
		}
	}
	for (int i = l; i <= mid; i++) if (q[i].op == 1) T2.clear (1, 1, n, q[i].x);
	for (int i = 1; i <= top; i++) q[i + l - 1] = tp[i];
}
void Main ()
{
	T1.build (T1.root[0], 1, n);
	for (int i = 1; i <= m; i++)
	{
		scanf ("%d%d%d", &q[i].op, &q[i].x, &q[i].y), q[i].id = i;
		if (q[i].op == 1)
		{
			T1.insert (T1.root[i], T1.root[i - 1], 1, n, q[i].x, q[i].y);
			q[i].y -= A[q[i].x], A[q[i].x] += q[i].y;
			ans[i] = -1;
		}
		else T1.root[i] = T1.root[i - 1], ans[i] = sum[q[i].y] - sum[q[i].x - 1];
	}
	solve (1, m);
	for (int i = 1; i <= m; i++) if (ans[i] != -1) printf ("%lld\n", ans[i]);
}
} //namespace solve2

int main ()
{
	freopen ("ds.in", "r", stdin);
	freopen ("ds.out", "w", stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf ("%d", &A[i]), sum[i] = sum[i - 1] + A[i];
	if (n <= 100) return solve1::Main (), 0;
	else return solve2::Main (), 0;
}
