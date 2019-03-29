#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, t[N], A[N];
ll f[N];
class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	ll t[N << 2];
public:
	void insert (int x, int l, int r, int p, int v)
	{
		if (l == r) return (void)(t[x] = v);
		if (p <= mid) insert (lc, l, mid, p, v);
		else insert (rc, mid + 1, r, p, v);
		t[x] = std::max (t[lc], t[rc]);
	}
	ll query (int x, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return t[x]; ll res = 0;
		if (ql <= mid) res = std::max (res, query (lc, l, mid, ql, qr));
		if (qr > mid) res = std::max (res, query (rc, mid + 1, r, ql, qr));
		return res;
	}
#undef mid
}T;
int main ()
{
	freopen("a.in","r",stdin);
	freopen("a.ans","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d%d", &t[i], &A[i]);
	for (int i = 1; i <= n; i++) T.insert (1, 1, n, i, A[i]);
	for (int i = 1; i <= n; i++)
	{
		f[i] = 1e15;
		for (int j = 0; j < i; j++)
			f[i] = std::min (f[i], std::max (f[j], 1ll * t[i]) + T.query (1, 1, n, j + 1, i) * 2);
	}
	std::cout << f[n] << "\n";
}
