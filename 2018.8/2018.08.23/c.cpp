#include<bits/stdc++.h>
#define N 100005
int n, m, a[N], f[505][1005], ans;
void solve1 ()
{
	memset (f, 1, sizeof (f));
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			if(j>=a[i]) f[i][j] = std::min (f[i - 1][j], f[i - 1][j - a[i]] + i * a[i]);
			else f[i][j] = f[i - 1][j];
			if (f[i][j] <= m - 2 * i) ans = std::max (ans, j);
		}
	}
	printf ("%d\n", ans);
}
struct node
{
	int v, cost;
	friend bool operator<(node t1, node t2)
	{
		return t1.v > t2.v || t1.v == t2.v &&t1.cost < t2.cost;
	}
};
void solve2 ()
{
	std::vector<node> f, g;
	f.push_back ({ 0,0 });
	for (int i = 1; i <= n; i++)
	{
		int pre = -1, Mincost = 1e9;
		std::sort (f.begin (), f.end ());
		for (auto st : f)
		{
			if (st.cost > m - 2 * i) continue;
			if (st.v == pre || st.cost > Mincost) continue;
			ans = std::max (ans, st.v);
			if (st.cost <= m - 2 * i - i * a[i]) g.push_back ({ st.v + a[i],st.cost + i * a[i] });
			g.push_back (st);
			pre = st.v, Mincost = std::min (Mincost, st.cost);
		}
		f.clear ();
		std::swap (f, g);
	}
	printf ("%d\n", ans);
}
int main ()
{
	freopen("w.in","r",stdin);freopen("w.out","w",stdout);
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf ("%d", &a[i]);
	if (n <= 500 && m <= 1000) solve1 ();
	else solve2 ();

}
/*
5 6
1 1 1 1 1
*/
