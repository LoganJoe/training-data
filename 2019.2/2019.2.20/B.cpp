#include<bits/stdc++.h>
#define N 150005
#define ll long long
int	n, q, A[N], mark[N], b[N], tot, INf = 1e9 + 2; ll ans, lastans, anst[N];
namespace solve1
{
	class BIT
	{
		int t[N];
	public:
		void add (int x, int v) { for (;x && x <= tot; x += x & -x) t[x] += v; }
		int ask (int x) { int res = 0; for (; x; x -= x & -x) res += t[x]; return res; }
		void clear () { for (int i = 1; i <= tot; i++) t[i] = 0; }
	}T;
	void Main ()
	{
		while (q--)
		{
			int op, x, v; scanf ("%d", &op);
			if (op == 0) scanf ("%d%d", &x, &v), A[x^lastans] = v ^ lastans;
			else scanf ("%d", &x), mark[x^lastans] = 1;
			int ans = 0;
			for (int i = 1, j = 1; i <= n; i = j + 1)
			{
				if (mark[i]) { j = i; continue; }
				for (j = i; j < n && !mark[j + 1]; j++);
				tot = 0; int res = 0;
				for (int k = j; k >= i; k--)
					b[++tot] = A[k];
				std::sort (b + 1, b + 1 + tot);
				tot = std::unique (b + 1, b + 1 + tot) - b - 1;
				for (int k = j; k >= i; k--)
				{
					int x = std::lower_bound (b + 1, b + 1 + tot, A[k]) - b;
					res += T.ask (x - 1);
					T.add (x, 1);
				}
				ans ^= res; T.clear ();
			}
			printf ("%d\n", lastans = ans);
		}
	}
}
namespace solve2
{
	class Segment_Tree
	{
#define lc t[x].ls
#define rc t[x].rs
#define mid ((l+r)>>1)
		struct tree
		{
			int ls, rs, v;
		}t[N * 450];
	public:
		int root[N], cnt;
		void pushup (int x)
		{
			t[x].v = t[lc].v + t[rc].v;
		}
		void modify (std::vector<int> now, int l, int r, int p, int v)
		{
			if (l == r)
			{
				for (int x : now) t[x].v += v;
				return;
			}
			std::vector<int> tp = now;
			if (p <= mid)
			{
				for (int& x : now) x = lc ? lc : lc = ++cnt;
				modify (now, l, mid, p, v);
			}
			else
			{
				for (int& x : now) x = rc ? rc : rc = ++cnt;
				modify (now, mid + 1, r, p, v);
			}
			for (int& x : tp) pushup (x);
			tp.clear ();
			std::vector<int> ().swap (tp);
		}
		ll query (std::vector<int> now, int l, int r, int ql , int qr)
		{
			ll res = 0;
			if (ql <= l && r <= qr)
			{
				for (int x : now) res += t[x].v;
				return res;
			}
			std::vector<int> tp = now;
			if (ql <= mid)
			{
				for (int& x : now) x = lc;
				res += query (now, l, mid, ql, qr);
			}
			now = tp;
			if (qr > mid)
			{
				for (int&x : now) x = rc;
				res += query (now, mid + 1, r, ql, qr);
			}
			tp.clear ();
			std::vector<int> ().swap (tp);
			return res;
		}
	}T;
	struct BIT
	{
		void add (int x, int p, int v)
		{
			std::vector<int> now;
			for (; x <= n; x += x & -x) now.push_back (x);
			T.modify (now, 0, INf, p, v);
			now.clear ();
			std::vector<int> ().swap (now);
		}
		ll ask (int L, int R, int ql, int qr)
		{
			if (L > R || ql > qr) return 0;
			std::vector<int> now;
			L--;
			ll res = 0;
			for (int x = R; x; x -= x & -x) now.push_back (x);
			res += T.query (now, 0, INf, ql, qr);
			now.clear ();
			for (int x = L; x; x -= x & -x) now.push_back (x);
			res -= T.query (now, 0, INf, ql, qr);
			now.clear ();
			std::vector<int> ().swap (now);
			return res;
		}
	}B;
	std::set<int> S;
	void Main ()
	{
		for (int i = 1; i <= n; i++) T.root[i] = ++T.cnt;
		for (int i = 1; i <= n; i++)
			ans += B.ask (1, i, A[i] + 1, INf), B.add (i, A[i], 1);
		S.insert (0), S.insert (n + 1);
		anst[n + 1] = ans;//markd by the left side.
		while (q--)
		{
			int op, x, y;
			scanf ("%d%d", &op, &x), x ^= lastans;
			std::set<int>::iterator it = S.lower_bound (x);
			int r = *it, l = *--it;
			if (!op)
			{
				scanf ("%d", &y), y ^= lastans, ans ^= anst[r];
				anst[r] -= B.ask (l + 1, x - 1, A[x] + 1, INf) + B.ask (x + 1, r - 1, 0, A[x] - 1);
				B.add (x, A[x], -1), A[x] = y, B.add (x, A[x], 1);
				anst[r] += B.ask (l + 1, x - 1, A[x] + 1, INf) + B.ask (x + 1, r - 1, 0, A[x] - 1);
				ans ^= anst[r];
			}
			else
			{
				ans ^= anst[r]; 
				anst[r] -= B.ask (l + 1, x - 1, A[x] + 1, INf) + B.ask (x + 1, r - 1, 0, A[x] - 1);
				if (r - x > x - l)
				{
					for (int i = l + 1; i < x; i++)
					{
						int a = B.ask (l + 1, i - 1, A[i] + 1, INf), 
							b = B.ask (x + 1, r - 1, 0, A[i] - 1);
						anst[r] -= a + b, anst[x] += a;
					}
				}
				else
				{
					anst[x] = anst[r], anst[r] = 0;
					for (int i = x+1; i < r; i++)
					{
						int a = B.ask (x + 1, i - 1, A[i] + 1, INf), 
							b = B.ask (l + 1, x - 1, A[i] + 1, INf);
						anst[x] -= a + b; anst[r] += a;
					}
				}
				S.insert (x);
				ans ^= anst[x], ans ^= anst[r];
			}
			printf ("%lld\n", lastans = ans);
		}
	}
}
int main ()
{
	freopen ("baibaide.in", "r", stdin);
	freopen ("baibaide.out", "w", stdout);
	scanf ("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	if (n <= 1000 && q <= 1000) return solve1::Main (), 0;
	else return solve2::Main (), 0;
	
}
