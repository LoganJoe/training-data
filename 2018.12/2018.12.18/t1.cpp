#include<bits/stdc++.h>
#define N 100005
#define P 666073
#define ull unsigned long long
#define ll long long
int n, Q, A[N], tot;
ll sumfront[N], sumback[N], distance[N], sumdist[N], ans = 1e18;
ull ha, mark[N], b[N];
struct node
{
	int s, t;
	friend bool operator <(node t1, node t2) { return t1.s < t2.s; }
}B[N];
std::vector<int> S[N];
struct Preisdent_Tree
{
#define lc t[x].ls
#define rc t[x].rs
#define mid ((l+r)>>1)
	struct tree
	{
		int ls, rs, v;
	}t[N * 40];
public:
	int root[N], cnt;
	void insert (int &x, int y, int l, int r, int p, int v)
	{
		t[x = ++cnt] = t[y];
		if (l == r) return (void)(t[x].v += v);
		if (p <= mid) insert (lc, t[x].ls, l, mid, p, v);
		else insert (rc, t[x].rs, mid + 1, r, p, v);
		t[x].v = t[lc].v + t[rc].v;
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
}T;
ll calc (int a, int b)
{
	ll res = sumdist[n];
	res += T.query (T.root[a - 1], 1, n, b, n);
	return res;
}
void solve (std::vector<int> S, int len)
{
	for (int i = 0, j = 1; i < len && j < len; i++)
	{
		for (; j < len - 1 && calc (S[i], S[j + 1]) < calc (S[i], S[j]); j++);
		ans = std::min (ans, calc (S[i], S[j]));
	}
}
int main ()
{
	scanf ("%d%d", &n, &Q);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 1; i <= n; i++) sumfront[i] = sumfront[i - 1] + A[i];
	for (int i = n; i >= 1; i--) sumback [i] = sumback [i + 1] + A[i];
	for (int i = 1; i <= Q; i++)
	{
		scanf ("%d%d", &B[i].s, &B[i].t); B[i].s++, B[i].t++;
		if (B[i].s > B[i].t) std::swap (B[i].s, B[i].t);
		ha = ha * P + (B[i].s ^ B[i].t) << 2 + B[i].s;
		mark[B[i].s] += ha, mark[B[i].t + 1] -= ha;
	}
	for (int i = 1; i <= n; i++) mark[i] += mark[i - 1], b[++tot] = mark[i];
	std::sort (b + 1, b + 1 + tot);
	tot = std::unique (b + 1, b + 1 + tot) - b - 1;
	for (int i = 1; i <= n; i++)
	{
		mark[i] = std::lower_bound (b + 1, b + 1 + tot, mark[i]) - b;
		if (S[mark[i]].empty() || S[mark[i]].back () != i - 1) S[mark[i]].push_back (i);
	}
	std::sort (B + 1, B + 1 + n);
	for (int i = 1; i <= n; i++)
	{
		distance[i] = sumfront[B[i].t - 1] - sumfront[B[i].s - 1];
		sumdist[i] = sumdist[i - 1] + distance[i];
	}
	for (int i = 1,j = 1; i <= n; i++)
	{
		T.root[i] = T.root[i - 1];
		for (; j <= n && B[j].s == i; j++) 
			T.insert (T.root[i], T.root[i], 1, n, i, sumfront[n] - 2 * distance[j]);
	}
	for (int i = 1; i <= tot; i++)
	{
		std::sort (S[i].begin (), S[i].end ());
		int len = S[i].size ();
		if (len <= 1) continue;
		solve (S[i], len);
	}
	ans = std::min (ans, sumdist[n]);
	std::cout << ans << "\n";
}
