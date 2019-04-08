#include<bits/stdc++.h>
#define N 100005
#define ll long long
#define mod 998244353
int n, Q, p[N];
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod;
	return t;
}
int mul (int x) { return x >= mod ? x - mod : x; }
class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	struct node
	{
		int s[2][2], v;
		friend node operator +(node a, node b)
		{
			node c;
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
				{
					c.s[i][j] = 0;
					for (int k = 0; k < 2; k++)
						c.s[i][j] = (1ll * a.s[i][k] * b.s[k][j] + c.s[i][j]) % mod;
				}
			c.v = 1ll * a.v * b.v % mod;
			return c;
		}
		void set (int p)
		{
			s[1][0] = mul (p + mod - 1);
			s[1][1] = 1, s[0][1] = v = p;
		}
	}t[N << 2], E;
public:
	void init ()
	{
		E.s[0][0] = E.s[1][1] = E.v = 1;
	}
	void build (int x, int l, int r)
	{
		if (l == r) return t[x].set (p[l]);
		build (lc, l, mid), build (rc, mid + 1, r);
		t[x] = t[rc] + t[lc];
	}
	void insert (int x, int l, int r, int pos)
	{
		if (l == r) return t[x].set (p[l]);
		if (pos <= mid) insert (lc, l, mid, pos);
		else insert (rc, mid + 1, r, pos);
		t[x] = t[rc] + t[lc];
	}
	node query (int x, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return t[x];
		node res = E;
		if (ql <= mid) res = query (lc, l, mid, ql, qr) + res;
		if (qr > mid) res = query (rc, mid + 1, r, ql, qr) + res;
		return res;
	}
	int ask (int l, int r)
	{
		node res = query (1, 1, n, l + 1, r);
		return 1ll * p[l] * res.v % mod * Pow ((1ll * res.s[1][0] * p[l] + res.s[1][1]) % mod, mod - 2) % mod;
	}
}T;
int main ()
{
	freopen ("hs.in", "r", stdin);
	freopen ("hs.out", "w", stdout);
	scanf ("%d%d", &n, &Q);
	for (int i = 1, a, b; i <= n; i++)
		scanf ("%d%d", &a, &b), p[i] = 1ll * a * Pow (b, mod - 2) % mod;
	T.init (), T.build (1, 1, n);
	while (Q--)
	{
		int op, x, a, b; scanf ("%d", &op);
		if (op == 1)
		{
			scanf ("%d%d%d", &x, &a, &b);
			p[x] = 1ll * a * Pow (b, mod - 2) % mod;
			T.insert (1, 1, n, x);
		}
		else
		{
			scanf ("%d%d", &a, &b);
			if (a == b) { printf ("%d\n", p[a]); continue; }
			else printf ("%d\n", T.ask (a, b));
		}
	}
}