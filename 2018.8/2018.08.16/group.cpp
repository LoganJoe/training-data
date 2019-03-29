#include<bits/stdc++.h>
#define N 105

int n, m, a[N][15], K, totS, f[N][1 << 13], val[1 << 13], va[1 << 13], g[1 << 13];
std::vector<int> e[N];
void dfs (int u, int fa)
{
	for (int i = 0; i <= totS; i++)
		for (int j = 1; j <= m; j++) if (i&(1 << j - 1)) f[u][i] -= a[u][j];
	for (auto v : e[u])
	{
		if (v == fa) continue;
		dfs (v, u);
		for (int s = totS; s ; s--)
			for (int t = s; ~t; t = (t - 1)&s)
			{
				f[u][s] = std::max (f[u][s], f[v][t] + f[u][s^t]);
				if(!t) break; 
			} 
	}
	for (int s = 0; s <= totS; s++) f[u][s] += val[s];
}
int main ()
{
	//freopen("group.in","r",stdin);
	//freopen("group.out","w",stdout);
	scanf ("%d%d", &n, &m); totS = (1 << m) - 1;
	for (int i = 1, u, v; i < n; i++) 
		scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf ("%d", &a[i][j]);
	scanf ("%d", &K);
	for (int i = 1, v, c, x, S; i <= K; i++)
	{
		scanf ("%d %d", &v, &c); S = 0;
		for (int j = 1; j <= c; j++) scanf ("%d", &x), S |= (1 << x - 1);
		val[S]+=v;
	}
	for (int i = totS; i ; i--)
		for(int s=i&(i-1);s;s=(i&(s-1))) val[i]+=val[s]; 
	dfs (1, 0);
	printf ("%d\n", f[1][totS]);
}
