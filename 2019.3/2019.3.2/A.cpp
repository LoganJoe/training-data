#include<bits/stdc++.h>
#define N 1000005
int Case, n, m, A[N], b[N], tot;
class Segment_Tree
{
#define lc t[x].ls
#define rc t[x].rs
#define mid ((l+r)>>1)
	struct node
	{
		int ls, rs, v;
	}t[N * 22];
	void pushup (int x)
	{
		t[x].v = t[lc].v^t[rc].v;
	}
public:
	int root[N], cnt;
	void insert (int &x, int y, int l, int r, int p, int v)
	{
		t[x = ++cnt] = t[y];
		if (l == r) return (void)(t[x].v ^= v);
		if (p <= mid) insert (lc, t[y].ls, l, mid, p, v);
		else insert (rc, t[y].rs, mid + 1, r, p, v);
		pushup (x);
	}
	int query (int x, int y, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr) return t[x].v^t[y].v;
		int res = 0;
		if (ql <= mid) res ^= query (lc, t[y].ls, l, mid, ql, qr);
		if (qr > mid) res ^= query (rc, t[y].rs, mid + 1, r, ql, qr);
		return res;
	}
}T;
std::pair<int, int> a[N], s[N];
int main ()
{
	freopen ("augury.in", "r", stdin);
	freopen ("augury.out", "w", stdout);
	scanf ("%d%d%d", &Case, &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]), a[i] = { A[i],i };
	std::sort (a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++)
	{
		if (i == 1 || a[i].first != a[i - 1].first) s[i] = { a[i].second,0 };
		else s[i] = { a[i].second,a[i - 1].second };
	}
	std::sort (s + 1, s + 1 + n);
	for (int i = 1; i <= n; i++)
		T.insert (T.root[i], T.root[i - 1], 0, n, s[i].second, A[s[i].first]);
	for (int i = 1; i <= n; i++) A[i] ^= A[i - 1];
	while (m--)
	{
		int l, r, op; scanf ("%d%d%d", &l, &r, &op);
		int res = A[r] ^ A[l - 1];
		if (op == 1) res ^= T.query (T.root[r], T.root[l - 1], 0, n, 0, l - 1);
		printf ("%d\n", res);
	}

}
/*
2
7 5
1 2 1 3 3 2 3
4 6 0
4 5 1
1 3 1
1 7 0
1 5 1

*/
