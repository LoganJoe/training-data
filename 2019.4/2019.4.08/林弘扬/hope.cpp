#include<bits/stdc++.h>
#define N 1000005
#define ll long long
#define mod 998244353
int n, L, K, ans;
std::vector<int> e[N];
ll Pow (ll x, ll k)
{
	ll t = 1;
	for (; k; k >>= 1, x = x * x%mod) if (k & 1) t = t * x%mod;
	return t;
}
namespace solve_Nle1000 //n <=1000, k <= 1
{
	int f[1005][1005], g[1005];
	void dfs (int u, int fa)
	{
		f[u][0] = 1;
		for (int v : e[u]) if (v^fa)
		{
			dfs (v, u);
			for (int i = 0; i <= L; i++)
				for (int j = 0; i + j + 1 <= L; j++)
					ans = (ans + 1ll * f[u][i] * f[v][j]) % mod;
			for (int i = 0; i <= L; i++) g[i] = 0;
			for (int i = 0; i <= L; i++)
				for (int j = 0; i + j + 1 <= L; j++)
					g[std::max (j + 1, i)] = (g[std::max (j + 1, i)] + 1ll * f[u][i] * f[v][j]) % mod;
			for (int i = 0; i <= L; i++) f[u][i] = (g[i] + f[u][i]) % mod;
		}
	}
	void Main ()
	{
		L = std::min (L << 1, n), dfs (1, 0);
		std::cout << (n + ans) % mod << "\n";
	}
}
namespace solveLle100Keq1 //n <= 100000, L <= 100, K = 1
{
	int f[1005][205], g[205];
	void dfs (int u, int fa)
	{
		f[u][0] = 1;
		for (int v : e[u]) if (v^fa)
		{
			dfs (v, u);
			for (int i = 0; i <= L; i++)
				for (int j = 0; i + j + 1 <= L; j++)
					ans = (ans + 1ll * f[u][i] * f[v][j]) % mod;
			for (int i = 0; i <= L; i++) g[i] = 0;
			for (int i = 0; i <= L; i++)
				for (int j = 0; i + j + 1 <= L; j++)
					g[std::max (j + 1, i)] = (g[std::max (j + 1, i)] + 1ll * f[u][i] * f[v][j]) % mod;
			for (int i = 0; i <= L; i++) f[u][i] = (g[i] + f[u][i]) % mod;
		}
	}
	void Main ()
	{
		L = std::min (L << 1, n), dfs (1, 0);
		std::cout << (n + ans) % mod << "\n";
	}
}
namespace solve_LnK1 //ignore the limit of L. Mostly work correct in K = 1.
{
	int f[N], g[N], h[N];
	void dfs1 (int u, int fa)
	{
		f[u] = 1;
		for (int v : e[u]) if (v^fa)
			dfs1 (v, u), f[u] = 1ll * f[u] * (f[v] + 1) % mod;
	}
	void dfs2 (int u, int fa)
	{
		if (fa) g[u] = 1ll * g[fa] * Pow (f[u] + 1, mod - 2) * f[u] % mod;
		else g[u] = f[u];
		for (int v : e[u]) if (v^fa) dfs2 (v, u);
	}
	void Main ()
	{
		dfs1 (1, 0), dfs2 (1, 0); g[1] = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= K; j++) h[j] = 0;
			h[0] = 1;
			for (int k = 1; k <= K; k++)
				for (int j = K; j; j--)
				{
					h[j] = (1ll * h[j] * g[i] + 1ll * h[j - 1] * f[i]) % mod;
					h[0] = 1ll * h[0] * g[i] % mod;
				}
			for (int j = 1; j <= K; j++) ans = (ans + h[j]) % mod;
		}
		std::cout << ans << "\n";
	}
}
int main ()
{
	freopen ("hope.in", "r", stdin);
	freopen ("hope.out", "w", stdout);
	scanf ("%d%d%d", &n, &L, &K);
	for (int i = 1, u, v; i < n; i++)
		scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
	if (n <= 1000) return solve_Nle1000::Main (), 0;
	if (n <= 100000 && L <= 100 && K == 1) return solveLle100Keq1::Main (), 0;
	return solve_LnK1::Main (), 0;
}
