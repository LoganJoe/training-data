#include<bits/stdc++.h>
#define ll long long
#define N 100005
int n, Q, K, A[N], st[N][20];
ll ans[N * 5];
class BIT
{
	ll t[N];
public:
	void add (int x, int v) { for (; x <= n; x += x & -x) t[x] += v; }
	ll ask (int x) { ll res = 0; for (; x > 0; x -= x & -x) res += t[x]; return res; }
}T[2];
struct node
{
	int l, r, id;
}p[N * 5], q[N * 5];
bool cmpl (node t1, node t2) { return t1.l < t2.l; }
bool cmpr (node t1, node t2) { return t1.r < t2.r; }
int main ()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf ("%d%d%d", &n, &Q, &K);
	for (int i = 1; i <= n; i++) scanf ("%d", &A[i]);
	for (int i = 1; i <= Q; i++) 
		scanf ("%d%d", &p[i].l, &p[i].r), p[i].id = i, q[i] = p[i];
	std::sort (p + 1, p + 1 + Q, cmpl);
	std::sort (q + 1, q + 1 + Q, cmpr);
	for (int i = 1; i <= n; i++) st[i][0] = A[i];
	for (int j = 1; j < 20; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			st[i][j] = st[i][j - 1] & st[i + (1 << j - 1)][j - 1];
	for (int i = 1, j = 1, k = 1; i <= n; i++)
	{
		for (; j <= Q && p[j].l == i; j++)
			ans[p[j].id] -= T[0].ask (p[j].r) * p[j].r + T[1].ask (p[j].r);
		for (int pos = i, x = A[i]; pos <= n; pos++, x = x & A[pos])
		{
			int l = pos, r = pos;
			for (int t = 19; ~t; t--)
				if (r + (1 << t) - 1 <= n && (x & st[r][t]) == x)
					r += (1 << t) - 1;
			pos = r;
			if (x % K) continue;
			T[0].add (l, 1), T[0].add (r + 1, -1);
			T[1].add (l, 1 - l), T[1].add (r + 1, r);
		}
		for (; k <= Q && q[k].r == i; k++)
			ans[q[k].id] += T[0].ask (q[k].r) * q[k].r + T[1].ask (q[k].r);
	}
	for (int i = 1; i <= Q; i++)
		printf ("%lld\n", ans[i]);
}

