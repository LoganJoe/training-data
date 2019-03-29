#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, m; ll A[N];
namespace solve1
{
	void Main ()
	{
		while (m--)
		{
			int op, x, y, v; scanf ("%d%d%d", &op, &x, &y);
			if (op == 0)
			{
				scanf ("%d", &v);
				for (int i = x; i <= y; i++) A[i] += 1ll * (i - x + 1) * v;
				for (int i = y + 1; i <= n; i++) A[i] += 1ll * (y - x + 1) * v;
			}
			else
			{
				ll ans = -1e18;
				for (int i = x; i <= y; i++) ans = std::max (ans, A[i]);
				printf ("%lld\n", ans);
			}
		}
	}
}
namespace solve2
{
	class Segment_Tree
	{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
		struct tree { ll v; }t[N << 2];
		void pushup (int x)
		{
			t[x].v = std::max (t[lc].v, t[rc].v);
		}
		ll val (int x, ll a, ll b) { return 1ll * a * x + b; }
	public:
		void build (int x, int l, int r)
		{
			if (l == r) return (void)(t[x].v = A[l]);
			build (lc, l, mid), build (rc, mid + 1, r);
			pushup (x);
		}
		void modify (int x, int l, int r, int p, ll v)
		{
			if (l == r) return (void)(t[x].v += v);
			if (p <= mid) modify (lc, l, mid, p, v);
			else modify (rc, mid + 1, r, p, v);
			pushup (x);
		}
		ll query (int x, int l, int r, int ql, int qr)
		{
			if (ql <= l && r <= qr) return t[x].v;
			ll res = -1e18;
			if (ql <= mid) res = std::max (res, query (lc, l, mid, ql, qr));
			if (qr > mid) res = std::max (res, query (rc, mid + 1, r, ql, qr));
			return res;
		}
	}T;
	void Main ()
	{
		while (m--)
		{
			T.build (1, 1, n);
			int op, x, y, v; scanf ("%d%d%d", &op, &x, &y);
			if (op == 0)
			{
				scanf ("%d", &v);
				for (int i = x; i <= y; i++) A[i] += 1ll * (i - x + 1) * v;
				for (int i = y + 1; i <= n; i++) A[i] += 1ll * (y - x + 1) * v;
				T.build (1, 1, n);
			}
			else printf ("%d\n", T.query (1, 1, n, x, y));
		}
	}
}
int main ()
{
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%lld", &A[i]), A[i] += A[i - 1];
	scanf ("%d", &m);
	//if (n <= 3000) 
	return solve1::Main (), 0;
	//else return solve2::Main (), 0;
}
