#include<bits/stdc++.h>
#define N 100005
#define ll long long
int n, m, vis[N], cnt;
ll ha[N], ans;
std::vector<int>e[N];
std::vector<ll> t;
std::vector<std::pair<int, int> > unt;
ll R48 ()
{
	ll x = 0;
	for (int k = 0; k < 3; k++) x = (x << 15) | rand ();
	return x;
}
void dfs1 (int u, int fa)
{
	vis[u] = 1;
	for (int v : e[u])
	{
		if (!vis[v]) dfs1 (v, u);
		else if (v != fa && v < u) unt.push_back ({ v,u });
	}
}
ll dfs2 (int u, int fa)
{
	vis[u] = 1;
	for (int v : e[u]) if (v^fa && !vis[v])
		ha[u] ^= dfs2 (v, u);
	if (fa) t.push_back (ha[u]);
	return ha[u];
}
int main ()
{
	freopen ("cip.in", "r", stdin);
	freopen ("cip.out", "w", stdout);
	srand (233);
	scanf ("%d%d", &n, &m);
	for (int i = 1, u, v; i <= m; i++)
		scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
	dfs1 (1, 0);
	for (auto G : unt)
	{
		ll val = R48 ();
		ha[G.first] ^= val, ha[G.second] ^= val;
		t.push_back (val);
	}
	for (int i = 1; i <= n; i++) vis[i] = 0;
	dfs2 (1, 0);
	for (auto v : t) if (!v) cnt++;
	ans += 1ll * cnt * (m - cnt);
	std::sort (t.begin (), t.end ());
	for (int i = 0, j = 0; i < t.size (); i = j)
	{
		for (; j < t.size () && t[i] == t[j]; j++);
		ans += 1ll * (j - i) * (j - i - 1) / 2;
	}
	printf ("%lld\n", ans);
}