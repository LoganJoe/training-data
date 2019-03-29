#include<bits/stdc++.h>
#define N 505
int Case, n, mod, deg[N], ans, po[N];
void dfs (int x)
{
	if (x > n) return (void)(ans++);
	for (int u = 1; u <= n; u++)
		for (int v = u + 1; v <= n; v++)
		{
			if (u == x || v == x) continue;
			if (!deg[u] || !deg[v]) continue;
			deg[u]--, deg[v]--;
			dfs (x + 1);
			deg[u]++, deg[v]++;
		}
}
void solve1 ()
{
	for (int i = 1; i <= n; i++) deg[i] = 2;
	dfs (1);
	std::cout << ans << "\n";
}
int f[14349000];
int dfs (int x, int S)
{
	if (x > n) return 1;
	if (f[S] >= 0)return f[S];
	int res = 0, T = S, deg[16];
	for (int i = 1; i <= n; i++) deg[i] = T % 3, T /= 3;
	for (int u = 1; u <= n; u++)
		for (int v = u + 1; v <= n; v++)
		{
			if (u == x || v == x) continue;
			if (!deg[u] || !deg[v]) continue;
			res = (res + dfs (x + 1, S - po[u - 1] - po[v - 1])) % mod;
		}
	return f[S] = res;
}
void solve2 ()
{
	po[0] = 1;
	for (int i = 1; i <= n; i++) po[i] = 1ll * po[i - 1] * 3 % mod;
	memset (f, -1, sizeof (f));
	std::cout << dfs (1, po[n] - 1) << "\n";
}
int main ()
{
	freopen("abracadabra.in","r",stdin);
	freopen("abracadabra.out","w",stdout);
	scanf ("%d%d%d", &Case, &n, &mod);
	if (n <= 2) return puts ("0"), 0;
	if (n <= 5) return solve1 (), 0;
	if (n <= 15) return solve2 (), 0;
}
/*
10 13 998244353
*/
