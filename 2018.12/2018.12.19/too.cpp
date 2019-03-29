#include<bits/stdc++.h>
#define N 50005
#define M 205
#define mod 998244353
int n, m, f[N][M][3], g[M][3];
std::vector<int>e[N];
int mul (int x) { return x >= mod ? x - mod : x; }
void dfs (int u, int fa)
{
	int mark = 1;
	for (int v : e[u]) if (v != fa) dfs (v, u);
	if (e[u].size () - (fa > 0) == 0) return (void)(f[u][0][1] = 1);
	for (int v : e[u])
	{
		if (v == fa) continue;
		if (mark)
		{
			mark = 0;
			for (int i = 0; i < m; i++)
				f[u][i][2] = (1ll * f[u][i][2] +  f[v][i][1] + 2ll * f[v][i][0]) % mod, f[u][i][1] = f[v][i][1];
			continue;
		}
		for (int i = 0; i < m; i++) g[i][0] = g[i][1] = 0;
		for (int i = 0; i < m; i++) if (f[v][i][0] || f[v][i][1])
			for (int j = 0; j < m; j++)
			{
				int to = (i + j) % m;
				g[to][0] = mul (g[to][0] + 1ll * mul(2ll * f[v][i][0]) + 1ll * f[v][i][1] * f[u][j][2] % mod);
				g[to][1] = mul (g[to][1] + mul(1ll * mul (f[u][j][2] + f[u][j][1]) * f[v][i][1] % mod + 1ll*f[v][i][0]*f[u][j][1]%mod));
			}
		for (int i = 0; i < m; i++)
				f[u][i][2] = (1ll * f[u][i][2] + mul(2ll * f[v][i][0]) + f[v][i][1]) % mod;
		for (int i = 0; i < m; i++) f[u][i][0] = mul (f[u][i][0] + g[i][0]), f[u][i][1] = mul (f[u][i][1] + g[i][1]);
	}
	for (int i = 0; i < m; i++) f[u][i][0] = mul (f[u][i][0] + (i ? f[u][i - 1][1] : f[u][m - 1][1]));
	for (int i = 0; i < m; i++) f[u][i][1] = f[u][i][2];
	/*
	printf ("------#%d-----\n", u);
	for (int i = 0; i < m; i++) std::cout << f[u][i][0] << " "; puts ("");
	for (int i = 0; i < m; i++) std::cout << f[u][i][1] << " "; puts ("");
	for (int i = 0; i < m; i++) std::cout << f[u][i][2] << " "; puts ("");
	*/
}
int main ()
{
	scanf ("%d%d", &n, &m);
	for (int i = 1, u, v; i < n; i++) 
		scanf ("%d%d", &u, &v), e[u].push_back (v), e[v].push_back (u);
	dfs (1, 0);
	std::cout << (f[1][0][0] + f[1][0][1]) % mod<< "\n";
}

