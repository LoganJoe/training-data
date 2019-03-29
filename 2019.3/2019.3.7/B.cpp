#include<bits/stdc++.h>
#define ll long long
#define N 100005
int n, A[N], rt, cnt;
ll ans;
class Splay
{
#define lc t[x].son[0]
#define rc t[x].son[1]
	struct tree
	{
		int son[2], fa, size;
		ll val, tag;
	}t[N << 1];
	void pushup (int x) { if (x) t[x].size = t[lc].size + t[rc].size + 1; }
	void pushdown (int x)
	{
		if (!t[x].tag) return;
		if (t[lc].val != 1e18) t[lc].val += t[x].tag, t[lc].tag += t[x].tag;
		if (t[rc].val != -1e18) t[rc].val += t[x].tag, t[rc].tag += t[x].tag;
		t[x].tag = 0;
	}
	void rotate (int x, int &k)
	{
		int y = t[x].fa, z = t[y].fa, l = t[y].son[1] == x, r = l ^ 1;
		y == k ? k = x : t[z].son[t[z].son[1] == y] = x;
		t[x].fa = z, t[y].fa = x, t[t[x].son[r]].fa = y;
		t[y].son[l] = t[x].son[r], t[x].son[r] = y;
		pushup (y), pushup (x);
	}
	void update (int x) { if (t[x].fa) update (t[x].fa); pushdown (x); }
	void splay (int x, int &k)
	{
		for (update (x); x^k; rotate (x, k))
		{
			int y = t[x].fa, z = t[y].fa;
			if (y ^ k)
				(t[z].son[0] == y ^ t[y].son[0] == x) ? rotate (x, k) : rotate (y, k);
		}
	}
public:
	void insert (ll v)
	{
		int x = rt, pa = 0;
		for (; x; pushdown (x), pa = x, x = t[x].son[t[x].val < v]);
		t[x = ++cnt].size = 1;
		t[x].fa = pa, t[pa].son[t[pa].val > v] = x;
		t[x].val = v; t[x].tag = t[x].son[0] = t[x].son[1] = 0;
		splay (x, rt);
	}
	int find ()
	{
		int x = rt;
		for (; lc && t[lc].val != 1e18; x = lc);
		return splay (x, rt), x;
	}
	void modify (ll v)
	{
		int x = rt, pa = 0, lst = 0, mark = 0;
		for (; x;)
		{
			pushdown (x);
			ll sz = t[lc].size, nw = 1ll * v * (lst + sz);
			pa = x;
			if (nw >= t[x].val) x = lc, mark = 0;
			else x = rc, lst += sz + 1, mark = 1;
		}
		t[x = ++cnt].size = 1;
		t[x].fa = pa, t[x].val = 1ll * lst * v;
		t[pa].son[mark] = x, splay (x, rt);
		if (t[rc].val != -1e18) t[rc].val += v, t[rc].tag += v;
	}
	void solve (int x)
	{
		pushdown (x);
		if (lc && t[lc].val != 1e18) solve (lc);
		ans += t[x].val; printf ("%lld ", ans);
		if (rc && t[rc].val != -1e18) solve (rc);
	}
}T;
int main ()
{
	freopen ("subsequence.in", "r", stdin);
	freopen ("subsequence.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	T.insert (1e18), T.insert (-1e18);
	for (int i = 1; i <= n; i++) T.modify (A[i]);
	T.find (); T.solve (rt);
	return 0;
}