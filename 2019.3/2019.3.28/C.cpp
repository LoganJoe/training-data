#include<bits/stdc++.h>
#define N 50005
#define M 505
#define ll long long
int Case, n, p, qcnt; ll ans[N];
struct node
{
	int w, v, l, r;
}q[N];
std::deque<node> dq;
class Segment_Tree
{
#define lc x<<1
#define rc x<<1|1
#define mid ((l+r)>>1)
	std::vector<std::pair<int, int> > t[N << 2];
	ll f[20][M], tp[M];
public:
	void init ()
	{
		f[0][0] = 0;
		for (int i = 1; i < p; i++) f[0][i] = -1;
	}
	void insert (int x, int l, int r, int ql, int qr, std::pair<int, int> v)
	{
		if (ql <= l && r <= qr) return (void)(t[x].push_back (v));
		if (ql <= mid) insert (lc, l, mid, ql, qr, v);
		if (qr > mid) insert (rc, mid + 1, r, ql, qr, v);
	}
	void solve (int x, int l, int r, int dep)
	{
		for (int i = 0; i < p; i++) f[dep][i] = f[dep - 1][i];
		for (int j = 0; j < t[x].size (); j++)
		{
			for (int i = 0; i < p; i++)
			{
				tp[i] = f[dep][i];
				if (tp[i] != -1) tp[i] += t[x][j].second;
			}
			for (int i = 0; i < p; i++) if (tp[i] != -1)	
				f[dep][(i + t[x][j].first) % p] = std::max (tp[i], f[dep][(i + t[x][j].first) % p]);
		}
		if (l == r)
		{
			if (!q[l].w) return;
			ll res = -1;
			for (int i = q[l].l; i <= q[l].r; i++)
				res = std::max (res, f[dep][i]);
			ans[q[l].v] = res;
			return;
		}
		solve (lc, l, mid, dep + 1), solve (rc, mid + 1, r, dep + 1);
	}
}T;
int main ()
{
	freopen ("tanwan.in", "r", stdin);
	freopen ("tanwan.out", "w", stdout);
	scanf ("%d%d%d", &Case, &n, &p);
	for (int i = 1; i <= n; i++)
	{
		char ch[10]; int w, v;
		scanf ("%s", ch);
		if (ch[0] == 'I')
		{
			scanf ("%d%d", &w, &v);
			if (ch[1] == 'F') dq.push_front ({ w,v,i,0 });
			else dq.push_back ({ w,v,i,0 });
		}
		if (ch[0] == 'D')
		{
			if (ch[1] == 'F')
			{	
				node x = dq.front (); dq.pop_front ();
				x.r = i;
				T.insert (1, 1, n, x.l, x.r, { x.w, x.v });
			}
			else
			{
				node x = dq.back (); dq.pop_back ();
				x.r = i;
				T.insert (1, 1, n, x.l, x.r, { x.w, x.v });
			}
		}
		if (ch[0] == 'Q') scanf ("%d%d", &w, &v), q[i] = { i,++qcnt,w,v };
	}
	while (!dq.empty ())
	{
		node x = dq.back (); dq.pop_back ();
		x.r = n;
		T.insert (1, 1, n, x.l, x.r, { x.w, x.v });
	}
	T.init ();
	T.solve (1, 1, n, 1);
	for (int i = 1; i <= qcnt; i++) printf ("%lld\n", ans[i]);
}
/*
0 
11 10 
QU 0 0 
QU 1 9 
IG 14 7 
IF 3 5 
QU 0 9 
IG 1 8 
DF 
QU 0 4
IF 1 2 
DG 
QU 2 9

*/
