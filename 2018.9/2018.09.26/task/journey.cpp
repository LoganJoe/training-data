#include<bits/stdc++.h>
#define N 205
int n, m, E[N][N], dis[N], vis[N], mark[N][N], ans[200005], acnt;
struct query
{
	int op, x, y, v;
}s[100005];
int main ()
{
	//freopen("journey.in","r",stdin);
	//freopen("journey.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) scanf ("%d", &E[i][j]);
	for (int i = 1; i <= m; i++)
	{
		scanf ("%d%d%d", &s[i].op, &s[i].x, &s[i].y);
		if (s[i].op == 1) mark[s[i].x][s[i].y]++, s[i].v = E[s[i].x][s[i].y], E[s[i].x][s[i].y] = 1e9;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) 
				E[i][j] = std::min (E[i][j], E[i][k] + E[k][j]);
	for (int k = m; k; k--)
		if (s[k].op == 1)
		{
			mark[s[k].x][s[k].y]--;
			if (mark[s[k].x][s[k].y])continue;
			E[s[k].x][s[k].y]=std::min(E[s[k].x][s[k].y],s[k].v);
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++) E[i][j] = std::min (E[i][j], E[i][s[k].x] + E[s[k].x][j]);
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++) E[i][j] = std::min (E[i][j], E[i][s[k].y] + E[s[k].y][j]);
				
		}
		else ans[++acnt] = E[s[k].x][s[k].y];
	for (int i = acnt; i; i--) printf ("%d\n", ans[i]==1e9?-1:ans[i]);
}
