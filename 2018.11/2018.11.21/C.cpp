#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, m; ll ans;
struct node
{
	int l, r, p;
	friend bool operator <(node t1, node t2)
	{
		return t1.r < t2.r || t1.r == t2.r && t1.p < t2.p;
	}
}A[N];
class Segent_Tree
{
#define lc (x<<1)
#define rc (x<<1|1)
#define mid ((l+r)>>1)
	struct tree { ll v, tag; } t[N << 2];
	void update (int x, ll v) { t[x].v += v,t[x].tag += v; }
	void pushdown (int x)
	{
		if (!t[x].tag) return;
		update (lc, t[x].tag), update (rc, t[x].tag);
		t[x].tag = 0;
	}
public:
	void build (int x, int l, int r)
	{
		t[x].tag = 0;
		if (l == r) return (void)(t[x].v = 0);
		build (lc, l, mid), build (rc, mid + 1, r);
		t[x].v = std::max (t[lc].v, t[rc].v);
	}
	void modify (int x, int l, int r, int ql, int qr, int v)
	{
		if (ql <= l && r <= qr) return update (x, v);
		pushdown (x);
		if (ql <= mid) modify (lc, l, mid, ql, qr, v);
		if (qr > mid) modify (rc, mid + 1, r, ql, qr, v);
		t[x].v = std::max (t[lc].v, t[rc].v);
	}
	ll query (int x, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return t[x].v;
		pushdown (x); ll res = 0;
		if (ql <= mid) res = std::max (res, query (lc, l, mid, ql, qr));
		if (qr > mid) res = std::max (res, query (rc, mid + 1, r, ql, qr));
		return res;
	}
}T;
int main ()
{
	freopen ("c.in", "r", stdin);
	freopen ("c.out", "w", stdout);
	std::ios::sync_with_stdio (0);
	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) std::cin >> A[i].l >> A[i].r >> A[i].p;
	for (int i = 1; i <= m; i++)
	{
		std::sort (A + 1, A + 1 + i);
		T.build (1, 1, n);
		for (int j = 1; j <= i; j++)
		{
			ll cnt = T.query (1, 1, n, A[j].l, A[j].r - 1);
			ans = std::max (ans, cnt + A[j].r + A[j].p - 1);
			T.modify (1, 1, n, A[j].l, A[j].r - 1, A[j].p);
		}
		std::cout << ans << "\n";
	}
	return 0;
}
