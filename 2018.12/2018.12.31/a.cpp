#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, t[N], A[N]; ll f[N];

class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	ll t[N << 2];
public:
	void insert (int x, int l, int r, int p, ll v)
	{
		if (l == r) return (void)(t[x] = v);
		if (p <= mid) insert (lc, l, mid, p, v);
		else insert (rc, mid + 1, r, p, v);
		t[x] = std::min (t[lc], t[rc]);
	}
	ll query (int x, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return t[x]; ll res = 1e15;
		if (ql <= mid) res = std::min (res, query (lc, l, mid, ql, qr));
		if (qr > mid) res = std::min (res, query (rc, mid + 1, r, ql, qr));
		return res;
	}
#undef mid
}T;
ll stav[N], staf[N];int top;
int main ()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) scanf ("%d%d", &t[i], &A[i]);
	stav[top = 1] = staf[top = 1] = 0;
	for (int i = 1; i <= n; i++)
	{
		f[i] = 1e15;
		for (; top && A[i] >= stav[top]; top--);
		stav[++top] = A[i], T.insert (1, 1, n, top, staf[top] + A[i] * 2);
		int pos = std::upper_bound (staf + 1, staf + 1 + top, t[i]) - staf - 1;
		if (pos) f[i] = t[i] + (stav[pos] << 1);
		if (pos^top) f[i] = std::min (f[i], T.query (1, 1, n, pos + 1, top));
		top++, stav[top] = 0, staf[top] = f[i];
	}
	std::cout << f[n] << "\n";
}
/*
10
1 3
2 6
3 7
8 5
11 4
23 23
32 32
80 23
81 12
82 23
*/
