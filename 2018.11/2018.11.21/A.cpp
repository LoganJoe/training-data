#include<bits/stdc++.h>
#define N 100005
#define mod 998244353
int n, m, p[N], b[N << 2], tot, ans, po[N];
struct node
{
	int l, r;
	friend bool operator <(node t1, node t2) { return t1.l < t2.l; }
}A[N];
int mul (int x) { return x >= mod ? x - mod : x; }
class President_Tree
{
#define lc t[x].ls
#define rc t[x].rs
#define mid ((l+r)>>1)
	struct tree { int ls, rs, v; }t[N * 60];
public:
	int tcnt, root[N];
	void insert (int &x, int y, int l, int r, int p)
	{
		x = ++tcnt;
		t[x] = t[y];
		if (l == r) return (void)(t[x].v = t[y].v + 1);
		if (p <= mid) insert (t[x].ls, t[y].ls, l, mid, p);
		else insert (t[x].rs, t[y].rs, mid + 1, r, p);
		t[x].v = t[lc].v + t[rc].v;
	}
	int query (int x, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return t[x].v;
		int res = 0;
		if (ql <= mid) res += query (lc, l, mid, ql, qr);
		if (qr > mid) res += query (rc, mid + 1, r, ql, qr);
		return res;
	}
#undef mid
}T;
int depart (int x)
{
	int l = 0, r = n, mid, res = 0;
	for (; l <= r;) mid = (l + r) >> 1, A[mid].l <= x ? l = mid + 1, res = mid : r = mid - 1;
	return res;
}
int main ()
{
	freopen ("a.in", "r", stdin);
	freopen ("a.out", "w", stdout);
	std::ios::sync_with_stdio (0);
	std::cin >> n >> m;
	po[0] = 1; for (int i = 1; i <= n; i++) po[i] = mul (po[i - 1] << 1);
	for (int i = 1; i <= n; i++)
		std::cin >> A[i].l >> A[i].r, b[++tot] = A[i].l, b[++tot] = A[i].r;
	for (int i = 1; i <= m; i++) std::cin >> p[i], b[++tot] = p[i];
	std::sort (b + 1, b + 1 + tot);
	tot = std::unique (b + 1, b + 1 + tot) - b - 1;
	std::sort (A + 1, A + 1 + n);
	std::sort (p + 1, p + 1 + m);
	for (int i = 1; i <= n; i++)
		A[i].l = std::lower_bound (b + 1, b + 1 + tot, A[i].l) - b,
		A[i].r = std::lower_bound (b + 1, b + 1 + tot, A[i].r) - b;
	for (int i = 1; i <= m; i++)
		p[i] = std::lower_bound (b + 1, b + 1 + tot, p[i]) - b;
	for (int i = 1; i <= n; i++)
		T.insert (T.root[i], T.root[i - 1], 1, tot, A[i].r);
	for (int i = 1; i <= m; i++)
	{
		int pos = depart (p[i]);
		ans = mul (ans + po[T.query (T.root[pos], 1, tot, p[i], tot)] - 1);
		if (i < m) ans = mul (ans - po[T.query (T.root[pos], 1, tot, p[i + 1], tot)] + 1 + mod);
	}
	std::cout << ans << "\n";
}
