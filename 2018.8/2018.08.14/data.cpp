#include<bits/stdc++.h>
#define N 100005
struct node
{
	int opt, pos, x, a, b, c, v;
	friend bool operator <(node t1, node t2)
	{
		if (t1.x != t2.x) return t1.x < t2.x;
		if (t1.a != t2.a) return t1.a < t2.a;
		if (t1.b != t2.b) return t1.b < t2.b;
		if (t1.c != t2.c) return t1.c < t2.c;
		return t1.opt < t2.opt;
	}
}A[N << 3], p[N << 3], B[N << 3];
int n, m, lb[N << 2], tot, cnt, ans[N], Query[N];
char ch[10];
class BIT
{
	int t[N << 1];
	int lowbit (int x) { return x & (-x); }
public:
	void add (int x, int v) { for (int i = x; i <= tot; i += lowbit (i)) t[i] += v; }
	int ask (int x) { int res = 0; for (int i = x; i; i -= lowbit (i)) res += t[i]; return res; }
}T;
void solve2 (int l, int r)
{
	if (l == r) return;
	int mid = (l + r) >> 1, sl = l, sr = mid + 1, top = 0;
	solve2 (l, mid); solve2 (mid + 1, r);
	while (sr <= r)
	{
		if (sl <= mid && B[sl].b <= B[sr].b)
		{
			if (!B[sl].opt) T.add (B[sl].c, B[sl].v);
			p[++top] = B[sl], sl++;
		}
		else
		{
			if (B[sr].opt) ans[B[sr].pos] += B[sr].v * T.ask (B[sr].c) ;
			p[++top] = B[sr], sr++;
		}
	}
	for (int i = l; i < sl; i++) if (!B[i].opt) T.add (B[i].c, -B[i].v);
	while (sl <= mid) p[++top] = B[sl], sl++;
	for (int i = l; i <= r; i++) B[i] = p[i - l + 1];

}
void solve1 (int l, int r)
{
	if (l == r) return;
	int mid = (l + r) >> 1, sl = l, sr = mid + 1, cnt = 0, top = 0;
	solve1 (l, mid); solve1 (mid + 1, r);
	while (sr <= r)
	{
		if (sl <= mid && A[sl].a <= A[sr].a)
		{
			if (!A[sl].opt) B[++cnt] = A[sl];
			p[++top] = A[sl], sl++;
		}
		else
		{
			if (A[sr].opt) B[++cnt] = A[sr];
			p[++top] = A[sr], sr++;
		}
	}
	while (sl <= mid) p[++top] = A[sl], sl++;
	for (int i = l; i <= r; i++) A[i] = p[i - l + 1];
	if (cnt) solve2 (1, cnt);
}
int main ()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int a, b, c;
		scanf ("%d%d%d", &a, &b, &c);
		A[i] = { 0,0,0,a,b,c,1 }; lb[++tot] = c;
	}
	scanf ("%d", &m);
	int a, b, c, aa, bb, cc, r;
	for (int i = 1; i <= m; i++)
	{
		scanf ("%s", ch);
		if (ch[0] == 'A')
		{
			scanf ("%d%d%d", &a, &b, &c);
			A[++n] = { 0,0,i,a,b,c,1 }; lb[++tot] = c;
		}
		if (ch[0] == 'C')
			A[++n] = { 0,0,i,a,b,c,-1 };
		if (ch[0] == 'Q')
		{
			scanf ("%d%d%d%d", &aa, &bb, &cc, &r);
			A[++n] = { 1,i,i,aa + r,bb + r,cc + r,1 };
			A[++n] = { 1,i,i,aa-1 ,bb + r,cc + r,-1 };
			A[++n] = { 1,i,i,aa + r,bb-1,cc + r,-1 };
			A[++n] = { 1,i,i,aa + r,bb + r,cc-1 ,-1 };
			A[++n] = { 1,i,i,aa-1 ,bb-1 ,cc + r,1 };
			A[++n] = { 1,i,i,aa + r,bb-1 ,cc-1 ,1 };
			A[++n] = { 1,i,i,aa-1 ,bb + r,cc-1 ,1 };
			A[++n] = { 1,i,i,aa-1,bb-1,cc-1,-1 };
			lb[++tot] = cc; lb[++tot] = cc + r;
			Query[i] = 1;
		}
	}
	std::sort (lb + 1, lb + 1 + tot);
	tot = std::unique (lb + 1, lb + 1 + tot) - lb - 1;
	for (int i = 1; i <= n; i++) A[i].c = std::lower_bound (lb + 1, lb + 1 + tot, A[i].c) - lb;
	std::sort (A + 1, A + 1 + n);
	solve1 (1, n);
	for (int i = 1; i <= m; i++) if (Query[i]) printf ("%d\n", ans[i]);
}
/*
2
1 2 3
1 1 3
2
ADD 1 1 1
QUERY 0 0 0 4
QUERY 1 1 2 3
*/
