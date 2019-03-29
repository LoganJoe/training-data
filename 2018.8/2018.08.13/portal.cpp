#include<bits/stdc++.h>
#define N 100005
#define db double
int n, m, a[N], head[N], cnt, tot[N];
struct edge
{
	int u, v, w; double p;
};
std::vector<edge>e[N];
db f[N];
int mark[N], pl[N];
void solve (int x, int id)
{
	if (x > tot[id])
	{
		double p = 1, res = 0, fl = 0;
		for (int i = 1; i <= tot[id]; i++)
		{

			res = res + (f[e[id][pl[i]].v] + e[id][pl[i]].w) * p * e[id][pl[i]].p + e[id][pl[i]].w * p * (1 - e[id][pl[i]].p);
			p *= (1 - e[id][pl[i]].p);
			//	printf ("%lf\n", (f[e[id][pl[i]].v] + e[id][pl[i]].w) * p * e[id][pl[i]].p);
		}
		res = res + p * (a[id] + f[id + 1]);
		f[id] = std::min (f[id], res);
		return;
	}
	for (int i = 0; i < tot[id]; i++)if (!mark[i]) mark[i] = 1, pl[x] = i, solve (x + 1, id), mark[i] = 0;
}
int main ()
{
	freopen("portal.in","r",stdin);
	freopen("portal.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i < n; i++) scanf ("%d", &a[i]);
	for (int i = 1; i <= m; i++)
	{
		int u, v, w; db p;
		scanf ("%d%d%lf%d", &u, &v, &p, &w);
		e[u].push_back ({ u,v,w,p }); tot[u]++;
	}
	for (int i = n - 1; i; i--)
	{
		f[i] = f[i + 1] + a[i];
		solve (1, i);
	}
	printf ("%.2lf\n", f[1]);
}
/*
4 3
26 27 28
1 3 0.5 15
2 4 0.8 18
3 4 0.9 20
*/
