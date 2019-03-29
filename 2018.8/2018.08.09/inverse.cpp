#include<bits/stdc++.h>
#define N 50005
int n, m, cnt[N];
std::vector<int> e[N];
char s[N][4];
void dfs (int u, int fa,int val,int tot)
{
//	printf ("%d %d %d %d\n", u, fa, val, tot);
	if (val < 0) return;
	if (!val) cnt[++tot]++;
	for (auto to : e[u]) if (to != fa)dfs (to, u, val + ((s[to][0] == '(') ? 1 : -1), tot);
}
int main ()
{
//	freopen ("test.in", "r", stdin);
//	freopen ("test.out", "w", stdout);
	scanf ("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
	for (int i = 1; i <= n; i++) scanf ("%s", s[i]);
	for (int i = 1; i <= n; i++) dfs (i, 0, ((s[i][0] == '(') ? 1 : -1), 0);
	scanf ("%d", &m);
	while (m--)
	{
		int x; scanf ("%d", &x);
		printf ("%d\n", cnt[x]);
	}
}
