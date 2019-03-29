#include<bits/stdc++.h>
#define N 105
int n, m, A[N], mark[N];
int l[N], r[N], s[N], ans;
void check ()
{
	int S = 0; for (int i = 1; i <= n; i++) if (mark[i]) S |= 1 << (i - 1);
	if (!S) return;
	for (int i = 1; i <= m; i++)
		if ((s[A[i]] & S) == S) { ans++; break; }
}
void dfs (int x)
{
	if (x > n) return check ();
	mark[x] = 0; dfs (x + 1);
	mark[x] = 1; dfs (x + 1);
}
int main ()
{
	freopen("a.in","r",stdin);
	freopen("a.ans","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf ("%d %d\n", &l[i], &r[i]);
		for (int j = l[i]; j <= r[i]; j++) s[j] |= (1 << i - 1);
	}
	for (int i = 1; i <= m; i++) scanf ("%d", &A[i]);
	dfs (1);
	printf ("%d\n", ans);
}
