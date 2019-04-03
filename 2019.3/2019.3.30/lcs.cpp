#include<bits/stdc++.h>
#define N 80005
int n, A[4][N], cnt, f[N], ans;
std::vector<int> t[4][N];
struct node
{
	int a, b, c, d, id;
}B[N], C[N], D[N], tp[N], E[N];
bool cmp1 (node t1, node t2)
{
	if (t1.a != t2.a) return t1.a < t2.a;
	if (t1.b != t2.b) return t1.b < t2.b;
	if (t1.c != t2.c) return t1.c < t2.c;
	return t1.d < t2.d;
}
bool cmp2 (node t1, node t2)
{
	if (t1.b != t2.b) return t1.b < t2.b;
	if (t1.c != t2.c) return t1.c < t2.c;
	if (t1.d != t2.d) return t1.d < t2.d;
	return t1.id < t2.id;
}
bool cmp3 (node t1, node t2)
{
	if (t1.c != t2.c) return t1.c < t2.c;
	if (t1.d != t2.d) return t1.d < t2.d;
	return t1.id < t2.id;
}
class BIT
{
	int t[N];
public:
	void add (int x, int v) { for (; x <= n; x += x & -x) t[x] = std::max (t[x], v); }
	int ask (int x) { int res = 0; for (; x > 0; x -= x & -x) res = std::max (res, t[x]); return res; }
	void clear (int x) { for (; x <= n; x += x & -x) t[x] = 0; }
}T;
void solve2 (int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1, top = l - 1;
	solve2 (l, mid);
	for (int i = mid + 1; i <= r; i++) tp[i] = C[i];
	std::sort (C + mid + 1, C + r + 1, cmp3);
	int mark = 0;
	for (int i = l; i <= mid; i++) mark |= !C[i].a;
	for (int i = mid + 1; i <= r; i++) mark |= C[i].a;
	if (!mark) goto label;
	for (int i = l, j = mid + 1; i <= mid || j <= r;)
	{
		if (cmp3 (C[i], C[j]) && i <= mid || j > r)
		{
			if (!C[i].a) T.add (C[i].d, f[C[i].id]);
			i++;
		}
		else
		{
			if (C[j].a) f[C[j].id] = std::max (f[C[j].id], T.ask (C[j].d - 1) + 1);
			j++;
		}
	}
	for (int i = l; i <= mid; i++) if (!C[i].a) T.clear (C[i].d);
label:
	for (int i = mid + 1; i <= r; i++) C[i] = tp[i];
	solve2 (mid + 1, r);
	for (int i = l, j = mid + 1; i <= mid || j <= r;)
		if (cmp3 (C[i], C[j]) && i <= mid || j > r) D[++top] = C[i++];
		else D[++top] = C[j++];
	for (int i = l; i <= r; i++) C[i] = D[i];
}
void solve1 (int l, int r)
{
	if (l == r || B[l].a == B[r].a) return;
	int mid = l + r >> 1, top = l - 1;
	for (; B[mid].a == B[mid + 1].a && mid < r; mid++);
	if (r == mid) return;
	solve1 (l, mid);
	for (int i = l; i <= r; i++) E[i] = B[i];
	for (int i = l; i <= mid; i++)  C[++top] = B[i], C[top].a = 0;
	for (int i = mid + 1; i <= r; i++) C[++top] = B[i], C[top].a = 1;
	std::sort (C + l, C + 1 + r, cmp2);
	solve2 (l, r);
	for (int i = l; i <= r; i++) B[i] = E[i];
	solve1 (mid + 1, r);
}
int main ()
{
	freopen ("lcs.in", "r", stdin);
	freopen ("lcs.out", "w", stdout);
	scanf ("%d", &n);
	for (int k = 0; k < 4; k++)
		for (int i = 1; i <= n; i++) 
			scanf ("%d", &A[k][i]), t[k][A[k][i]].push_back (i);
	for (int i = 1; i <= n; i++)
		for (int t1 : t[0][i])
			for (int t2 : t[1][i])
				for (int t3 : t[2][i])
					for (int t4 : t[3][i])
						B[++cnt] = { t1,t2,t3,t4,0 };
	std::sort (B + 1, B + 1 + cnt, cmp1);
	for (int i = 1; i <= cnt; i++) B[i].id = i, f[i] = 1;
	solve1 (1, cnt);
	for (int i = 1; i <= cnt; i++) ans = std::max (ans, f[i]);
	printf ("%d\n", ans);
}
/*
5
1 2 1 2 3
1 2 3 1 2
3 1 2 1 2
1 2 1 2 1

*/