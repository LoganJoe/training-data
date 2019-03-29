#include<bits/stdc++.h>
#define N 300005
int n, m, mark[N], col[N];
std::vector<int>e[N];
void solve2 (int x)
{
	printf ("B 3 %d %d %d\n", x, e[x][0], e[x][1]);
}
int main ()
{
	freopen("g.in","r",stdin);freopen("g.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++) scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
	if (n <= 4)
	{
		printf ("A ");
		for (int i = 1; i <= n; i++) printf ("%d ", i);
		return puts (""), 0;
	}
	for (int i = 1; i <= n; i++)
	{
		for (auto v : e[i]) mark[col[v]] = 1;
		for (int j = 1; j <= 4; j++) if (!mark[j]) { col[i] = j; break; }
		if (!col[i]) return solve2 (i), 0;
	}
	printf ("A ");
	for (int i = 1; i <= n; i++) printf ("%d ", col[i]);
	return puts (""), 0;
}
