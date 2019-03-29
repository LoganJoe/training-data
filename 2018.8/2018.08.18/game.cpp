#include<bits/stdc++.h>
#define N 100005

int n, m, Q;
struct edge
{
	int u, v;
}e[N << 1];
int f[N];
int find (int x) {return f[x] == x ? f[x] : f[x] = find (f[x]);}
int main ()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf ("%d%d", &e[i].u, &e[i].v);
	scanf ("%d", &Q);
	while (Q--)
	{
		int l, r, a, b; scanf ("%d%d%d%d", &l, &r, &a, &b);
		for (int i = 1; i <= n; i++) f[i] = i;
		for (int i = l; i <= r; i++)
		{
			int fx = find (e[i].u), fy = find (e[i].v);
			if (fx != fy) f[fy] = fx;
			else  continue;
			if (find(a)==find(b)) break;
		}
		int fx = find (a), fy = find (b);
		if (fx == fy) puts ("1");
		else puts ("0");
	}
}
