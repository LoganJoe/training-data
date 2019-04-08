#include<bits/stdc++.h>
#define N 200005
#define ll long long
int Case, n, m, na, nb, ida[N], idb[N]; char s[N];
struct node
{
	int l, r;
}A[N], B[N];
class Suffix_Array
{
	int cmp (int x, int y, int w) { return tp[x] == tp[y] && tp[x + w] == tp[y + w]; }
	void qsort ()
	{
		for (int i = 0; i <= m; i++) tax[i] = 0;
		for (int i = 1; i <= n; i++) tax[rnk[tp[i]]]++;
		for (int i = 1; i <= m; i++) tax[i] += tax[i - 1];
		for (int i = n; i >= 1; i--) sa[tax[rnk[tp[i]]]--] = tp[i];
	}
public:
	int sa[N], rnk[N], tp[N], tax[N], height[N], m, Min[N][20], Log[N];
	void getsa ()
	{
		for (int i = 1; i <= n; i++) rnk[i] = s[tp[i] = i]; m = 28, qsort ();
		for (int j = 1, p = 0; p < n; j <<= 1, m = p)
		{
			p = 0;
			for (int i = n - j + 1; i <= n; i++) tp[++p] = i;
			for (int i = 1; i <= n; i++) if (sa[i] > j) tp[++p] = sa[i] - j;
			qsort (); std::swap (rnk, tp), rnk[sa[1]] = p = 1;
			for (int i = 2; i <= n; i++) rnk[sa[i]] = cmp (sa[i], sa[i - 1], j) ? p : ++p;
		}
	}
	void getheight ()
	{
		for (int i = 1, k = 0; i <= n; i++)
		{
			if (rnk[i] == 1) continue;
			if (k) k--; int j = sa[rnk[i] - 1];
			for (; s[i + k] == s[j + k]; k++);
			height[rnk[i]] = k;
		}
	}
	void process ()
	{
		for (int i = 2; i <= n; i++) Log[i] = Log[i >> 1] + 1;
		for (int i = 1; i <= n; i++) Min[i][0] = height[i];
		for (int j = 1; j < 20; j++)
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
				Min[i][j] = std::min (Min[i][j - 1], Min[i + (1 << j - 1)][j - 1]);
	}
	
	int asklcp (int l, int r)
	{
		int k = Log[r - l];
		return std::min (Min[l + 1][k], Min[r - (1 << k) + 1][k]);
	}
	void clear ()
	{
		for (int i = 1; i <= n; i++) 
			sa[i] = rnk[i] = tp[i] = tax[i] = height[i] = 0;
	}
}SA;
int head[N * 5], ecnt, deg[N * 5]; ll dis[N * 5];
struct edge
{
	int v, next; ll w;
}e[N * 25];
void add (int u, int v, ll w)
{
	e[++ecnt] = { v,head[u], w }; head[u] = ecnt; deg[v]++;
}
class Segment_Tree
{
#define lc t[x].ls
#define rc t[x].rs
#define mid ((l+r)>>1)
	struct node
	{
		int ls, rs;
	}t[N << 2];
public:
	int rt, id[N], cnt;
	void build (int &x, int l, int r)
	{
		if (!x) x = ++cnt, lc = rc = 0;
		if (l == r) return (void)(id[l] = x);
		build (lc, l, mid), build (rc, mid + 1, r);
		add (x, lc, 0), add (x, rc, 0);
	}
	void query (int x, int l, int r, int ql, int qr, int v, ll w)
	{
		if (ql <= l && r <= qr) return add (v, x, w);
		if (ql <= mid) query (lc, l, mid, ql, qr, v, w);
		if (qr > mid) query (rc, mid + 1, r, ql, qr, v, w);
	}
	void init () { rt = cnt = 0; }
	
#undef mid
}T;
void clear ()
{
	for (int i = 1; i <= T.cnt; i++) head[i] = deg[i] = dis[i] = 0;
	ecnt = 0; SA.clear ();
}
ll topo ()
{
	std::queue<int> q;
	for (int i = 1; i <= T.cnt; i++) if (!deg[i]) q.push (i);
	int qcnt = 0;
	while (!q.empty ())
	{
		int u = q.front (); q.pop (); qcnt++;
		for (int i = head[u]; i; i = e[i].next)
		{
			int v = e[i].v; deg[v]--;
			dis[v] = std::max (dis[v], dis[u] + e[i].w);
			if (!deg[v]) q.push (v);
		}
	}
	if (qcnt != T.cnt) return -1;
	ll res = 0;
	for (int i = 1; i <= T.cnt; i++) res = std::max (res, dis[i]);
	return res;
}
int main ()
{
	freopen ("string.in", "r", stdin);
	freopen ("string.out", "w", stdout);
	for (scanf ("%d", &Case); Case--; clear ())
	{
		scanf ("%s", s + 1), n = strlen (s + 1);
		for (int i = 1; i <= n; i++) s[i] -= 'a' - 1;
		SA.getsa (); SA.getheight (); SA.process ();
	//	for (int i = 1; i <= n; i++) printf ("%d ", SA.sa[i]); puts ("");
	//	for (int i = 1; i <= n; i++) printf ("%d ", SA.rnk[i]); puts ("");
	//	for (int i = 1; i <= n; i++) printf ("%d ", SA.height[i]); puts ("");
		T.init (), T.build (T.rt, 1, n);
		scanf ("%d", &na);
		for (int i = 1; i <= na; i++) scanf ("%d%d", &A[i].l, &A[i].r);
		scanf ("%d", &nb);
		for (int i = 1; i <= nb; i++) scanf ("%d%d", &B[i].l, &B[i].r);
		for (int i = 1; i <= na; i++)
			add (T.id[SA.rnk[A[i].l]], ida[i] = ++T.cnt, A[i].r - A[i].l + 1);
		scanf ("%d", &m);
		for (int i = 1; i <= m; i++)
		{
			int x, y; scanf ("%d%d", &x, &y);
			int t = SA.rnk[B[y].l], len = B[y].r - B[y].l + 1;
			int l = 1, r = t - 1, tl = t, tr = t;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (SA.asklcp (mid, t) >= len) tl = mid, r = mid - 1;
				else l = mid + 1;
			}
			l = t + 1, r = n, tr = t;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (SA.asklcp (t, mid) >= len) tr = mid, l = mid + 1;
				else r = mid - 1;
			}
			T.query (T.rt, 1, n, tl, tr, ida[x], 0);
		}
		printf ("%lld\n", topo ());
	}
}
